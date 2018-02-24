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
	//std::fstream file("event.list",std::ios::out);
	//file.close();

	//IO io("event.list");
	//Initiate a menu object with the 3 options specified
	Interface::Menu menu({
		{"Enter UserMode", Events::userMode},
		{"Enter AdminMode", Events::adminMode},
		{"Exit", nullptr}
	});
	//Enter menu loop
	menu.Loop();	


	return (0);
}
