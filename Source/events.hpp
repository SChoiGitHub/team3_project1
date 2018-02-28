/**
*	@author Team 3
*	@date
*	@file events.hpp
*/



time_t Events::t = time(NULL);
tm* Events::timePtr = localtime(&t);
int Events::current_year = (int)timePtr->tm_year + 1900;
int Events::current_month = (int)timePtr->tm_mon + 1;
int Events::current_day = (int)timePtr->tm_mday;
Interface Events::interface;
IO Events::io;


void Events::userMode()
{
	Interface::Menu menu({
		{"Set Availability", Events::setAvailability},
		{"Task a Task", Events::takeTask},
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
	IO io_;
	bool digit_flag = true;
	bool new_attendee = false;  //for any new attendence
	int dummy_int = 0;

	std::size_t found;
	

	if( io_.size != 0 )
	{
		std::string input = interface.getInput("Please select an event ID from the list above: "); //Storing the event ID in varaible "input"

		for(unsigned int i = 0; i < input.size() ; ++i)
			if( isdigit(input[i]) == 0 )
				digit_flag = false; //Checking to see if "input" is a number for sanitization purposes (probably will reduce to helper method)

		if(digit_flag == true) //If "input" is a number
		{
			int input_ = atoi(input.c_str()); //"input_" variable is an integer clone of "input"

			if( input_ < 0 || input_ > io_.size - 1) //More input sanitization
			{
				std::cout << "Invalid event ID." << std::endl;
				interface.Wait("");
			}
			else //"input_" is in the valid range of IDs
			{
				input = io_.retrieveElement(input_,"total_slots"); //"input" now holds a string of the number of time slots
				dummy_int = atoi(input.c_str()); //"dummy_int" now holds the number of time slots
				input = io_.retrieveElement(input_,"slots"); //"input" now holds a string of comma-separated slots

				std::string slots[dummy_int]; //"slots" is an array of size "dummy_int" (which is the total number of time slots)
				std::string dummy_string; //"dummy_string"
				std::stringstream ss(input); //"ss" is a stringstream over "input" (which is a string of all the time slots)

				for(int i = 0; i < dummy_int ; ++i) //Iterate over the number of time slots
				{
					//Get slots
					getline(ss, slots[i], ','); //Put the ith slot into the ith entry of "slots"
					//Just to move the string forward (over the number of people in a slot)
					getline(ss, input, ',');

					dummy_string = "slot" + std::to_string(i+1); //"dummy_string" holds a string in the form 'slotn' (n is an int)

					if(io_.timeFormat == true ) //Formatting slot output for 12/24 hours
						std::cout << "Are you available at " << slots[i] << " ? [Y/n]: ";
					else
						std::cout << "Are you available at " << io_.timeFormatter(slots[i]) << " ? [Y/n]: ";

					getline(std::cin, input); //Get the user's choice

					if(input == "Yes" || input == "yes" || input == "y" || input == "Y") //If user is available
					{
						io_.updateElement(input_,dummy_string,NULL); //Adding to timeslot 
						/** NOTE **/
						//updateElement() is to be replaced with storeAttendee()
						new_attendee = true;
					}
					else if(input != "No" && input != "no" && input != "n" && input != "N") //If user enters some invalid input
					{
						std::cout << "Invalid input. Please try again." << std::endl;

						ss.clear(); //Clear the fail bit
						ss.seekg(0, std::ios::beg); //Go back to position 0 in "ss"

						for(int j = 0; j < 2*i ; ++j)
						    //Here "i" refers to the current slot
						    //The point of this loop is to reset the position of the stringstream to the current slot
						    //This is needed if the input was invalid, since whether or not the user was added was indecisive
							getline(ss, input, ',');

						--i; //Reset the slot position
					}
				}

				if(new_attendee == true) //If the person is a new attendee to the slot
				{
				    const char* name_ = (interface.getName()).c_str();
				    //const char* name_ = name.c_str(); //"name_" points to a c string of "name"
				    io_.updateElement(input_,"total_attendees",NULL); //Increment the "total_attendees" element
				    io_.updateElement(input_,"attendees", (char *) name_); //Add "name_" to the "attendees" element
				}
			}
		}
		else //If "input" is not a number
		{
			std::cout << "Invalid event ID." << std::endl;
			interface.Wait("");
		}

	} else { //If there are no events to set availability for
		interface.Wait("No events available... Sorry!");
	}
}

void Events::createEvent()
{
	Interface::Menu menu({{"", NULL}});

	std::string outputString = "";
	std::string adminName = "";
	std::string eventName = "";

	/*----------------------------Declaring variables used for input and verification of time slots----------------------------*/

	interface.clearScreen();
	menu.Header();

	std::size_t found;



	do {
		found = 0;
		std::cout << "\nEnter your name (no commas): ";
		std::getline(std::cin, adminName);
		found = adminName.find_first_of(",");

	} while (found != std::string::npos);


	do {
		found = 0;
		std::cout << "\nEnter event name (no commas): ";
		std::getline(std::cin, eventName);
		found = eventName.find_first_of(",");
	} while (found != std::string::npos);

	//Declaring a set of date strings
	std::unordered_map<std::string,std::string>* dateInfo = new std::unordered_map<std::string,std::string>;
	bool newDate = false;
	std::string choose;

	/*----------------------------Date input and verification----------------------------*/

	do {
    //Ask for the date.
    std::string date = requestDate();
		std::cout << "Succesful addition of the date " << date << "!\n";
    dateInfo->emplace(date,std::string(""));
    date = "";
    
    bool continueInput = true;
		do {
      //Do we want a new date?
			std::cout << "Do you want to set a new date? (Yes/No) : ";
			std::getline(std::cin, choose);

			if (choose == "Yes" || choose == "yes" || choose == "y" || choose == "Y")
			{
				newDate = true;
        continueInput = false;
			}else if(choose == "No" || choose == "no" || choose == "n" || choose == "N"){
        newDate = false;
        continueInput = false;
      }
		}while(continueInput);
	}while(newDate);

/*----------------------------Time slot input and verification----------------------------*/
  auto&& it = dateInfo->begin();
  std::string timeSlots = "";
  
	do {
    bool copyNewItems = false;
    
		std::cout << "Please set time slots for " << std::string(it->first) << "\n\n";
    
    //Copy over new string slots!
    if(timeSlots != ""){
      std::cout << "Would you like to copy over the previous time slots to this new date?\n"
                << "Yes: Type 'y'.\n"
                << "No: Type anything else.\n"
                << "Choose: ";
      std::getline(std::cin, choose);
      copyNewItems = (choose == "y");
    }
              
    if(!copyNewItems){
      timeSlots = requestTimeSlots();
    }
    
		//Add new stuff to timeslots and reset everything.
    dateInfo->at(it->first) = timeSlots;  
    if(it != dateInfo->end()){
      it++;
    }
  }while(it != dateInfo->end());
  
  
  //Ask for tasks
  std::list<std::string> tasks = requestTasks(); //Ask for tasks.
  
  //ADD STUFF
  int id = io.storeEvent(eventName,adminName); //Store the event and set id.
  for(auto&& it = tasks.begin(); it != tasks.end(); it++){
		io.storeTask(id,(*it));
	}
  //Store the schedule
  for(auto&& it = dateInfo->begin(); it != dateInfo->end(); it++){
    //Pass this in later.
    std::list<std::string> parsedTimeString;
    //We will parse it.
    std::stringstream s(dateInfo->at(it->first));
    std::string hold;
    //Read everything in.
    while(std::getline(s,hold,',')){
      parsedTimeString.push_back(hold);
      std::getline(s,hold,','); //Remove the pointless numOfAttendees...
    }
    //Pass in schedule
    io.storeSchedule(id,it->first,parsedTimeString);
  }
  
  delete dateInfo;
}
std::list<std::string> Events::requestTasks(){
	Interface interface;
	std::string userChoice;
	std::list<std::string> currentTaskList;
	bool quit = true;
	
	interface.clearScreen();
	do{
		quit = true;
		std::cout << "Would you like to create tasks?\n"
			<< "\tCreate a task: input 'a'.\n"
			<< "\tView current tasks: input 'v'.\n"
			<< "\tExit menu: input anything else.\n"
			<< "Choice: ";
		std::cin >> userChoice;
		std::cin.ignore(1, '\n');
		
		//Clear screen.
		
		//If any of these happen, we do not exit the loop.
		if(userChoice.at(0) == 'a'){
			quit = false;
			
			//Get a task.
			interface.clearScreen();
			std::cout << "What is the task?: ";
			std::getline(std::cin, userChoice);
			currentTaskList.push_back(userChoice);
			
		}else if(userChoice.at(0) == 'v'){
			quit = false;
			
			//Just display the current list.
			std::cout << "Your current task list:\n";
			for(auto&& it = currentTaskList.begin(); it != currentTaskList.end(); it++){
				std::cout << '\t' << (*it) << '\n';
			}
			
		}
		std::cout << "\n\n";
	}while(!quit);
  
	return currentTaskList;
}
void Events::takeTask(){
  Interface interface;
	bool digit_flag = true;
  bool quit;
  std::string userChoice;


	if( io.size != 0 )
	{
		std::string input = interface.getInput("Please select an event ID from the list above: ");

		for(unsigned int i = 0; i < input.size() ; ++i)
			if( isdigit(input[i]) == 0 )
				digit_flag = false;

		if(digit_flag == true)
		{
			int input_ = atoi(input.c_str());

			if( input_ < 0 || input_ > io.size - 1)
			{
				std::cout << "Invalid event ID." << std::endl;
				interface.Wait("");
			}
			else{
        //Temporary measure, change later.
        do{
          quit = true;
          std::cout << "Would you like to take tasks?\n"
            << "\tTake a task: input 't'.\n"
            << "\tView current tasks and who is doing them: input 'v'.\n"
            << "\tExit menu: input anything else.\n"
            << "Choice: ";
          std::cin >> userChoice;
          std::cin.ignore(1, '\n');
          
          //If any of these happen, we do not exit the loop.
          if(userChoice.at(0) == 't'){
            quit = false;
            
            std::cout << "What task do you want (type in the task name)?\n"
              << "Snacks\n"
              << "Choice: ";
            std::cin >> userChoice;
            std::cin.ignore(1, '\n');
            
            if(userChoice != "Snacks"){
              std::cout << "Invalid Choice. You may try again.\n";
            }else{
              std::cout << "You are assigned for snacks.\n";
            }
            
          }else if(userChoice.at(0) == 'v'){
            quit = false;
            
            std::cout << "Here is a list of tasks:\n"
              << "\tBBQ: Barbie\n"
              << "\tPlates: Dan\n"
              << "\tGames: Tommy\n"
              << "\t(Takable) Snacks\n";
            
            std::cout << "\n";
          }
          std::cout << "\n\n";
        }while(!quit);
      }
    }
		else
		{
			std::cout << "Invalid event ID." << std::endl;
			interface.Wait("");
		}

	} else {
		interface.Wait("No events available... Sorry!");
	}
}

std::string Events::requestDate(){
  Interface::Menu menu({{"", NULL}});
  std::string date = "";
	std::string month = "";
	int day = 0;
	int year = 0;
	bool dateIsCorrect = true;
	bool dateIsAvailable = true;
	bool isLeapYear = true;
  
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
    else if ((!isdigit(date[6])) || (!isdigit(date[7])) || (!isdigit(date[8])) || (!isdigit(date[9]))) {
      dateIsCorrect = false;
    }
    //Now we will explicitly separate the string into month, day, and year make some additional checks.
  
    month = date.substr(0, 2);
    day = std::stoi(date.substr(3, 2));
    year = std::stoi(date.substr(6, 4));

    //Determining whether a year is a leap year or not.
    if ((year % 4 != 0) || ((year % 100 == 0) && (year % 400 != 0))) {
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
    if (current_year > year || (current_year == year && current_month > atoi(month.c_str())) || (current_year == year && current_month == atoi(month.c_str()) && current_day > day))
    {
      dateIsCorrect = false;
    }
    if (!dateIsCorrect) {
      interface.clearScreen();
      menu.Header();
      std::cout << "\nWrong input! Please enter a valid date in MM/DD/YYYY format.\n";
    }
    if (!dateIsAvailable) {
      interface.clearScreen();
      menu.Header();
      std::cout << "\nSorry, that day is not available for meetings. Please enter a different date.\n";
    }
  } while ((!dateIsCorrect) || (!dateIsAvailable));
  
  return date;
}

std::string Events::requestTimeSlots(){
  //variables regarding the time slots
  Interface::Menu menu({{"", NULL}});
  
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

	std::pair<int, int> newSlot(0, 0);
	std::string createdTimeSlots = "";

	std::list<std::pair<int, int>> slotsList;
	slotsList.push_back(std::pair<int, int>(0, 300));
	slotsList.push_back(std::pair<int, int>(720, 780));

  interface.clearScreen();
  //Everything is cleared.
  
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
      std::getline(std::cin, timeSlot);

      index = timeSlot.find(':');

      //Making sure we find a colon in the input string.
      if (index != std::string::npos) {
        //Separating the hour characters and converting them to a single integer; throwing exceptions when necessary.
        try {
          hour = std::stoi(timeSlot.substr(0, index));
        }
        catch (std::invalid_argument& e) {
          interface.clearScreen();
          menu.Header();
          std::cout << "\nInvalid argument.\n";
          continue;
        }
        catch (std::out_of_range& e) {
          interface.clearScreen();
          menu.Header();
          std::cout << "\nOut of range.\n";
          continue;
        }
        catch (...) {
          interface.clearScreen();
          menu.Header();
          std::cout << "\nOther error.\n";
          continue;
        }

        //Separating the minute characters and converting them to a single integer; throwing exceptions when necessary.
        try {
          minute = std::stoi(timeSlot.substr(index + 1));
        }
        catch (std::invalid_argument& e) {
          interface.clearScreen();
          menu.Header();
          std::cout << "\nInvalid argument.\n";
          continue;
        }
        catch (std::out_of_range& e) {
          interface.clearScreen();
          menu.Header();
          std::cout << "\nOut of range.\n";
          continue;
        }
        catch (...) {
          interface.clearScreen();
          menu.Header();
          std::cout << "\nOther error.\n";
          continue;
        }

        /*Checking case in which the substring before the colon only contains numbers and that the substring after
        the colon only contains non-numeric characters after the first two digits (input is in 12-hour format)*/
        if (((timeSlot.substr(0, index)).find_first_not_of("0123456789") == std::string::npos)
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
            hour = std::stoi(timeSlot.substr(0, index));
            minute = std::stoi(timeSlot.substr(index + 1));
          }
          /*Checking case in which both the substring before the colon and the substring after the colon
          only contain numbers (input is in 24-hour format)*/
        }
        else if (((timeSlot.substr(0, index)).find_first_not_of("0123456789") == std::string::npos)
          && ((timeSlot.substr(index + 1)).find_first_not_of("0123456789") == std::string::npos)) {
          //Only allowing strings of length 4 (e.g. 1:00) or length 5 (e.g. 23:00).
          if ((timeSlot.length() == 4) || ((timeSlot.length() == 5))) {
            timeSlotFormatIsCorrect = true;
          }
        }
        else {
          interface.clearScreen();
          menu.Header();
          std::cout << "\nFormat is incorrect.\n";
          continue;
        }

        if ((timeSlotFormatIsCorrect) && ((hour <= 23) && (hour >= 0)) && ((minute <= 59) && (minute >= 0))) {
          timeSlotHourAndMinuteAreCorrect = true;
        }

        if ((timeSlotHourAndMinuteAreCorrect) && (timeSlotFormatIsCorrect)) {
          //Converting time to minutes past midnight to make it easier to manage timer intervals.
          timeInMins = (hour * 60) + minute;
          /*Making sure events can be created between 12:00am and 5:00am or after 11:40pm (there would be an overlap
          into the 12:00am - 5:00am time range).*/
          if ((timeInMins >= 1420) || ((timeInMins >= 0) && (timeInMins <= 300))) {
            interface.clearScreen();
            menu.Header();
            timeSlotIsAvailable = false;
            std::cout << "\nSorry, you cannot create a meeting between 12:00am and 5:00am. Please pick a different time.\n";
            continue;
            /*Making sure events can be created between 12:00pm and 1:00pm or after 11:40pm (there would be an overlap
            into the 12:00am - 5:00am time range).*/
          }
          else if ((timeInMins >= 720) && (timeInMins <= 780)) {
            interface.clearScreen();
            menu.Header();
            timeSlotIsAvailable = false;
            std::cout << "\nSorry, you cannot create a meeting between 12:00pm and 1:00pm. Please pick a different time.\n";
            continue;
          }

          //Creating a pair of integers that will represent the start and end of the slot (in minutes).
          slotStart = timeInMins;
          slotEnd = timeInMins + 20;
          newSlot = { slotStart, slotEnd };

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
              }
              else {
                itr--;
                continue;
              }
              /*If the start time of the new slot is < than the end time of some slot in the list, we
              go inside this else statement.*/
            }
            else {
              /*If the end time of the new slot is > the start time of the slot currently on the list,
              we have encountered a conflict and we must tell the admin to input a different time.*/
              if (newSlot.second > itr->first) {
                interface.clearScreen();
                menu.Header();
                timeSlotIsAvailable = false;
                std::cout << "\nSorry, cannot add that slot because there is a scheduling conflict. Please pick a different time.\n";
                break;
                /*If the end time of the new slot is <= the start time of the slot currently on the list,
                we can be confident that the new slot should be inserted there and we proceed to insert it.*/
              }
              else {
                successfulAddition = true;
                slotsList.insert(itr, newSlot);
                break;
              }
            }
          }


        }

        //If there is no colon in the string, the format is incorrect.
      }
      else {
        timeSlotFormatIsCorrect = false;
        continue;
      }

      if (!timeSlotHourAndMinuteAreCorrect) {
        interface.clearScreen();
        menu.Header();
        std::cout << "\nHour and/or minutes are off bounds.\n";
      }

      if (!timeSlotFormatIsCorrect) {
        interface.clearScreen();
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
        if (io.timeFormat == false)
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
    } while ((!timeSlotIsAvailable) || (!timeSlotHourAndMinuteAreCorrect) || (!timeSlotFormatIsCorrect));
    
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
  
  return stringOfTimeSlots;
}
