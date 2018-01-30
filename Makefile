#	Author: 
#	Date: 


#make clean then make the exectuable by default
#standard "make clean" still works


.PHONY: main main.o clean 

main: main.o 
	g++ -g -Wall -std=c++11 main.o -o main


main.o: main.cpp io.h log.h
	g++ -g -Wall -std=c++11 -c main.cpp


#force returning true to prevent the default make from 
#	haulting when .o files aren't present
clean:
	rm *.o main || true
