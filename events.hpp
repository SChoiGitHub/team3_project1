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
	IO io("event.list");
	
	std::string eventName;
	std::string date;
	std::string timeSlot;
	
	std::cout << "Enter event name: ";
	std::getline(std::cin,eventName);
	std::cout << "Enter date: ";
	std::getline(std::cin,date);
	std::cout << "Enter time slot: ";
	std::getline(std::cin,timeSlot);
	std::cout << "Attendees";

	//Add all string together with comma delimiter, line in event.list format, and then put it in io.new_line
	//io.new_line = ...
	
	io.addEntry();
}



