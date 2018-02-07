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
	
	std::string outputString = "";
	std::string adminName = "";
	std::string eventName = "";

	std::string date = "";
	std::string month = "";
	int day = 0;
	int year = 0;
	bool dateIsCorrect = true;
	bool dateIsAvailable = true;
	bool isLeapYear = true;

	std::cout << "Enter your name: ";
	std::getline(std::cin, adminName);

	std::cout << "Enter event name: ";
	std::getline(std::cin, eventName);
	outputString += (eventName + ",");

	do {
		dateIsCorrect = true;
		dateIsAvailable = true;
		isLeapYear = true;

		std::cout << "Enter date in MM/DD/YYYY format: ";
		std::getline(std::cin, date);

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
				//std::cout << "Error 9\n";
				dateIsCorrect = false;
			} else if ((month == "02") && (!isLeapYear) && (day > 28)) {
				//std::cout << "Error 10\n";
				dateIsCorrect = false;
			} else if (((month == "04") || (month == "06") || (month == "09") || (month == "11")) && (day > 30)) {
				//std::cout << "Error 11\n";
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
			std::cout << "Sorry, that day is not available for meetings. Please enter a different date.\n";
		}

	} while ((!dateIsCorrect) || (!dateIsAvailable));

	std::cout << "Succesful addition of the date " << date << '\n';
	outputString += (date + ",");

	char addMoreSlots = false;
	std::string timeSlot = "";
	int amountOfSlots = 0;

	int hour = -1;
	int minute = -1;
	int index = 0;
	bool timeSlotFormatIsCorrect = false;
	bool timeSlotHourAndMinuteAreCorrect = false;
	bool timeSlotIsAvailable = true;
	bool successfulAddition = false;

	std::string stringOfTimeSlots = "";
	int timeInMins = 0;
	int slotStart = 0;
	int slotEnd = 0;
	std::pair<int,int> newSlot(0,0);

	std::list<std::pair<int,int>> slotsList;
	slotsList.push_back(std::pair<int,int>(0,300));
	slotsList.push_back(std::pair<int,int>(720,780));

	for(auto itr = slotsList.begin(); itr != slotsList.end(); itr++) {
		std::cout << "<" << itr->first << ", " << itr->second << "> ";
	}
	std::cout << std::endl;

	do {
		do {
			hour = -1;
			minute = -1;
			index = 0;
			timeSlotFormatIsCorrect = false;
			timeSlotHourAndMinuteAreCorrect = false;
			timeSlotIsAvailable = true;
			successfulAddition = false;

			std::cout << "Enter start time of a 20-minute time slot: ";
			std::getline(std::cin,timeSlot);

			index = timeSlot.find(':');

			//DEBUGGING CODE
			/*std::cout << "index: " << index << '\n';
			std::cout << "First substring of length " << timeSlot.substr(0,index).length() << ": " << timeSlot.substr(0,index) << '\n';
			if (timeSlot.substr(0,index).find_first_not_of("0123456789") != std::string::npos) {
				std::cout << "First not of: " << timeSlot.substr(0,index).find_first_not_of("0123456789") << '\n';
			} else {
				std::cout << "First not of: " << "npos\n";
			}
			std::cout << "Second substring of length " << timeSlot.substr(index+1).length() << ": " << timeSlot.substr(index+1) << '\n';
			if (timeSlot.substr(index + 1).find_first_not_of("0123456789") != std::string::npos) {
				std::cout << "First not of: " << timeSlot.substr(index + 1).find_first_not_of("0123456789") << '\n';
			} else {
				std::cout << "First not of: " << "npos\n";
			}*/
			//END OF DEBUGGING CODE

			if (index != std::string::npos) {
				try {
					hour = std::stoi(timeSlot.substr(0,index));
				} catch(std::invalid_argument& e) {
					std::cout << "Invalid argument.\n";
					continue;
				} catch(std::out_of_range& e) {
					std::cout << "Out of range.\n";
					continue;
				} catch(...) {
					std::cout << "Other error.\n";
					continue;
				}
				//std::cout << "hour: " << hour << '\n';

				try {
					minute = std::stoi(timeSlot.substr(index + 1));
				} catch(std::invalid_argument& e) {
					std::cout << "Invalid argument.\n";
					continue;
				} catch(std::out_of_range& e) {
					std::cout << "Out of range.\n";
					continue;
				} catch(...) {
					std::cout << "Other error.\n";
					continue;
				}
				//std::cout << "minute: " << minute << '\n';

				if (((timeSlot.substr(0,index)).find_first_not_of("0123456789") == std::string::npos)
				&& ((timeSlot.substr(index + 1)).find_first_not_of("0123456789") == 2)) {
					//std::cout << "This is a 12 hour format.\n";
					//If the length is 6 or 7 and no extra; disallows things like 2:03amp
					if ((timeSlot.length() == 6) || ((timeSlot.length() == 7) && ((timeSlot.substr(index + 1)).length() == 4))) {
						int lastIndex = timeSlot.length() - 1;
						int secondToLastIndex = lastIndex - 1;
						//std::cout << "At last index: " << timeSlot[lastIndex] << '\n';
						//std::cout << "At second to last index: " << timeSlot[secondToLastIndex] << '\n';
						if ((timeSlot[lastIndex] == 'm') && ((timeSlot[secondToLastIndex] == 'a') || (timeSlot[secondToLastIndex] == 'p'))) {
							timeSlotFormatIsCorrect = true;
						}
						//Converting to 24-hr format:::
						timeSlot = io.timeFormatter("timeSlot");
						hour = std::stoi(timeSlot.substr(0,index));
						minute = std::stoi(timeSlot.substr(index + 1));
					}
				} else if (((timeSlot.substr(0,index)).find_first_not_of("0123456789") == std::string::npos)
				&& ((timeSlot.substr(index + 1)).find_first_not_of("0123456789") == std::string::npos)) {
					//std::cout << "This is a 24 hour format.\n";
					if ((timeSlot.length() == 4) || ((timeSlot.length() == 5))) {
						timeSlotFormatIsCorrect = true;
					}
				} else {
					std::cout << "Format is incorrect.\n";
					continue;
				}

				//---------IMPORTANT double check conditions and couts

				if((timeSlotFormatIsCorrect) && ((hour <= 23) && (hour >= 0)) && ((minute <= 59) && (minute >= 0))){
					timeSlotHourAndMinuteAreCorrect = true;
				}

				//Assuming we have a correctly-formatted 24-hour time:
				if ((timeSlotHourAndMinuteAreCorrect) && (timeSlotFormatIsCorrect)) {
					timeInMins = (hour * 60) + minute;
					std::cout << "Time in minutes: " << timeInMins << '\n';
					//No events can be created after 11:40pm (aka 1420)
					if ((timeInMins >= 1420) || ((timeInMins >= 0) && (timeInMins <= 300))) {
						timeSlotIsAvailable = false;
						std::cout << "Sorry, you cannot create a meeting between 12:00 am and 5:00 am. Please pick a different time.\n";
						continue;
					} else if ((timeInMins >= 720) && (timeInMins <= 780))  {
						timeSlotIsAvailable = false;
						std::cout << "Sorry, you cannot create a meeting between 12:00 pm and 1:00 pm. Please pick a different time.\n";
						continue;
					}

					slotStart = timeInMins;
					slotEnd = timeInMins + 20;
					newSlot = {slotStart, slotEnd};
					//std::cout << "New pair: <" << newSlot.first << ", " << newSlot.second << ">\n";

					for (auto itr = slotsList.begin(); itr != slotsList.end(); itr++) {
						if (newSlot.first >= itr->second) {
							itr++;
							if (itr == slotsList.end()) {
								successfulAddition = true;
								//std::cout << "We're at end. Inserting at end...\n";
								slotsList.push_back(newSlot);
								break;
							} else {
								itr--;
								//std::cout << newSlot.first << " >= " << itr->second << " continuing..\n";
								continue;
							}
						} else {
							if (newSlot.second > itr->first) {
								//std::cout << newSlot.second << " > " << itr->first << " ";
								timeSlotIsAvailable = false;
								std::cout << "Sorry, cannot add slot because there is a scheduling conflict. Please pick a different time.\n";
								break;
							} else {
								successfulAddition = true;
								//std::cout << newSlot.second << " <= " << itr->first << " ";
								//std::cout << "Adding newSlot in previous position!\n";
								slotsList.insert(itr, newSlot);
								break;
							}
						}
					}

					/*for(auto itr = slotsList.begin(); itr != slotsList.end(); itr++) {
						std::cout << "<" << itr->first << ", " << itr->second << "> ";
					}
					std::cout << std::endl;*/
				}
			} else {
				std::cout << "No colon.\n";
				continue;
			}

			if (!timeSlotHourAndMinuteAreCorrect) {
				std::cout << "Hour and/or minutes are off bounds.\n";
			}
			if (!timeSlotFormatIsCorrect) {
				std::cout << "Time slot format is not correct. Please enter a time in either 12 hour mode (e.g. 1:15pm) or 24 hour mode (e.g. 13:15).\n";
			}
			if (successfulAddition) {
				amountOfSlots++;
				//Converting to 12-hr format:::
				timeSlot = io.timeFormatter("timeSlot");
				stringOfTimeSlots += timeSlot + ",1,";
				std::cout << "Your " << timeSlot << " time slot was successfully added!\n";
			}
		} while((!timeSlotIsAvailable) || (!timeSlotHourAndMinuteAreCorrect) || (!timeSlotFormatIsCorrect));

		std::cout << "Do you want to add more slots?\n"
							<< "To add more slots, type 'y'\n"
							<< "To quit, type any other character\n"
							<< "Choice: ";
		std::cin >> addMoreSlots;
		std::cin.ignore(1, '\n');
	} while (addMoreSlots == 'y');

	outputString += (stringOfTimeSlots + std::to_string(amountOfSlots) + "," + adminName);
	std::cout << outputString << std::endl;

	//Add all string together with comma delimiter, line in event.list format, and then put it in io.new_line
	//io.new_line = ...
	
	io.addEntry(outputString);
}



