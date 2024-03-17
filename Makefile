all: proj5.exe

CarClass.o: CarClass.h CarClass.cpp constants.h
	g++ -std=c++98 -Wall -c CarClass.cpp -o CarClass.o

EventClass.o: EventClass.h EventClass.cpp constants.h
	g++ -std=c++98 -Wall -c EventClass.cpp -o EventClass.o

IntersectionSimulationClass.o: IntersectionSimulationClass.h IntersectionSimulationClass.cpp constants.h SortedListClass.h EventClass.h FIFOQueueClass.h CarClass.h random.h 
	g++ -std=c++98 -Wall -c IntersectionSimulationClass.cpp -o IntersectionSimulationClass.o

random.o: random.h random.cpp constants.h
	g++ -std=c++98 -Wall -c random.cpp -o random.o

project5.o: project5.cpp IntersectionSimulationClass.h
	g++ -std=c++98 -Wall -c project5.cpp -o project5.o

proj5.exe: CarClass.o EventClass.o IntersectionSimulationClass.o random.o project5.o 
	g++ -std=c++98 -Wall CarClass.o EventClass.o IntersectionSimulationClass.o random.o project5.o -o proj5.exe
	
clean:
	rm -f *.o *.exe

