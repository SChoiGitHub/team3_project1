#	Author: Team 3
#	Date: 


.PHONY: main main.o clean 

main: main.o 
	g++ -g -Wall -std=c++11 main.o -o main


main.o: main.cpp io.h log.h interface.h events.h
	g++ -g -Wall -std=c++11 -c main.cpp



clean:
	rm *.o main || true
