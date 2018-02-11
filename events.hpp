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
	Interface interface_;
	IO io_("event.list");
	bool digit_flag = true;
	bool new_attendee = false;
	int dummy_int = 0;

	if( io_.size != 0 )
	{
		std::string input = interface_.getInput("Please select an event ID from the list above: ");

		for(unsigned int i = 0; i < input.size() ; ++i)
			if( isdigit(input[i]) == 0 )
				digit_flag = false;

		if(digit_flag == true)
		{
			int input_ = atoi(input.c_str());

			if( input_ < 0 || input_ > io_.size - 1)
			{
				std::cout << "Invalid event ID." << std::endl;
				interface_.Wait("");
			}
			else
			{
				input = io_.retrieveElement(input_,"total_slots");
				dummy_int = atoi(input.c_str());
				input = io_.retrieveElement(input_,"slots");

				std::string slots[dummy_int];
				std::string dummy_string;
				std::stringstream ss(input);

				for(int i = 0; i < dummy_int ; ++i)
				{
					//Get slots
					getline(ss, slots[i], ',');
					//Just to move the string forward (over the number of people in a slot)
					getline(ss, input, ',');

					dummy_string = "slot" + std::to_string(i+1);

					if(io_.timeFormat == true )
						std::cout << "Are you available at " << slots[i] << " ? [Y/n]: ";
					else
						std::cout << "Are you available at " << io_.timeFormatter(slots[i]) << " ? [Y/n]: ";

					getline(std::cin, input);

					if(input == "Yes" || input == "yes" || input == "y" || input == "Y")
					{
						io_.updateElement(input_,dummy_string,NULL);
						new_attendee = true;
					}
					else if(input != "No" && input != "no" && input != "n" && input != "N")
					{
						std::cout << "Invalid input. Please try again." << std::endl;

						ss.clear();
						ss.seekg(0, std::ios::beg);

						for(int j = 0; j < 2*i ; ++j)
							getline(ss, input, ',');

						--i;
					}
				}

				if(new_attendee == true)
				{
					std::string name = interface_.getInput("What's your name? ");
					const char* name_ = name.c_str();
					io_.updateElement(input_,"total_attendees",NULL);
					io_.updateElement(input_,"attendees", (char *) name_);
				}
			}
		}
		else
		{
			std::cout << "Invalid event ID." << std::endl;
			interface_.Wait("");
		}

	} else {
		interface_.Wait("No events available... Sorry!");
	}
}

void Events::createEvent()
{
	Interface interface_;
	Interface::Menu menu({{"", NULL}});

	IO io("event.list");


	time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	int current_year = (int)timePtr->tm_year + 1900;
	int current_month = (int) timePtr->tm_mon + 1;
	int current_day = (int) timePtr->tm_mday;

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

	int amountOfAtendees = 1;

	interface_.clearScreen();
	menu.Header();

	std::cout << "\nEnter your name: ";
	std::getline(std::cin, adminName);

	std::cout << "\nEnter event name: ";
	std::getline(std::cin, eventName);

	do {
		dateIsCorrect = true;
		dateIsAvailable = true;
		isLeapYear = true;

		std::cout << "\nEnter date in MM/DD/YYYY format: ";
		std::getline(std::cin, date);

		if (date.length() != 10) {
			dateIsCorrect = false;
		} else if ((date[0] != '0') && (date[0] != '1')) {
			dateIsCorrect = false;
		} else if ((date[0] == '0') && ((date[1] == '0') || (!isdigit(date[1])))) {
			dateIsCorrect = false;
		} else if ((date[0] == '1') && (date[1] != '0') && (date[1] != '1') && (date[1] != '2')) {
			dateIsCorrect = false;
		} else if (date[2] != '/') {
			dateIsCorrect = false;
		} else if ((date[3] != '0') && (date[3] != '1') && (date[3] != '2') && (date[3] != '3')) {
			dateIsCorrect = false;
		} else if (((date[3] == '0') || (date[3] == '1') || (date[3] == '2')) && (!isdigit(date[4]))) {
			dateIsCorrect = false;
		} else if ((date[3] == '3') && (date[4] != '0') && (date[4] != '1')) {
			dateIsCorrect = false;
		} else if (date[5] != '/') {
			dateIsCorrect = false;
		} else if((!isdigit(date[6])) || (!isdigit(date[7])) || (!isdigit(date[8])) || (!isdigit(date[9]))) {
			dateIsCorrect = false;
		} else {
			month = date.substr(0,2);
			day = std::stoi(date.substr(3,2));
			year = std::stoi(date.substr(6,4));

			if ((year%4 != 0) || ((year%100 == 0) && (year%400 != 0))) {
				isLeapYear = false;
			}

			if ((month == "02") && (isLeapYear) && (day > 29)) {
				dateIsCorrect = false;
			} else if ((month == "02") && (!isLeapYear) && (day > 28)) {
				dateIsCorrect = false;
			} else if (((month == "04") || (month == "06") || (month == "09") || (month == "11")) && (day > 30)) {
				dateIsCorrect = false;
			}

			if (((month == "01") && (day == 1)) || ((month == "07") && (day == 4)) || ((month == "12") && (day == 25))) {
				dateIsAvailable = false;
			}

			if(current_year > year || ( current_year == year && current_month > atoi(month.c_str()) ) || ( current_year == year && current_month == atoi(month.c_str()) && current_day > day) )
			{
				dateIsCorrect = false;
			}
		}

		if (!dateIsCorrect) {
			interface_.clearScreen();
			menu.Header();
			std::cout << "\nWrong input! Please enter a valid date in MM/DD/YYYY format.\n";
		}

		if (!dateIsAvailable) {
			interface_.clearScreen();
			menu.Header();
			std::cout << "\nSorry, that day is not available for meetings. Please enter a different date.\n";
		}

	} while ((!dateIsCorrect) || (!dateIsAvailable));

	std::cout << "Succesful addition of the date " << date << ".\n";

	char userChoice = false;
	std::string timeSlot = "";
	int amountOfSlots = 0;

	int hour = -1;
	int minute = -1;
	unsigned int index = 0;
	bool timeSlotFormatIsCorrect = false;
	bool timeSlotHourAndMinuteAreCorrect = false;
	bool timeSlotIsAvailable = true;
	bool successfulAddition = false;

	std::string stringOfTimeSlots = "";
	int timeInMins = 0;
	int slotStart = 0;
	int slotEnd = 0;
	std::pair<int,int> newSlot(0,0);
	std::string createdTimeSlots = "";

	std::list<std::pair<int,int>> slotsList;
	slotsList.push_back(std::pair<int,int>(0,300));
	slotsList.push_back(std::pair<int,int>(720,780));


	do {
		do {
			hour = -1;
			minute = -1;
			index = 0;
			timeSlotFormatIsCorrect = false;
			timeSlotHourAndMinuteAreCorrect = false;
			timeSlotIsAvailable = true;
			successfulAddition = false;

			std::cout << "\nEnter start time of a 20-minute time slot: ";
			std::getline(std::cin,timeSlot);

			index = timeSlot.find(':');


			if (index != std::string::npos) {
				try {
					hour = std::stoi(timeSlot.substr(0,index));
				} catch(std::invalid_argument& e) {
					interface_.clearScreen();
					menu.Header();
					std::cout << "\nInvalid argument.\n";
					continue;
				} catch(std::out_of_range& e) {
					interface_.clearScreen();
					menu.Header();
					std::cout << "\nOut of range.\n";
					continue;
				} catch(...) {
					interface_.clearScreen();
					menu.Header();
					std::cout << "\nOther error.\n";
					continue;
				}


				try {
					minute = std::stoi(timeSlot.substr(index + 1));
				} catch(std::invalid_argument& e) {
					interface_.clearScreen();
					menu.Header();
					std::cout << "\nInvalid argument.\n";
					continue;
				} catch(std::out_of_range& e) {
					interface_.clearScreen();
					menu.Header();
					std::cout << "\nOut of range.\n";
					continue;
				} catch(...) {
					interface_.clearScreen();
					menu.Header();
					std::cout << "\nOther error.\n";
					continue;
				}


				if (((timeSlot.substr(0,index)).find_first_not_of("0123456789") == std::string::npos)
				&& ((timeSlot.substr(index + 1)).find_first_not_of("0123456789") == 2)) {

					//If the length is 6 or 7 and no extra; disallows things like 2:03amp
					if ((timeSlot.length() == 6) || ((timeSlot.length() == 7) && ((timeSlot.substr(index + 1)).length() == 4))) {
						int lastIndex = timeSlot.length() - 1;
						int secondToLastIndex = lastIndex - 1;

						if ((timeSlot[lastIndex] == 'm') && ((timeSlot[secondToLastIndex] == 'a') || (timeSlot[secondToLastIndex] == 'p'))) {
							timeSlotFormatIsCorrect = true;
						}

						//Converting to 24-hr format:::
						timeSlot = io.timeFormatter(timeSlot);

						index = timeSlot.find(':');
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
					interface_.clearScreen();
					menu.Header();
					std::cout << "\nFormat is incorrect.\n";
					continue;
				}

				//---------IMPORTANT double check conditions and couts

				if((timeSlotFormatIsCorrect) && ((hour <= 23) && (hour >= 0)) && ((minute <= 59) && (minute >= 0))){
					timeSlotHourAndMinuteAreCorrect = true;
				}

				//Assuming we have a correctly-formatted 24-hour time:
				if ((timeSlotHourAndMinuteAreCorrect) && (timeSlotFormatIsCorrect)) {
					timeInMins = (hour * 60) + minute;
					//std::cout << "Time in minutes: " << timeInMins << '\n';
					//No events can be created after 11:40pm (aka 1420)
					if ((timeInMins >= 1420) || ((timeInMins >= 0) && (timeInMins <= 300))) {
						interface_.clearScreen();
						menu.Header();
						timeSlotIsAvailable = false;
						std::cout << "\nSorry, you cannot create a meeting between 12:00 am and 5:00 am. Please pick a different time.\n";
						continue;
					} else if ((timeInMins >= 720) && (timeInMins <= 780))  {
						interface_.clearScreen();
						menu.Header();
						timeSlotIsAvailable = false;
						std::cout << "\nSorry, you cannot create a meeting between 12:00 pm and 1:00 pm. Please pick a different time.\n";
						continue;
					}

					slotStart = timeInMins;
					slotEnd = timeInMins + 20;
					newSlot = {slotStart, slotEnd};

					for (auto itr = slotsList.begin(); itr != slotsList.end(); itr++) {
						if (newSlot.first >= itr->second) {
							itr++;
							if (itr == slotsList.end()) {
								successfulAddition = true;

								slotsList.push_back(newSlot);
								break;
							} else {
								itr--;

								continue;
							}
						} else {
							if (newSlot.second > itr->first) {

								interface_.clearScreen();
								menu.Header();
								timeSlotIsAvailable = false;
								std::cout << "\nSorry, cannot add that slot because there is a scheduling conflict. Please pick a different time.\n";
								break;
							} else {
								successfulAddition = true;

								slotsList.insert(itr, newSlot);
								break;
							}
						}
					}


				}
			} else {
				std::cout << "No colon.\n";
				continue;
			}

			if (!timeSlotHourAndMinuteAreCorrect) {
				interface_.clearScreen();
				menu.Header();
				std::cout << "\nHour and/or minutes are off bounds.\n";
			}
			if (!timeSlotFormatIsCorrect) {
				interface_.clearScreen();
				menu.Header();
				std::cout << "\nTime slot format is not correct. Please enter a time in either 12 hour mode (e.g. 1:15pm) or 24 hour mode (e.g. 13:15).\n";
			}
			if (successfulAddition) {
				amountOfSlots++;

				//Converting slot end time to 24-hr mode (temporarily):
				int hourEndTime = slotEnd / 60;
				int minuteEndTime = slotEnd % 60;
				std::string timeSlotEnd = "";
				if (hourEndTime < 10) {
					timeSlotEnd += "0";
				}
				timeSlotEnd = (std::to_string(hourEndTime) + ":");
				if (minuteEndTime < 10) {
					timeSlotEnd += "0";
				}
				timeSlotEnd += std::to_string(minuteEndTime);

				std::string timeSlotInterval;

				if(io.timeFormat == false)
					timeSlotInterval = timeSlot + " - " + timeSlotEnd;
				else
					timeSlotInterval = io.timeFormatter(timeSlot) + " - " + io.timeFormatter(timeSlotEnd);


				createdTimeSlots += ("\n\t" + timeSlotInterval);
				std::cout << "The " << timeSlotInterval << " time slot was successfully added!\n";

				//Converting to 12-hr format:::
				timeSlot = io.timeFormatter(timeSlot);

				stringOfTimeSlots += timeSlot + ",1,";
			}
		} while((!timeSlotIsAvailable) || (!timeSlotHourAndMinuteAreCorrect) || (!timeSlotFormatIsCorrect));

		do {
			std::cout << "\nPlease select an option:\n"
						<< "\tAdd more slots: input 'a'\n"
						<< "\tView created slots: input 'v'\n"
						<< "\tExit menu: input any other key\n"
						<< "Choice: ";
			std::cin >> userChoice;
			std::cin.ignore(1, '\n');

			if (userChoice == 'v') {
				std::cout << "\nTime slots you have created so far: " << createdTimeSlots << '\n';
			}
		} while (userChoice == 'v');
	} while (userChoice == 'a');

	outputString += (std::to_string(io.size) + "," + eventName + "," + date + "," + std::to_string(amountOfSlots) + "," + stringOfTimeSlots + std::to_string(amountOfAtendees) + "," + adminName);


	io.addEntry(outputString);
}
