#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "IntersectionSimulationClass.h"
#include "random.h"
#include "constants.h"

void IntersectionSimulationClass::readParametersFromFile(
                                  const string &paramFname) {
    bool success = true;
    ifstream paramF;
  
    paramF.open(paramFname.c_str());
  
    //Check that the file was able to be opened...
    if (paramF.fail()) {
        success = false;
        cout << "ERROR: Unable to open parameter file: " << paramFname << endl;
    }
    else{
        //Now read in all the params, according to the specified format of
        //the text-based parameter file.
        if (success) {
            paramF >> randomSeedVal;
            if (paramF.fail() || randomSeedVal < 0) {
                success = false;
                cout << "ERROR: Unable to read/set random generatsor seed" 
                << endl;
            }
        }

        if (success) {
            paramF >> timeToStopSim;
            if (paramF.fail() || timeToStopSim <= 0) {
                success = false;
                cout << "ERROR: Unable to read/set simulation end time" 
                << endl;
            }
        }
        
        if (success) {
            paramF >> eastWestGreenTime >> eastWestYellowTime;
            if (paramF.fail() || eastWestGreenTime <= 0 ||
                eastWestYellowTime <= 0) {
                success = false;
                cout << "ERROR: Unable to read/set east-west times" 
                << endl;
            }
        }

        if (success) {
            paramF >> northSouthGreenTime >> northSouthYellowTime;
            if (paramF.fail() || northSouthGreenTime <= 0 ||
                northSouthYellowTime <= 0) {
                success = false;
                cout << "ERROR: Unable to read/set north-south times" 
                << endl;
            }
        }

        if (success) {
            paramF >> eastArrivalMean >> eastArrivalStdDev;
            if (paramF.fail() || eastArrivalMean <= 0 ||
                eastArrivalStdDev < 0) {
                success = false;
                cout << "ERROR: Unable to read/set east arrival distribution" 
                << endl;
            }
        }

        if (success) {
            paramF >> westArrivalMean >> westArrivalStdDev;
            if (paramF.fail() || westArrivalMean <= 0 ||
                westArrivalStdDev < 0) {
                success = false;
                cout << "ERROR: Unable to read/set west arrival distribution" 
                << endl;
            }
        }

        if (success) {
            paramF >> northArrivalMean >> northArrivalStdDev;
            if (paramF.fail() || northArrivalMean <= 0 ||
                northArrivalStdDev < 0) {
                success = false;
                cout << "ERROR: Unable to read/set north arrival distribution" 
                << endl;
            }
        }

        if (success) {
            paramF >> southArrivalMean >> southArrivalStdDev;
            if (paramF.fail() || southArrivalMean <= 0 ||
                southArrivalStdDev < 0) {
                success = false;
                cout << "ERROR: Unable to read/set south arrival distribution" 
                << endl;
            }
        }

        if (success) {
            paramF >> percentCarsAdvanceOnYellow;
            if (paramF.fail() || percentCarsAdvanceOnYellow < 0 ||
                percentCarsAdvanceOnYellow > 100) {
                success = false;
                cout << "ERROR: Unable to read/set percentage yellow advance" 
                << endl;
            }

            //Use the specified seed to seed the random number generator
            setSeed(randomSeedVal);
        }

        paramF.close();
    }
  
    //Let the caller know whether things went well or not by printing the
    if (!success) {
        cout << "ERROR: Parameter file was NOT read in successfully, so the " <<
                "simulation is NOT setup properly!" << endl;
        isSetupProperly = false;
    }
    else{
        cout << "Parameters read in successfully - simulation is ready!" 
        << endl;
        isSetupProperly = true;
    }
}

void IntersectionSimulationClass::printParameters() const {
    cout << "===== Begin Simulation Parameters =====" << endl;
    if (!isSetupProperly) {
        cout << "  Simulation is not yet properly setup!" << endl;
    }
    else{
        cout << "  Random generator seed: " << randomSeedVal << endl;
        cout << "  Simulation end time: " << timeToStopSim << endl;

        cout << "  East-West Timing -" << 
                " Green: " << eastWestGreenTime << 
                " Yellow: " << eastWestYellowTime << 
                " Red: " << getEastWestRedTime() << endl;

        cout << "  North-South Timing -" << 
                " Green: " << northSouthGreenTime << 
                " Yellow: " << northSouthYellowTime << 
                " Red: " << getNorthSouthRedTime() << endl;

        cout << "  Arrival Distributions:" << endl;
        cout << "    East - Mean: " << eastArrivalMean << 
                " StdDev: " << eastArrivalStdDev << endl;
        cout << "    West - Mean: " << westArrivalMean << 
                " StdDev: " << westArrivalStdDev << endl;
        cout << "    North - Mean: " << northArrivalMean << 
                " StdDev: " << northArrivalStdDev << endl;
        cout << "    South - Mean: " << southArrivalMean << 
                " StdDev: " << southArrivalStdDev << endl;

        cout << "  Percentage cars advancing through yellow: " << 
                percentCarsAdvanceOnYellow << endl;
    }
    cout << "===== End Simulation Parameters =====" << endl;
}

void IntersectionSimulationClass::scheduleArrival(const string &travelDir) {
    int arrivalIntervalTime; // time a car will arrive in this dir from now
    int arrivalType; // containing dir info

    if (!isSetupProperly) {
        cout << "  Simulation is not yet properly setup!" << endl;
        return;
    }
    else{
        // check valid direction
        if (travelDir == EAST_DIRECTION) {
            arrivalType = EVENT_ARRIVE_EAST;
            arrivalIntervalTime = getPositiveNormal(eastArrivalMean, 
                                                    eastArrivalStdDev);
            cout << "Time: " << this->currentTime << " Scheduled Event Type: " 
                 << "East-Bound ";
        }
        else if (travelDir == WEST_DIRECTION) {
            arrivalType = EVENT_ARRIVE_WEST;
            arrivalIntervalTime = getPositiveNormal(westArrivalMean, 
                                                    westArrivalStdDev);
            cout << "Time: " << this->currentTime << " Scheduled Event Type: " 
                 << "West-Bound ";
        }
        else if (travelDir == NORTH_DIRECTION) {
            arrivalType = EVENT_ARRIVE_NORTH;
            arrivalIntervalTime = getPositiveNormal(northArrivalMean, 
                                                    northArrivalStdDev);
            cout << "Time: " << this->currentTime << " Scheduled Event Type: " 
                 << "North-Bound ";
        }
        else if (travelDir == SOUTH_DIRECTION) {
            arrivalType = EVENT_ARRIVE_SOUTH;
            arrivalIntervalTime = getPositiveNormal(southArrivalMean, 
                                                    southArrivalStdDev);
            cout << "Time: " << this->currentTime << " Scheduled Event Type: " 
                 << "South-Bound ";
        }
        // check invalid dir
        else {
            cout << "Invalid direction input!" << endl;
            return;
        }

        // create an event and add to the LinkedListClass
        int arrivalTime = currentTime + arrivalIntervalTime;
        cout << "Arrival Time: " << arrivalTime << endl;
        EventClass newArrival(arrivalTime, arrivalType);
        eventList.insertValue(newArrival);
    }
}

void IntersectionSimulationClass::scheduleLightChange() {
    int nextLightType;
    int lightChangeTime;

    if (!isSetupProperly) {
        cout << "  Simulation is not yet properly setup!" << endl;
        return;
    }
    else{
        if (currentLight == LIGHT_GREEN_EW) {
            nextLightType = EVENT_CHANGE_YELLOW_EW;
            lightChangeTime = currentTime + eastWestGreenTime;
            
            // print info
            cout << "Time: " << currentTime << " Scheduled Event Type: "
                 << "Light Change to EW Yellow Time: " << lightChangeTime 
                 << endl; 
        }
        else if (currentLight == LIGHT_YELLOW_EW) {
            nextLightType = EVENT_CHANGE_GREEN_NS;
            lightChangeTime = currentTime + eastWestYellowTime;
            
            // print info
            cout << "Time: " << currentTime << " Scheduled Event Type: "
                 << "Light Change to NS Green Time: " << lightChangeTime 
                 << endl; 
        }
        else if (currentLight == LIGHT_GREEN_NS) {
            nextLightType = EVENT_CHANGE_YELLOW_NS;
            lightChangeTime = currentTime + northSouthGreenTime;
            
            // print info
            cout << "Time: " << currentTime << " Scheduled Event Type: "
                 << "Light Change to NS Yellow Time: " << lightChangeTime 
                 << endl;
        }
        else if (currentLight == LIGHT_YELLOW_NS) {
            nextLightType = EVENT_CHANGE_GREEN_EW;
            lightChangeTime = currentTime + northSouthYellowTime;
            
            // print info
            cout << "Time: " << currentTime << " Scheduled Event Type: "
                 << "Light Change to EW Green Time: " << lightChangeTime 
                 << endl;
        }

        // create an event and add to the LinkedListClass
        EventClass lightChange(lightChangeTime, nextLightType);
        eventList.insertValue(lightChange);
    }
}

bool IntersectionSimulationClass::handleNextEvent() {
    EventClass eventToHandle;
    bool doHandleNext = true;

    if (eventList.removeFront(eventToHandle)) {
        // check time of event in range
        if (eventToHandle.getTimeOccurs() > this->timeToStopSim) {
            cout << "\nNext event occurs AFTER the simulation end time ("
                 << eventToHandle << ")!" << endl;
            doHandleNext = false;
            return doHandleNext;
        }
    }
    else {
        // error when nothing found in eventlist
        cout << "Error: No event scheduled!" << endl;
        doHandleNext = false;
        return doHandleNext;
    }

    if (doHandleNext) {
        int handleType = eventToHandle.getType();
        this->currentTime = eventToHandle.getTimeOccurs();

        // create car for specific direction and enqueue
        if (handleType == EVENT_ARRIVE_EAST) {
            CarClass arrivingCar(WEST_DIRECTION,
                                 eventToHandle.getTimeOccurs());
            eastQueue.enqueue(arrivingCar);

            // update max len
            if (eastQueue.getNumElems() > maxEastQueueLength) {
                maxEastQueueLength = eastQueue.getNumElems();
            }

            // print
            cout << "\nHandling " << eventToHandle << endl;
            cout << "Time: " << this->currentTime << " Car #" 
                 << arrivingCar.getId() << " arrives east-bound" 
                 << " - queue length: " << eastQueue.getNumElems() << endl;
            
            // schedule new arrival
            scheduleArrival(EAST_DIRECTION); 
        }
        else if (handleType == EVENT_ARRIVE_WEST) {
            CarClass arrivingCar(EAST_DIRECTION,
                                 eventToHandle.getTimeOccurs());
            westQueue.enqueue(arrivingCar);

            // update max len
            if (westQueue.getNumElems() > maxWestQueueLength) {
                maxWestQueueLength = westQueue.getNumElems();
            }

            // print
            cout << "\nHandling " << eventToHandle << endl;
            cout << "Time: " << this->currentTime << " Car #" 
                 << arrivingCar.getId() << " arrives west-bound" 
                 << " - queue length: " << westQueue.getNumElems() << endl;
            
            // schedule new arrival
            scheduleArrival(WEST_DIRECTION); 
        }
        else if (handleType == EVENT_ARRIVE_NORTH) {
            CarClass arrivingCar(NORTH_DIRECTION,
                                 eventToHandle.getTimeOccurs());
            northQueue.enqueue(arrivingCar);

            // update max len
            if (northQueue.getNumElems() > maxNorthQueueLength) {
                maxNorthQueueLength = northQueue.getNumElems();
            }

            // print
            cout << "\nHandling " << eventToHandle << endl;
            cout << "Time: " << this->currentTime << " Car #" 
                 << arrivingCar.getId() << " arrives north-bound" 
                 << " - queue length: " << northQueue.getNumElems() << endl;
            
            // schedule new arrival
            scheduleArrival(NORTH_DIRECTION); 
        }
        else if (handleType == EVENT_ARRIVE_SOUTH) {
            CarClass arrivingCar(SOUTH_DIRECTION,
                                 eventToHandle.getTimeOccurs());
            southQueue.enqueue(arrivingCar);

            // update max len
            if (southQueue.getNumElems() > maxSouthQueueLength) {
                maxSouthQueueLength = southQueue.getNumElems();
            }

            // print
            cout << "\nHandling " << eventToHandle << endl;
            cout << "Time: " << this->currentTime << " Car #" 
                 << arrivingCar.getId() << " arrives south-bound" 
                 << " - queue length: " << southQueue.getNumElems() << endl;
            
            // schedule new arrival
            scheduleArrival(SOUTH_DIRECTION); 
        }
        else if (handleType == EVENT_CHANGE_YELLOW_EW) {
            int totalCanPass = eastWestGreenTime;
            int numGoneEast = 0;
            int numGoneWest = 0;
            CarClass passingCar;

            // change light 
            currentLight = LIGHT_YELLOW_EW;

            // print
            cout << "\nHandling " << eventToHandle << endl;
            cout << "Advancing cars on east-west green" << endl;

            // Car passig during green
            while (numGoneEast < totalCanPass && 
                   eastQueue.dequeue(passingCar)) {
                numGoneEast++;
                numTotalAdvancedEast++;
                cout << "  Car #" << passingCar.getId() 
                     << " advances east-bound" << endl;
            }
            while (numGoneWest < totalCanPass && 
                   westQueue.dequeue(passingCar)) {
                numGoneWest++;
                numTotalAdvancedWest++;
                cout << "  Car #" << passingCar.getId() 
                     << " advances west-bound" << endl;
            }

            cout << "East-bound cars advanced on green: " << numGoneEast
                 << " Remaining queue: " << eastQueue.getNumElems() << endl;
            cout << "West-bound cars advanced on green: " << numGoneWest
                 << " Remaining queue: " << westQueue.getNumElems() << endl;
            
            scheduleLightChange();
        }
        else if (handleType == EVENT_CHANGE_GREEN_NS) {
            int totalCouldPass = eastWestYellowTime;
            bool keepAdv = true;
            bool doNextAdv;
            int numGoneEast = 0;
            int numGoneWest = 0;
            CarClass passingCar;

            // change light 
            currentLight = LIGHT_GREEN_NS;

            // print
            cout << "\nHandling " << eventToHandle << endl;
            cout << "Advancing cars on east-west yellow" << endl;

            // east
            while (keepAdv) {
                if (!eastQueue.getNumElems()) {
                    cout << "  No east-bound cars waiting to advance "
                         << "on yellow" << endl;
                    keepAdv = false;
                }
                else {
                    if (numGoneEast < totalCouldPass) {
                        // generate random number
                        int random = getUniform(UNIF_LOWER_BOUND, 
                                                UNIF_UPPER_BOUND);
                        doNextAdv = random < percentCarsAdvanceOnYellow;

                        if (doNextAdv) {
                            eastQueue.dequeue(passingCar);
                            numGoneEast++;
                            numTotalAdvancedEast++;

                            // print info
                            cout << "  Next east-bound car will advance "
                                 << "on yellow" << endl;
                            cout << "  Car#" << passingCar.getId() 
                                 << " advances east-bound" << endl;
                        }
                        else {
                            cout << "  Next east-bound car will NOT advance "
                                 << "on yellow" << endl;
                            keepAdv = false;
                        }
                    }
                    else {
                        keepAdv = false;
                    }
                }
            }

            // west
            keepAdv = true;
            while (keepAdv) {
                if (!westQueue.getNumElems()) {
                    cout << "  No west-bound cars waiting to advance "
                         << "on yellow" << endl;
                    keepAdv = false;
                }
                else {
                    if (numGoneWest < totalCouldPass) {
                        // generate random number
                        int random = getUniform(UNIF_LOWER_BOUND, 
                                                UNIF_UPPER_BOUND);
                        doNextAdv = random < percentCarsAdvanceOnYellow;
                        
                        if (doNextAdv) {
                            westQueue.dequeue(passingCar);
                            numGoneWest++;
                            numTotalAdvancedWest++;

                            // print info
                            cout << "  Next west-bound car will advance "
                                 << "on yellow" << endl;
                            cout << "  Car#" << passingCar.getId() 
                                 << " advances west-bound" << endl;
                        }
                        else {
                            cout << "  Next west-bound car will NOT advance "
                                 << "on yellow"
                                 << endl;
                            keepAdv = false;
                        }
                    }
                    else {
                        keepAdv = false;
                    }
                }
            }

            // print info
            cout << "East-bound cars advanced on yellow: " << numGoneEast
                 << " Remaining queue: " << eastQueue.getNumElems() << endl;
            cout << "West-bound cars advanced on yellow: " << numGoneWest
                 << " Remaining queue: " << westQueue.getNumElems() << endl;

            scheduleLightChange();
        }
        else if (handleType == EVENT_CHANGE_YELLOW_NS) {
            int totalCanPass = northSouthGreenTime;
            int numGoneNorth = 0;
            int numGoneSouth = 0;
            CarClass passingCar;

            // change light 
            currentLight = LIGHT_YELLOW_NS;

            // print
            cout << "\nHandling " << eventToHandle << endl;
            cout << "Advancing cars on north-south green" << endl;

            // Car passig during green
            while (numGoneNorth < totalCanPass && 
                   northQueue.dequeue(passingCar)) {
                numGoneNorth++;
                numTotalAdvancedNorth++;
                cout << "  Car #" << passingCar.getId() 
                     << " advances north-bound" << endl;
            }
            while (numGoneSouth < totalCanPass && 
                   southQueue.dequeue(passingCar)) {
                numGoneSouth++;
                numTotalAdvancedSouth++;
                cout << "  Car #" << passingCar.getId() 
                     << " advances south-bound" << endl;
            }
            cout << "North-bound cars advanced on green: " << numGoneNorth
                 << " Remaining queue: " << northQueue.getNumElems() << endl;
            cout << "South-bound cars advanced on green: " << numGoneSouth
                 << " Remaining queue: " << southQueue.getNumElems() << endl;
            
            scheduleLightChange();
        }
        else if (handleType == EVENT_CHANGE_GREEN_EW) {
            int totalCouldPass = northSouthYellowTime;
            bool keepAdv = true;
            bool doNextAdv;
            int numGoneNorth = 0;
            int numGoneSouth = 0;
            CarClass passingCar;

            // change light 
            currentLight = LIGHT_GREEN_EW;

            // print
            cout << "\nHandling " << eventToHandle << endl;
            cout << "Advancing cars on north-south yellow" << endl;

            // north
            while (keepAdv) {
                if (!northQueue.getNumElems()) {
                    cout << "  No north-bound cars waiting to advance "
                         << "on yellow" << endl;
                    keepAdv = false;
                }
                else {
                    if (numGoneNorth < totalCouldPass) {
                        // generate random number
                        int random = getUniform(UNIF_LOWER_BOUND, 
                                                UNIF_UPPER_BOUND);
                        doNextAdv = random < percentCarsAdvanceOnYellow;

                        if (doNextAdv) {
                            northQueue.dequeue(passingCar);
                            numGoneNorth++;
                            numTotalAdvancedNorth++;

                            // print info
                            cout << "  Next north-bound car will advance "
                                 << "on yellow" << endl;
                            cout << "  Car#" << passingCar.getId() 
                                 << " advances north-bound" << endl;
                        }
                        else {
                            cout << "  Next north-bound car will NOT advance "
                                 << "on yellow" 
                                 << endl;
                            keepAdv = false;
                        }
                    }
                    else {
                        keepAdv = false;
                    }
                }
            }

            // south
            keepAdv = true;
            while (keepAdv) {
                if (!southQueue.getNumElems()) {
                    cout << "  No south-bound cars waiting to advance "
                         << "on yellow" << endl;
                    keepAdv = false;
                }
                else {
                    if (numGoneSouth < totalCouldPass) {
                        // generate random number
                        int random = getUniform(UNIF_LOWER_BOUND, 
                                                UNIF_UPPER_BOUND);
                        doNextAdv = random < percentCarsAdvanceOnYellow;

                        if (doNextAdv) {
                            southQueue.dequeue(passingCar);
                            numGoneSouth++;
                            numTotalAdvancedSouth++;

                            // print info
                            cout << "  Next south-bound car will advance "
                                 << "on yellow" << endl;
                            cout << "  Car#" << passingCar.getId() 
                                 << " advances south-bound" << endl;
                        }
                        else {
                            cout << "  Next south-bound car will NOT advance "
                                 << "on yellow" 
                                 << endl;
                            keepAdv = false;
                        }
                    }
                    else {
                        keepAdv = false;
                    }
                }
            }

            // print info
            cout << "North-bound cars advanced on yellow: " << numGoneNorth
                 << " Remaining queue: " << northQueue.getNumElems() << endl;
            cout << "South-bound cars advanced on yellow: " << numGoneSouth
                 << " Remaining queue: " << southQueue.getNumElems() << endl;

            scheduleLightChange();
        }
    }
    return doHandleNext;
}

void IntersectionSimulationClass::printStatistics() const {
    cout << "===== Begin Simulation Statistics =====" << endl;
    cout << "  Longest east-bound queue: " << maxEastQueueLength << endl;
    cout << "  Longest west-bound queue: " << maxWestQueueLength << endl;
    cout << "  Longest north-bound queue: " << maxNorthQueueLength << endl;
    cout << "  Longest south-bound queue: " << maxSouthQueueLength << endl;
    cout << "  Total cars advanced east-bound: " << 
            numTotalAdvancedEast << endl;
    cout << "  Total cars advanced west-bound: " << 
            numTotalAdvancedWest << endl;
    cout << "  Total cars advanced north-bound: " << 
            numTotalAdvancedNorth << endl;
    cout << "  Total cars advanced south-bound: " << 
            numTotalAdvancedSouth << endl;
    cout << "===== End Simulation Statistics =====" << endl;
}