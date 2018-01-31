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
	
	logFile.addEntry("12:04 - 01/12/2018", "Seg fault", "main");
	
	logFile.addEntry("13:04 - 01/13/2018", "Some sort of fault", "main");

	Log<void> fr;

	fr.addEntry("10:04 - 12/13/2018", "Some sort of fault", "main");

	return (0);
}

