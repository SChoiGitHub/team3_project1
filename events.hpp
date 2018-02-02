/**
*	@author Team 3
*	@date 
*	@file events.hpp
*/

void Events::userMode()
{
	Interface::Menu menu({
		{"Set Availability", Events::setAvailability},
		{"Toggle Time Format 12/24", Interface::toggleTimeFormat},
		{"Go back", nullptr}
	});

	menu.Loop();
}

void Events::adminMode()
{
	Interface::Menu menu({
		{"Add Event", Events::createEvent},
		{"Toggle Time Format 12/24", Interface::toggleTimeFormat},
		{"Go back", nullptr}
	});

	menu.Loop();
}

void Events::setAvailability()
{
	
}

void Events::createEvent()
{
	std::cout << "Enter event name: ";
	std::getline(eventName);
	std::cout << "Enter date: ";
	std::getline(date);
	std::cout << "Enter time slot: ";
	std::getline(timeSlot);
	std::cout << "Attendees";
}



