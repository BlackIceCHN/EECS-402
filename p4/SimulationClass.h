#ifndef _SIMULATION_CLASS_
#define _SIMULATION_CLASS_

#include <fstream>
#include "LinkedNodeClass.h"
#include "FIFOQueueClass.h"
#include "SortedListClass.h"
#include "EventTypeClass.h"
#include "random.h"
#include <iostream>
#include <string>
using namespace std;



/* HEADER: SimulationClass handles the simulation. It contains all objects
needed for the simulation such at the FIFOs, the event list, and the values
for the statistics. It handles each event until the simulation is over. 
While the simulation runs, it prints out what's going on to the console. 
When the simulation terminates, it prints out the statistics from the 
simulation.
*/


class SimulationClass
{
private:
  FIFOQueueClass < int > regularLine;
  FIFOQueueClass < int > fastPassLine;
  FIFOQueueClass < int > superFastLine;
  SortedListClass < EventTypeClass > eventList;

  int carArrivalMin, carArrivalMax;
  double riderArrMean, riderArrSD;
  int closingTime, percentFP, percentSFP, numFPAdmit, numSFPAdmit;
  int rSize, fpSize, sfpSize, rTotal, fpTotal, sfpTotal;
  int carCapacity;
  string AmusementPark;
  // statistics

  int maxRegularLine, maxFastPassLine, maxSuperFastPassLine;

  double numRides;

public:
  SimulationClass(ifstream &myStream, int carSize, string parkName);

  int boardRide(int &carTime);

  int boardLine(int &riderTime);

  int getAvgWaitTime(int totalTime);

  void printMaxes();

  void updateMaxOfLines();

  void getTotalRides();

  void printTotalPerLine();

  void handleNextEvent(int &riderT, int &carT);

  int getEventSize();

  bool checkCarCapacity(int carSpace);

  ~SimulationClass();
  
};


#endif