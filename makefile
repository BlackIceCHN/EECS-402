proj4.exe: p4Final.o SimulationClass.o EventTypeClass.o random.o
	g++ p4Final.o SimulationClass.o EventTypeClass.o random.o -o proj4.exe

p4Final.o: SimulationClass.o EventTypeClass.o random.o
	g++ -c proj4.cpp -o p4Final.o

random.o: random.h random.cpp
	g++ -c random.cpp -o random.o

SimulationClass.o: SimulationClass.h random.o SimulationClass.cpp
	g++ -c SimulationClass.cpp -o SimulationClass.o

EventTypeClass.o: EventTypeClass.h EventTypeClass.cpp
	g++ -c EventTypeClass.cpp -o EventTypeClass.o

clean:
	rm -f proj4.exe random.o EventTypeClass.o SimulationClass.o 


