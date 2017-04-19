#include <iostream>
using namespace std;
#include "EventTypeClass.h"
#include "LinkedNodeClass.h"
#include "FIFOQueueClass.h"
#include "SortedListClass.h"
#include "random.h"
#include <cstdlib>
#include <fstream>
#include <string>
#include "SimulationClass.h"

const int carEvent = 1;
const int riderEvent = 0;

/* Default ctor - takes in a filestream to read in the data
that determine the simulation parameters. It then asks for the
seed that generates random values used in the simulation. Lastly,
it initializes all the values used in teh simulation.
*/
SimulationClass::SimulationClass(ifstream &myStream, int carSize, string parkName)
{

  /*ifstream inFile;
  string fname;
  cin >> fname;
  cout << fname << endl;
  // need to do an error check to make sure the file isn't empty
  inFile.open(fname.c_str());*/


  myStream >> closingTime >> riderArrMean >> riderArrSD 
      >> carArrivalMin >> carArrivalMax >> percentSFP >> percentFP 
      >> numSFPAdmit >> numFPAdmit;

  int seed;
  cout << "Enter your desired seed: "; 
  cin >> seed;
  carCapacity = carSize;
  srand(seed);
  rSize = 0;
  fpSize = 0;
  sfpSize = 0;
  rTotal = 0;
  fpTotal = 0;
  sfpTotal = 0;
  AmusementPark = parkName;

  // statistics
  maxRegularLine = 0;
  maxFastPassLine = 0;
  maxSuperFastPassLine = 0;
  numRides = 0;

  cout << "Welcome to " << AmusementPark << "!" << endl;
}


/* handleNextEvent(int &riderT, int &carT) - it takes in the current time
of the rider's arrival into the amusement park and the car's departure time.
It then looks at the next event in the sorted list and runs that event (which
updates riderT or carT to represent then next rider or car arrival time and 
puts that new event into the sorted list). It then removes the event that just
transpired.
*/
void SimulationClass::handleNextEvent(int &riderT, int &carT)
{
  // rename these
  EventTypeClass requestedEvent;
  EventTypeClass removeEvent;
  int firstEvent = 0;

  // Gets the first event in the sorted list
  eventList.getElemAtIndex(firstEvent, requestedEvent);

  // make the event type a variable
  // board ride deletes as desired... but still have mem leak in board line
  if (requestedEvent.getEventType() == carEvent)
  {
    boardRide(carT);
    eventList.removeFront(removeEvent);
  }
  else
  {
    // for the last few, it adds two ppl but the car only takes one person..
    boardLine(riderT);
    eventList.removeFront(removeEvent);
  }
}

/* getEventSize() - returns the number of events in the sorted list.
This is mainly to ensure that all events transpired by the time the 
simulation has ended.
*/
int SimulationClass::getEventSize()
{
  int length = eventList.getNumElems();
  return length;
}


/* boardLine(int %riderTime) - Takes in the time of the rider who is 'waiting'
to be queued into one of three FIFOs. It then enqueues that person into 
whichever FIFO it is randomly sorted in. After sorting into a line, it checks
if that line is now at it's current max size or not. Lastly, it determines the
next rider's arrival time into the amusement park and puts that event into the
sorted list. It returns when the next person will arrive
*/
int SimulationClass::boardLine(int &riderTime)
{
  double randVal;
  int maxRange = 100;
  int minRange = 0;
  int rider = 0;
  int nextArrTime;
  randVal = getUniform(minRange, maxRange);


  if (randVal < percentSFP)
  {
    //cout << "sfp" << endl;
    superFastLine.enqueue(rider);
    sfpSize += 1;
    sfpTotal += 1;
    cout << "One person joined the Super Fast Pass line." << endl;
    cout << "sfp line size is: " << sfpSize << endl;
  }
  else if ((randVal > percentSFP) && (randVal < percentSFP + percentFP))
  {
    //cout << "fp" << endl;
    fastPassLine.enqueue(rider);
    // change to fpSize++;
    fpSize += 1;
    fpTotal += 1;
    cout << "One person joined the Fast Pass line." << endl;
    cout << "fast pass line size is: " << fpSize << endl;
  }
  else
  {
    //cout << "reg" << endl;
    regularLine.enqueue(rider);
    rSize += 1;
    rTotal += 1;
    cout << "One person joined the regular line." << endl;
    cout << "regular line size is: " << rSize << endl;
  }
  // check if line size is the current largest or not
  updateMaxOfLines();

  nextArrTime = riderTime + getNormal(riderArrMean, riderArrSD);
  cout << "next rider arrival time is: " << nextArrTime << endl;

  if (nextArrTime > closingTime)
  {
    cout << "Past the closing time. This passenger can't enter." << endl;
    return riderTime;
  }
  else
  {
    EventTypeClass riderArrives(riderEvent, nextArrTime);
    eventList.insertValue(riderArrives);
    riderTime = nextArrTime;
  }
  return nextArrTime;
}


/* boardRide(int &carTime) - This function dequeues from the different
FIFOs until the lines are empty or the car is full. Afterwards,
it gathers some statistics to print to the console. Lastly it determines
the next car's arrival time and returns it.
*/
int SimulationClass::boardRide(int &carTime)
{
  int i;
  int carEmpty = 0;
  bool carFilled = false;
  int carSpace = carCapacity;
  int numRegAdmit = carCapacity - numSFPAdmit - numFPAdmit;
  int nextArrTime;
  int rider;
  int numLoadedFromRegular = 0;
  int numLoadedFromFastPass = 0;
  int numLoadedFromSuperFastPass = 0;

  int numPassengers;
  numPassengers = regularLine.getNumElems() + superFastLine.getNumElems() +
                  fastPassLine.getNumElems();


  if (numPassengers == 0 && carTime > closingTime)
  {
    cout << "No passengers and past closing time. We are closed!" << endl;
    return 0;
  }

  // dequeue based on number to admit for each line
  for (i = 0; i < numSFPAdmit; i++)
  {
    if (superFastLine.dequeue(rider) && !carFilled)
    {
      cout << "Dequed from Super Fast Pass Line" << endl;
      // carSpace--;
      carSpace--;
      //cout << "first load trial (sfp) " << endl;
      sfpSize--;
      numLoadedFromSuperFastPass += 1;
      carFilled = checkCarCapacity(carSpace);
    }
  }

  for (i = 0; i < numFPAdmit; i++)
  { // if we actually took someone from that line
    if (fastPassLine.dequeue(rider) && !carFilled)
    {
      cout << "Dequed from Fast Pass" << endl;
      carSpace--;
      fpSize--;
      numLoadedFromFastPass += 1;
      carFilled = checkCarCapacity(carSpace);
    }
  }

  for (i = 0; i < numRegAdmit; i++)
  {
    if (regularLine.dequeue(rider) && !carFilled)
    {
      cout << "Dequed from Regular line " << endl;
      carSpace--;
      rSize--;
      numLoadedFromRegular += 1;
      carFilled = checkCarCapacity(carSpace);
    }  
  }

  carFilled = checkCarCapacity(carSpace);

  // dequeue based on FIFO priority
  while (superFastLine.dequeue(rider) && !carFilled)
  {
    carSpace--;
    cout << "2nd stage deque from Super Fast Pass Line" << endl;
    numLoadedFromSuperFastPass += 1;
    sfpSize--;
    /*if (carSpace == carEmpty)
    {
      carFilled = true;
    }*/
    carFilled = checkCarCapacity(carSpace);
  }

  while (fastPassLine.dequeue(rider) && !carFilled)
  {
    carSpace--;
    cout << "2nd stage deque from Fast Pass Line" << endl;
    numLoadedFromFastPass += 1;
    fpSize--;
    /*if (carSpace == carEmpty)
    {
      carFilled = true;
    }*/
    carFilled = checkCarCapacity(carSpace);
  }

  while (regularLine.dequeue(rider) && !carFilled)
  {
    carSpace--;
    cout << "2nd stage deque from Regular Line" << endl;
    numLoadedFromRegular += 1;
    rSize--;
    /*if (carSpace == carEmpty)
    {
      carFilled = true;
    }*/
    carFilled = checkCarCapacity(carSpace);
  }

  cout << "Loading car..." << endl;
  cout << "Number loaded from Regular Line: " << numLoadedFromRegular << endl;
  cout << "Number loaded from Super Fast Pass Line: " 
       << numLoadedFromSuperFastPass << endl;
  cout << "Number loaded from fast Pass Line: " 
       << numLoadedFromFastPass << endl;
  cout << "Amount of space left in car after loading: " << carSpace << endl;

  // get next car arrival time and make event

  nextArrTime = carTime + getUniform(carArrivalMin, carArrivalMax);

  cout << "next car arrival time is: " << nextArrTime << endl;
  EventTypeClass carEvent(1, nextArrTime);
  eventList.insertValue(carEvent);

  // increment numRides
  numRides += 1;

  carTime = nextArrTime;

  return nextArrTime;


}


// checkCarCapacity(int carSpace) is a way to see if the car is empty
// or not in a cleaner way
bool SimulationClass::checkCarCapacity(int carSpace)
{
  bool success = false;
  int empty = 0;
  if (carSpace == empty)
  {
    success = true;
  }
  return success;
}


// getTotalRides() - just prints the total number of rides
void SimulationClass::getTotalRides()
{
  cout << "The total number of rides were: " << numRides << endl;
}


// maybe change this
int SimulationClass::getAvgWaitTime(int totalTime)
{
  double avgWait;
  int half = 2;
  int expectedValue = (carArrivalMax + carArrivalMin) / half;
  cout << "totaltime: " << totalTime << " numRides " << numRides << endl;
  avgWait = (totalTime / numRides) - expectedValue;
  cout << "Deviation from car arrival Expected Value : " << avgWait 
       << " ticks" << endl;
  return avgWait;
}


/* updateMaxOfLines() - checks the current length of each line and determines
if the current line length is the max length. If so, it assigns it stores 
the said length.
*/

void SimulationClass::updateMaxOfLines()
{
  if (rSize > maxRegularLine)
  {
    maxRegularLine = rSize;
  }

  if (fpSize > maxFastPassLine)
  {
    maxFastPassLine = fpSize;
  }

  if (sfpSize > maxSuperFastPassLine)
  {
    maxSuperFastPassLine = sfpSize;
  }
}


// printMaxes() - prints the max line length for each FIFO
void SimulationClass::printMaxes()
{
  cout << "Max of Regular line: " << maxRegularLine << endl;
  cout << "Max of Fast Pass line: " << maxFastPassLine << endl;
  cout << "Max of Super Fast Pass line: " << maxSuperFastPassLine << endl;
}


// printTotalPerLine() - prints the total number of riders who stayed in each
// line
void SimulationClass::printTotalPerLine()
{
  cout << "Total in Regular line: " << rTotal << endl;
  cout << "Total in Fast Pass line: " << fpTotal << endl;
  cout << "Total in Super Fast Pass line: " << sfpTotal << endl;
}


SimulationClass::~SimulationClass()
{
  eventList.clear();
  int regSize = regularLine.getNumElems();
  int fpSize = fastPassLine.getNumElems();
  int sfpSize = superFastLine.getNumElems();
  int remove = 0;

  for (int i = 0; i < regSize; i++)
  {
    regularLine.dequeue(remove);
  }

  for (int i = 0; i < fpSize; i++)
  {
    fastPassLine.dequeue(remove);
  }

  for (int i = 0; i < sfpSize; i++)
  {
    superFastLine.dequeue(remove);
  }
  cout << endl;
  cout << "Thank you for visiting " << AmusementPark << "!" << endl;
}