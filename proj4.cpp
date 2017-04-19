#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;
#include "EventTypeClass.h"
#include "LinkedNodeClass.h"
#include "SortedListClass.h"
#include "FIFOQueueClass.h"
#include "random.h"
#include <string>
#include "SimulationClass.h"

const int defaultRideCapacity = 20;
/*
Jarvis Miller
Code written: 04/05/17
Purpose: This code runs a simulation of three FIFO queues with different
priority. The context given is three lines for an amusement park ride, 
and each line (FIFO) has a different probability of a newcomer being 
sorted into it. The three lines are dequeued at different rates into the
amusement ride. We gather statistics from the simulation once it has
ended. */


int main(int argc, char** argv)
{
  int argVArgument = 1;

  // open file and read in the data as I create a SimulationClass object
  ifstream str(argv[argVArgument]);

  if (str.eof())
  {
    cout << "EOF while reading file!" << endl;
    
    return 0;
  }
  else if (str.fail())
  {
    str.clear();
    str.ignore(200, '\n');
    cout << "Error while reading file!" << endl;
    return 0;
  }


  int UserChoice;
  int defaultArgs = 1;
  int userArgs = 0;
  int rideCapacity;
  string parkName;

  cout << "Run with default car size and park name?" << endl;
  cout << "Enter (1) for yes, another int for no: ";
  cin >> UserChoice;

  if (UserChoice == defaultArgs)
  {
    rideCapacity = defaultRideCapacity;
    parkName = "Space Mountain";
  }
  else
  {
    cout << "You said no need to error check so pls enter as requested!" 
         << endl;
    cout << "Enter car capacity (integer): ";
    cin >> rideCapacity;
    cout << "Enter park name (no quotes): ";
    cin.ignore(); 
    getline(cin, parkName);
  }
  SimulationClass mySim(str, rideCapacity, parkName);
  str.close();

  // first rider arrives at
  int riderTime = 0;
  // first car arrives at
  int carTime = 1;

  // seed first rider arrival
  cout << endl;
  cout << "Seeding first rider arrival and car arrival events!" << endl;
  cout << endl;
  mySim.boardLine(riderTime);
  mySim.boardRide(carTime);   

  int empty = 0;
  while (mySim.getEventSize() != empty)
  {
    mySim.handleNextEvent(riderTime, carTime);
    cout << "======================================================="<<  endl;
  }


  // statistics
  cout << endl;
  cout << "Statistics:" << endl << endl;
  mySim.getAvgWaitTime(carTime);
  mySim.getTotalRides();
  mySim.printMaxes();
  mySim.printTotalPerLine();



  // TESTING OF EACH DATA STRUCTURE


  //LinkedNodeClass < int >* head; // head that will point to first row
  //head = new LinkedNodeClass< int >(NULL, 7, NULL); // created first node
  //cout << "the first node has value: " << head->getValue() << endl;
/*
  SortedListClass < char > myList;
  // make sure head and tail are NULL - confirmed
  cout << "head is : " << myList.coutHeadorTail(1) << endl;
  cout << "tail is : " << myList.coutHeadorTail(0) << endl;
  myList.insertValue('a');
  // confirms that they both point to the same thing
  cout << "after inserting node, head is : " << myList.coutHeadorTail(1) << endl;
  cout << "after inserting node, tail is : " << myList.coutHeadorTail(0) << endl;


  cout << "Attempting to add node number 2" << endl;
  cout << endl;
  myList.insertValue('b');
  cout << endl;// confirms that tail has indeed changed to another node :D 
  cout << "after inserting node, head is : " << myList.coutHeadorTail(1) << endl;
  cout << "after inserting node, tail is : " << myList.coutHeadorTail(0) << endl;
  cout << endl;

  cout << "Attempting to add node number 3" << endl;
  cout << endl;
  myList.insertValue('A');
  cout << endl;// confirms that tail has indeed changed to another node :D 
  cout << "after inserting node, head is : " << myList.coutHeadorTail(1) << endl;
  cout << "after inserting node, tail is : " << myList.coutHeadorTail(0) << endl;

  cout << "Attempting to add node number 4" << endl;
  cout << endl;
  //myList.insertValue("C");
  cout << endl;// confirms that tail has indeed changed to another node :D 
  cout << "after inserting node, head is : " << myList.coutHeadorTail(1) << endl;
  cout << "after inserting node, tail is : " << myList.coutHeadorTail(0) << endl;
  
  //int remove = 0;
  char remove = 'r';
  cout << "Attempting remove first" << endl;
  cout << myList.removeFront(remove) << endl;
  cout << "head is : " << myList.coutHeadorTail(1) << endl;
  cout << "tail is : " << myList.coutHeadorTail(0) << endl;

  cout << "Attempting to add node number 5" << endl;
  cout << endl;
  myList.insertValue(remove);
  cout << endl;
  cout << "after inserting node, head is : " << myList.coutHeadorTail(1) << endl;
  cout << "after inserting node, tail is : " << myList.coutHeadorTail(0) << endl;

  cout << "size of list: " << myList.getNumElems() << endl;
  cout << "Attempting remove last" << endl;
  cout << myList.removeLast(remove) << endl;
  cout << "head is : " << myList.coutHeadorTail(1) << endl;
  cout << "tail is : " << myList.coutHeadorTail(0) << endl; 

  cout << "Total number of nodes: " << myList.getNumElems() << endl;
  cout << "Should be 4 b/c I added 5 but removed one" << endl;

  cout << "Attempting print forward" << endl;
  myList.printForward();
/*
  cout << endl;
  cout << "Attempting print backwards" << endl;
  myList.printBackward();

  cout << endl;
  cout << "Attempting getElemAtIndex" << endl;
  int numElems = myList.getNumElems();
  for (int i = 0; i < numElems; i++)
  {
    myList.getElemAtIndex(i, remove);
  }

  cout << "Attempting copy ctor" << endl;

  SortedListClass < int > myList2 = SortedListClass < int > (myList);
  cout << "head is: " << myList2.coutHeadorTail(1) << endl;
  cout << "tail is: " << myList2.coutHeadorTail(0) << endl;


  cout << endl;
  cout << "Attempting to clear list" << endl;
  myList.clear();
  cout << "now, the number of nodes are: " << myList.getNumElems() << endl;
  cout << "head is : " << myList.coutHeadorTail(1) << endl;
  cout << "tail is : " << myList.coutHeadorTail(0) << endl;

  cout << "Printing out copied list" << endl;
  myList2.printForward();
  cout << endl;

  cout << "Printing out deleted list" << endl;
  myList.printForward();
  cout << endl;

  cout << "attempting copy of deleted list" << endl;
  SortedListClass < int > myList3 = SortedListClass < int > (myList);
  cout << endl;

  cout << "Printing out copy of deleted list" << endl;
  myList3.printForward();
  cout << endl;
*/
  /*
  FIFOQueueClass < int > fifo;
  for (int i = 0; i < 1; i++)
  {
    cout << "created FIFOQueueClass object, will attempt enqueue" << endl;
    fifo.enqueue(7);
    //fifo.print();
    cout << "after enqueue, head is : " << fifo.coutHeadorTail(1) << endl;
    cout << "after enqueue, tail is : " << fifo.coutHeadorTail(0) << endl;

    fifo.enqueue(10);
    cout << "after enqueue, head is : " << fifo.coutHeadorTail(1) << endl;
    cout << "after enqueue, tail is : " << fifo.coutHeadorTail(0) << endl;

    //cout << "size of fifo " << fifo.getNumElems() << endl;
    fifo.dequeue(remove);
    cout << "after dequeue, head is : " << fifo.coutHeadorTail(1) << endl;
    cout << "after dequeue, tail is : " << fifo.coutHeadorTail(0) << endl;

  }
  fifo.enqueue(10);
  //fifo.print();

  //cout << fifo.getNumElems() << endl;
*/

  return 0;
}


