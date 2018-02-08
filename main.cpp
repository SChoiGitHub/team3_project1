/**
*	@author Team 3
*	@date
*	@file main.cpp
*	@brief driver for project
*/
#include <iostream>
#include "interface.h"
#include "io.h"
#include "log.h"
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


	//IO io("event.list");

	//io.updateElement(0,"total_attendees", NULL);
	//io.updateElement(0,"attendees", (char *) "peter");

	//io.updateElement(1,"total_attendees", NULL);
	//io.updateElement(1,"attendees", (char *) "peter");
	//std::cout << io.size << std::endl;

	//std::cout << "Number of lines in events file (number of events): " << io.size << std::endl;

	//std::cout << io.retrieveElement(0,"date") << std::endl;

	/*Log logFile;

	logFile.addEntry("Seg fault", "main");

	logFile.addEntry("Some sort of fault", "main");

	Log fr;

	fr.addEntry("Some sort of fault", "main");
*/
	//std::cout << io.size << std::endl;

	return (0);
}
