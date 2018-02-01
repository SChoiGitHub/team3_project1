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
#include "events.h"

int main(int argc, char **argv)
{

	//Initiate a menu object with the 3 options specified
	Interface::Menu menu({
		{"Enter UserMode", Events::userMode},
		{"Enter AdminMode", Events::adminMode},
		{"Exit", nullptr}
	});
	//Enter menu loop
	menu.Loop();

	
	
	IO io("event.list");

	Log logFile;
	
	logFile.addEntry("Seg fault", "main");
	
	logFile.addEntry("Some sort of fault", "main");

	Log fr;

	fr.addEntry("Some sort of fault", "main");

	return (0);
}

