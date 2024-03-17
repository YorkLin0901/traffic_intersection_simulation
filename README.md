# Traffic Intersection Simulation Project

## Overview

This project is an event-driven simulation of traffic flow through a 4-way intersection managed by a traffic light. The simulation includes cars arriving at the intersection from all four directions and the light changing state throughout the simulation. After the simulation is complete, some statistics about the traffic flow are output.

## Detailed Description

The project is split into two phases:

1. **Phase 1:** Update the `SortedListClass` and `FIFOQueueClass` from project 4 to be templated classes, allowing them to hold more data types than just integers.
2. **Phase 2:** Develop the event-driven simulation of cars traveling through an intersection managed by a functioning traffic light.

## File Structure

- `CarClass.cpp`, `CarClass.h`
- `EventClass.cpp`, `EventClass.h`
- `IntersectionSimulationClass.cpp`, `IntersectionSimulationClass.h`
- `LinkedNodeClass.h`, `LinkedNodeClass.inl`
- `FIFOQueueClass.h`, `FIFOQueueClass.inl`
- `SortedListClass.h`, `SortedListClass.inl`
- `constants.h`
- `random.cpp`, `random.h`
- `simulation.cpp`
- `Makefile`
- Sample output: `typescript`

## Implementation and Design

- The project uses C++ templates to create generic data structures.
- The event-driven simulation is the core of the project, handling events such as car arrivals and traffic light changes.
- Statistics are maintained throughout the simulation, including queue lengths and the number of cars advancing through the intersection in each direction.

## How to Build and Run

1. Ensure all .h, .cpp, .inl files, and the Makefile are in the same directory.
2. Open a terminal in that directory.
3. Run `make` to compile the project.
4. Execute the program with the appropriate command line arguments.

## Notes

- This project is part of EECS402 Fall 2023 at the University of Michigan.
- The implementation is based on the specifications provided in the original project description.
