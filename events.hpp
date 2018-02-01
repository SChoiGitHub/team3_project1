/**
*	@author Team 3
*	@date 
*	@file events.hpp
*/

void Events::userMode()
{
	
}

void Events::adminMode()
{
	Interface::Menu menu({
		{"Add Event", IO::addEntry},
		{"Toggle Time Format 12/24", Interface::toggleTimeFormat},
		{"Go back", nullptr}
	});

	menu.Loop();
}
