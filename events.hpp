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
	bool dateIsCorrect = true;
	std::string timeSlot;
	
	std::cout << "Enter event name: ";
	std::getline(std::cin, eventName);
	
	do {
		dateIsCorrect = true;
		std::cout << "Enter date: ";
		std::getline(std::cin,date);
		if (date.length() != 10) {
			//std::cout << "Error -1\n";
			dateIsCorrect = false;
		} else if ((date[0] != '0') && (date[0] != '1')) {
			//std::cout << "Error 0\n";
			dateIsCorrect = false;
		} else if ((date[0] == '0') && ((date[1] == '0') || (!isdigit(date[1])))) {
			//std::cout << "Error 1\n";
			dateIsCorrect = false;
		} else if ((date[0] == '1') && (date[1] != '0') && (date[1] != '1') && (date[1] != '2')) {
			//std::cout << "Error 2\n";
			dateIsCorrect = false;
		} else if (date[2] != '/') {
			//std::cout << "Error 3\n";
			dateIsCorrect = false;
		} else if ((date[3] != '0') && (date[3] != '1') && (date[3] != '2') && (date[3] != '3')) {
			//std::cout << "Error 4\n";
			dateIsCorrect = false;
		} else if (((date[3] == '0') || (date[3] == '1') || (date[3] == '2')) && (!isdigit(date[4]))) {
			//std::cout << "Error 5\n";
			dateIsCorrect = false;
		} else if ((date[3] == '3') && (date[4] != '0') && (date[4] != '1')) {
			//std::cout << "Error 6\n";
			dateIsCorrect = false;
		} else if (date[5] != '/') {
			//std::cout << "Error 7\n";
			dateIsCorrect = false;
		} else if((!isdigit(date[6])) || (!isdigit(date[7])) || (!isdigit(date[8])) || (!isdigit(date[9]))) {
			//std::cout << "Error 8\n";
			dateIsCorrect = false;
		}
		
		if (!dateIsCorrect) {
			std::cout << "Wrong input! Please enter a valid date in MM/DD/YYYY format.\n";
		}
		
	} while (!dateIsCorrect);
	
	std::cout << "Your date is: " << date << '\n';
	
	std::cout << "Enter time slot: ";
	std::getline(std::cin,timeSlot);
	std::cout << "Attendees: ";

	//Add all string together with comma delimiter, line in event.list format, and then put it in io.new_line
	//io.new_line = ...
	
	io.addEntry();
}



