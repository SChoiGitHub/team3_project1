/**
*	@author Team 3
*	@date 
*	@file main.cpp
*	@brief driver for project
*/
#include <iostream>
#include "io.h"
#include "log.h"
#include "interface.h"

int main(int argc, char **argv)
{
	
	IO<void> io("event.list");

	Log<void> logFile;
	
	logFile.addEntry("Seg fault", "main");
	
	logFile.addEntry("Some sort of fault", "main");

	Log<void> fr;

	fr.addEntry("Some sort of fault", "main");

	return (0);
}

