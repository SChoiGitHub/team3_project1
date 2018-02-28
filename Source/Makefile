# Originally Built by Team 3
# Updated by Team 8

src = ./Source/

.PHONY: EventScheduler.app main.o clean

EventScheduler.app: main.o
	g++ -Wall -std=c++11 main.o -o EventScheduler



main.o: main.cpp log.h events.h io.h interface.h
	g++ -Wall -std=c++11 -c main.cpp

clean:
	rm *.o EventScheduler.app || true
