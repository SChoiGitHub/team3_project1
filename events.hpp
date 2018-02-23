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

	std::size_t found;


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
					std::string name;
					do{
						found = 0;
						name = interface_.getInput("What's your name (no commas)? ");
						found = name.find_first_of(",");

					} while( found!=std::string::npos );

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

/*----------------------------Declaring variables used for input and verification of dates----------------------------*/
	std::string date = "";
	std::string month = "";
	int day = 0;
	int year = 0;
	bool dateIsCorrect = true;
	bool dateIsAvailable = true;
	bool isLeapYear = true;

	int amountOfAtendees = 1;

/*----------------------------Declaring variables used for input and verification of time slots----------------------------*/
	char userChoice = '\0';
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
	int lastIndex = 0;
	int secondToLastIndex = 0;
	int hourEndTime = 0;
	int minuteEndTime = 0;
	std::string timeSlotInterval = "";

	std::pair<int,int> newSlot(0,0);
	std::string createdTimeSlots = "";

	std::list<std::pair<int,int>> slotsList;
	slotsList.push_back(std::pair<int,int>(0,300));
	slotsList.push_back(std::pair<int,int>(720,780));

	interface_.clearScreen();
	menu.Header();

	std::size_t found;



	do{
		found = 0;
		std::cout << "\nEnter your name (no commas): ";
		std::getline(std::cin, adminName);
		found = adminName.find_first_of(",");

	} while( found!=std::string::npos );


	do{
		found = 0;
		std::cout << "\nEnter event name (no commas): ";
		std::getline(std::cin, eventName);
		found = eventName.find_first_of(",");
	}while(found!=std::string::npos );

	/*----------------------------Date input and verification----------------------------*/

	do {
		dateIsCorrect = true;
		dateIsAvailable = true;
		isLeapYear = true;

		std::cout << "\nEnter date in MM/DD/YYYY format: ";
		std::getline(std::cin, date);

		//The following if-else if-else statement discards most inputs with an incorrect format:
		//The length of the input must be 10.
		if (date.length() != 10) {
			dateIsCorrect = false;
		}
		//The first character of the month must be 0 or 1.
		else if ((date[0] != '0') && (date[0] != '1')) {
			dateIsCorrect = false;
		}
		//If the first character of the month is 0, the second character can be any integer other than 0.
		else if ((date[0] == '0') && ((date[1] == '0') || (!isdigit(date[1])))) {
			dateIsCorrect = false;
		}
		//If the first character of the month is 1, the second character must be 0, 1, or 2.
		else if ((date[0] == '1') && (date[1] != '0') && (date[1] != '1') && (date[1] != '2')) {
			dateIsCorrect = false;
		}
		//Making sure the first slash is present and is placed in the right position.
		else if (date[2] != '/') {
			dateIsCorrect = false;
		}
		//The first character of the day must be 0, 1, 2, or 3.
		else if ((date[3] != '0') && (date[3] != '1') && (date[3] != '2') && (date[3] != '3')) {
			dateIsCorrect = false;
		}
		//If the first character of the day is 0 the second character can be any integer other than 0.
		else if ((date[3] == '0') && ((date[4] == '0') || (!isdigit(date[4])))) {
			dateIsCorrect = false;
		}
		//If the first character of the day is 1 or 2,the second character can be any integer.
		else if (((date[3] == '1') || (date[3] == '2')) && (!isdigit(date[4]))) {
			dateIsCorrect = false;
		}
		//If the first character of the date is 3, the second character must be 0 or 1.
		else if ((date[3] == '3') && (date[4] != '0') && (date[4] != '1')) {
			dateIsCorrect = false;
		}
		//Making sure the second slash is present and is placed in the right position.
		else if (date[5] != '/') {
			dateIsCorrect = false;
		}
		//Making sure the characters corresponding to the year are all integers.
		else if((!isdigit(date[6])) || (!isdigit(date[7])) || (!isdigit(date[8])) || (!isdigit(date[9]))) {
			dateIsCorrect = false;
		}
		//Now we will explicitly separate the string into month, day, and year make some additional checks.
		else {
			month = date.substr(0,2);
			day = std::stoi(date.substr(3,2));
			year = std::stoi(date.substr(6,4));

			//Determining whether a year is a leap year or not.
			if ((year%4 != 0) || ((year%100 == 0) && (year%400 != 0))) {
				isLeapYear = false;
			}

			//Disallowing days after February 29th on leap years.
			if ((month == "02") && (isLeapYear) && (day > 29)) {
				dateIsCorrect = false;
			}
			//Disallowing days after February 28th on non-leap years.
			else if ((month == "02") && (!isLeapYear) && (day > 28)) {
				dateIsCorrect = false;
			}
			//Disallowing a 31st day on months that only contain 30 days.
			else if (((month == "04") || (month == "06") || (month == "09") || (month == "11")) && (day > 30)) {
				dateIsCorrect = false;
			}

			//Disallowing special holidays (New Year, 4th of July, and Christmas).
			if (((month == "01") && (day == 1)) || ((month == "07") && (day == 4)) || ((month == "12") && (day == 25))) {
				dateIsAvailable = false;
			}

			//Disallowing dates before the current date.
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

	std::cout << "Succesful addition of the date " << date << "!\n";

/*----------------------------Time slot input and verification----------------------------*/

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

			//Making sure we find a colon in the input string.
			if (index != std::string::npos) {
				//Separating the hour characters and converting them to a single integer; throwing exceptions when necessary.
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

				//Separating the minute characters and converting them to a single integer; throwing exceptions when necessary.
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

				/*Checking case in which the substring before the colon only contains numbers and that the substring after
				the colon only contains non-numeric characters after the first two digits (input is in 12-hour format)*/
				if (((timeSlot.substr(0,index)).find_first_not_of("0123456789") == std::string::npos)
				&& ((timeSlot.substr(index + 1)).find_first_not_of("0123456789") == 2)) {

					/*Only allowing strings of length 6 (e.g. 1:00am) or length 7 (e.g. 11:00pm) in which there are strictly
					four characters after the colon.*/
					if ((timeSlot.length() == 6) || ((timeSlot.length() == 7) && ((timeSlot.substr(index + 1)).length() == 4))) {
						lastIndex = timeSlot.length() - 1;
						secondToLastIndex = lastIndex - 1;

						//Making sure the last two characters are "am" or "pm".
						if ((timeSlot[lastIndex] == 'm') && ((timeSlot[secondToLastIndex] == 'a') || (timeSlot[secondToLastIndex] == 'p'))) {
							timeSlotFormatIsCorrect = true;
						}

						//Converting from 12-hour to 24-hour format.
						timeSlot = io.timeFormatter(timeSlot);

						index = timeSlot.find(':');
						hour = std::stoi(timeSlot.substr(0,index));
						minute = std::stoi(timeSlot.substr(index + 1));
					}
				/*Checking case in which both the substring before the colon and the substring after the colon
				only contain numbers (input is in 24-hour format)*/
				} else if (((timeSlot.substr(0,index)).find_first_not_of("0123456789") == std::string::npos)
					&& ((timeSlot.substr(index + 1)).find_first_not_of("0123456789") == std::string::npos)) {
					//Only allowing strings of length 4 (e.g. 1:00) or length 5 (e.g. 23:00).
					if ((timeSlot.length() == 4) || ((timeSlot.length() == 5))) {
						timeSlotFormatIsCorrect = true;
					}
				} else {
					interface_.clearScreen();
					menu.Header();
					std::cout << "\nFormat is incorrect.\n";
					continue;
				}

				if((timeSlotFormatIsCorrect) && ((hour <= 23) && (hour >= 0)) && ((minute <= 59) && (minute >= 0))){
					timeSlotHourAndMinuteAreCorrect = true;
				}

				if ((timeSlotHourAndMinuteAreCorrect) && (timeSlotFormatIsCorrect)) {
					//Converting time to minutes past midnight to make it easier to manage timer intervals.
					timeInMins = (hour * 60) + minute;
					/*Making sure events can be created between 12:00am and 5:00am or after 11:40pm (there would be an overlap
					into the 12:00am - 5:00am time range).*/
					if ((timeInMins >= 1420) || ((timeInMins >= 0) && (timeInMins <= 300))) {
						interface_.clearScreen();
						menu.Header();
						timeSlotIsAvailable = false;
						std::cout << "\nSorry, you cannot create a meeting between 12:00am and 5:00am. Please pick a different time.\n";
						continue;
						/*Making sure events can be created between 12:00pm and 1:00pm or after 11:40pm (there would be an overlap
						into the 12:00am - 5:00am time range).*/
					} else if ((timeInMins >= 720) && (timeInMins <= 780))  {
						interface_.clearScreen();
						menu.Header();
						timeSlotIsAvailable = false;
						std::cout << "\nSorry, you cannot create a meeting between 12:00pm and 1:00pm. Please pick a different time.\n";
						continue;
					}

					//Creating a pair of integers that will represent the start and end of the slot (in minutes).
					slotStart = timeInMins;
					slotEnd = timeInMins + 20;
					newSlot = {slotStart, slotEnd};

					/*Iterating through the current pairs in the list and compare the new pair (newSlot) with
					each pair in order to determine where to place it*/
					for (auto itr = slotsList.begin(); itr != slotsList.end(); itr++) {
						/*If the start time of the new slot is >= than the end time of some slot in the list, we
						go inside this else statement.*/
						if (newSlot.first >= itr->second) {
							itr++;
							//If we have reached the end of the list, we simply push our new slot to the end of the list.
							if (itr == slotsList.end()) {
								successfulAddition = true;
								slotsList.push_back(newSlot);
								break;
							//If we haven't reached the end of the list, we continue iterating through the list.
							} else {
								itr--;
								continue;
							}
						/*If the start time of the new slot is < than the end time of some slot in the list, we
						go inside this else statement.*/
						} else {
							/*If the end time of the new slot is > the start time of the slot currently on the list,
							we have encountered a conflict and we must tell the admin to input a different time.*/
							if (newSlot.second > itr->first) {
								interface_.clearScreen();
								menu.Header();
								timeSlotIsAvailable = false;
								std::cout << "\nSorry, cannot add that slot because there is a scheduling conflict. Please pick a different time.\n";
								break;
							/*If the end time of the new slot is <= the start time of the slot currently on the list,
							we can be confident that the new slot should be inserted there and we proceed to insert it.*/
							} else {
								successfulAddition = true;
								slotsList.insert(itr, newSlot);
								break;
							}
						}
					}


				}

			//If there is no colon in the string, the format is incorrect.
			} else {
				timeSlotFormatIsCorrect = false;
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

				//Converting slot end time from minutes to hours and minutes in 24-hr mode.
				hourEndTime = slotEnd / 60;
				minuteEndTime = slotEnd % 60;
				std::string timeSlotEnd = "";
				if (hourEndTime < 10) {
					timeSlotEnd += "0";
				}
				timeSlotEnd = (std::to_string(hourEndTime) + ":");
				if (minuteEndTime < 10) {
					timeSlotEnd += "0";
				}
				timeSlotEnd += std::to_string(minuteEndTime);

				//Creating a string that shows the time interval.
				if(io.timeFormat == false)
					timeSlotInterval = timeSlot + " - " + timeSlotEnd;
				else
					timeSlotInterval = io.timeFormatter(timeSlot) + " - " + io.timeFormatter(timeSlotEnd);

				/*Adding the timeSlotInterval to this string that will be printed when the user wants to view
				the slots they have created for far*/
				createdTimeSlots += ("\n\t" + timeSlotInterval);

				std::cout << "The " << timeSlotInterval << " time slot was successfully added!\n";

				//Converting from 24-hour mode to 12-hour mode.
				timeSlot = io.timeFormatter(timeSlot);

				/*This string contains each timeSlot with the amount of people who signed up for that time slot; since the
				creator of the time slot is the only one there for now, in this function that amount will always be 1.*/
				stringOfTimeSlots += timeSlot + ",1,";
			}
		} while((!timeSlotIsAvailable) || (!timeSlotHourAndMinuteAreCorrect) || (!timeSlotFormatIsCorrect));

		do {
			std::cout << "\nPlease select an option:\n"
								<< "\tAdd more slots: input 'a'.\n"
								<< "\tView created slots: input 'v'.\n"
								<< "\tExit menu: input any other key.\n"
								<< "Choice: ";
			std::cin >> userChoice;
			std::cin.ignore(1, '\n');

			if (userChoice == 'v') {
				std::cout << "\nTime slots you have created so far: " << createdTimeSlots << '\n';
			}
		} while (userChoice == 'v');
	} while (userChoice == 'a');
	
	
	//Ask for tasks.
	std::string taskList = requestTasks();
	
	//debug
	std::cout << taskList;
	
	
	

	//This string, containing all the information gathered, will be sent as a parameter to the function addEntry in io.hpp
	outputString += (std::to_string(io.size) + "," + eventName + "," + date + "," + std::to_string(amountOfSlots) + "," + stringOfTimeSlots + std::to_string(amountOfAtendees) + "," + adminName);

	io.addEntry(outputString);
}
std::string Events::requestTasks(){
	std::string userChoice;
	do{
		std::cout << "Would you like to create tasks?\n"
			<< "\tCreate a task: input 'a'.\n"
			<< "\tExit menu: input 'e'.\n"
			<< "Choice: ";
	}while(userChoice != 'a');
	return "";
}
