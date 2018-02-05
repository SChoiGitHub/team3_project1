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

	std::string month = "";
	int day = 0;
	int year = 0;
	bool dateIsCorrect = true;
	bool dateIsAvailable = true;
	bool isLeapYear = true;

	char addMoreSlots = false;
	std::string timeSlot;

	std::cout << "Enter event name: ";
	std::getline(std::cin, eventName);

	do {
		dateIsCorrect = true;
		dateIsAvailable = true;
		isLeapYear = true;

		std::cout << "Enter date in MM/DD/YYYY format: ";
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
		} else {
			month = date.substr(0,2);
			//std::cout << month << " \n";
			day = std::stoi(date.substr(3,2));
			//std::cout << day << " \n";
			year = std::stoi(date.substr(6,4));
			//std::cout << year << " \n";

			if ((year%4 != 0) || ((year%100 == 0) && (year%400 != 0))) {
				//std::cout << "This is not a leap year.\n";
				isLeapYear = false;
			}

			if ((month == "02") && (isLeapYear) && (day > 29)) {
				std::cout << "Error 9\n";
				dateIsCorrect = false;
			} else if ((month == "02") && (!isLeapYear) && (day > 28)) {
				std::cout << "Error 10\n";
				dateIsCorrect = false;
			} else if (((month == "04") || (month == "06") || (month == "09") || (month == "11")) && (day > 30)) {
				std::cout << "Error 11\n";
				dateIsCorrect = false;
			}

			if (((month == "01") && (day == 1)) || ((month == "07") && (day == 4)) || ((month == "12") && (day == 25))) {
				dateIsAvailable = false;
			}
		}

		if (!dateIsCorrect) {
			std::cout << "Wrong input! Please enter a valid date in MM/DD/YYYY format.\n";
		}

		if (!dateIsAvailable) {
			std::cout << "Sorry, that day is not available. Please enter a different date.\n";
		}

	} while (!dateIsCorrect || !dateIsAvailable);

	//std::cout << "Your date is: " << date << '\n';

	do {
		/*do {
			std::cout << "Enter start time of a 20-minute time slot: ";
			std::getline(std::cin,timeSlot);

		} while(1);*/

		std::cout << "Do you want to add more slots?\n"
							<< "To add more slots, type 'y'\n"
							<< "To quit, type any other character\n"
							<< "Choice: ";
		std::cin >> addMoreSlots;
		std::cin.ignore(1, '\n');
	} while (addMoreSlots == 'y');


	std::cout << "Attendees: admin" << std::endl;

	//Add all string together with comma delimiter, line in event.list format, and then put it in io.new_line
	//io.new_line = ...
	
	io.addEntry();
}



















































































