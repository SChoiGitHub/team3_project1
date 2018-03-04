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
    {"Inspect an Event", Events::inspectEvent},
		{"Set Availability", Events::setAvailability},
		{"Take a Task", Events::takeTask},
		{"Toggle Time Format 12/24", Interface::toggleTimeFormat},
		{"Go back", nullptr}
	});

	menu.Loop();
}

void Events::adminMode()
{
	Interface::Menu menu({
    {"Inspect an Event", Events::inspectEvent},
		{"Add Event", Events::createEvent},
		{"Toggle Time Format 12/24", Interface::toggleTimeFormat},
		{"Go back", nullptr}
	});

	menu.Loop();
}

void Events::setAvailability()
{

  std::string input = ""; //Dummy variable to stop compiler from complaining for now.
  std::string name = "";

  int id = requestID();

  if(id != -1){ //Event exists.
    name = sanitizeInput("What is your name?: ",",");//Get name

    std::cout << "\n\n Please look at the dates of your chosen event.";
    std::cout << "\nWhat date do you want?\n";

    std::list<std::pair<std::string, std::list<std::string>>>* datesAndSchedules = io.obtainSchedules(id);
    std::string date;
    bool dateIsThere;
    std::pair<std::string,std::list<std::string>> scheduleAtDate;

    do{
      do{
        dateIsThere = false;

        date = requestDate();
        //Is the date even there?
        for(auto & it : *datesAndSchedules){
          if(date == it.first){
            dateIsThere = true;
            scheduleAtDate = it;
            break;
          }
        }
        if(!dateIsThere){
          std::cout << "The event does not have that date.\n";
        }
      }while(!dateIsThere);

      /*
      for(auto&& it = datesAndSchedules->begin(); it != datesAndSchedules->end(); it++){
        if(date == (*it).first){
          dateIsThere = true;
          break;
        }
      }
      */
      for(auto & it : scheduleAtDate.second){
        std::cout << "Do you want to attend the event at " << it << " on " << scheduleAtDate.first << "? (Yes/No):";
        if(yesOrNo()){
          io.storeAttendee(id, date, it, name);
        }
      }
      std::cout << "Would you like to attend at another date of the same event? (Yes/No)? ";
    }while(yesOrNo());

    delete datesAndSchedules;
  }else{
    //Do nothing
  }
}
void Events::createEvent(){
	Interface::Menu menu({{"", NULL}});

	std::string outputString = "";
	std::string adminName = "";
	std::string eventName = "";

	/*----------------------------Declaring variables used for input and verification of time slots----------------------------*/

	interface.clearScreen();
	menu.Header();

  adminName = sanitizeInput("\nEnter your name (no commas): ",",");
  eventName = sanitizeInput("\nEnter event name (no commas): ",",");

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

			if(yesOrNo()){
				newDate = true;
        continueInput = false;
			}else{
        newDate = false;
        continueInput = false;
      }
		}while(continueInput);
	}while(newDate);

/*----------------------------Time slot input and verification----------------------------*/
  auto&& it = dateInfo->begin();
  std::string timeSlots = "";

	do {
    interface.clearScreen();
    bool copyNewItems = false;

		std::cout << "Please set time slots for " << std::string(it->first) << "\n";

    //Copy over new string slots!
    if(timeSlots != ""){
      std::cout << "\nWould you like to copy over the previous time slots to this new date? (Yes/No)\n"
                << "Yes: Type 'y'.\n"
                << "No: Type 'n'.\n"
                << "Choose: ";
      copyNewItems = yesOrNo();
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
      hold = IO::timeFormatter(hold);
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
      userChoice = sanitizeInput("What is the task?: ",",");

      //Tasks are unique, NO DUPLICATES.
      if(currentTaskList.end() != std::find(currentTaskList.begin(),currentTaskList.end(),userChoice)){
        std::cout << "That task already exists. The duplicate will be ignored.\n";
      }else{
        currentTaskList.push_back(userChoice);
      }

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
  bool quit;
  std::string userChoice;


  int id = requestID();

  if(id != -1){
      std::list<std::pair<std::string, std::string>>* tasks = io.obtainTasks(id);
      std::cout << "\n";
      std::string name = sanitizeInput("What is your name? ",",");
      std::cout << "\n";
      do{
        quit = true;
        std::cout << "Would you like to take tasks?\n"
          << "\tTake a task: input 't'.\n"
          << "\tView current tasks and who is doing them: input 'v'.\n"
          << "\tExit menu: input anything else.\n"
          << "Choice: ";
        std::cin >> userChoice;
        std::cin.ignore(1, '\n');
        
        std::cout << "\n";

        //If any of these happen, we do not exit the loop.
        if(userChoice.at(0) == 't'){
          quit = false;
          if(tasks != nullptr){
            std::cout << "Tasks Below:\n";
            for(auto&& it = tasks->begin(); it != tasks->end(); it++){
              if(it->second == ""){
                std::cout << "\t" << it->first << " (UNTAKEN)\n";
              }else{
                std::cout << "\t" << it->first << " is being done by " << it->second << "\n";
              }
            }
            
            std::cout << "\n";
            bool keepTrying;

            do{
              keepTrying = true;
              std::string input = sanitizeInput("What task do you want (type in the task name)?",",");

              for(auto&& it = tasks->begin(); it != tasks->end(); it++){
                if(it->first == input){
                  if(it->second == ""){
                    std::cout << "You are now doing that task.\n";
                    io.storeTaskAssignee(id,input,name);
                  }else{
                    std::cout << it->first << " is already being done by " << it->second << "\n";
                  }
                  keepTrying = false;
                }
              }
              if(keepTrying){
                std::cout << "That is not a task in this event.\n";
              }
            }while(keepTrying);
          }
        }else if(userChoice.at(0) == 'v'){
          quit = false;

          if(tasks != nullptr){
            std::cout << "Tasks Below:\n";
            for(auto&& it = tasks->begin(); it != tasks->end(); it++){
              if(it->second == ""){
                std::cout << "\t" << it->first << " (UNTAKEN)\n";
              }else{
                std::cout << "\t" << it->first << " is being done by " << it->second << "\n";
              }
            }
          }
        }
        std::cout << "\n\n";
      }while(!quit);

      delete tasks;
    }else{
      //Do nothing, the event is invalid.
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

    try{
      month = date.substr(0, 2);
      day = std::stoi(date.substr(3, 2));
      year = std::stoi(date.substr(6, 4));
    }catch(...){
      dateIsCorrect = false;
    }

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

  interface.clearScreen();
  return stringOfTimeSlots;
}
int Events::requestID(){
	bool digit_flag = true;

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
        return input_;
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
  return -1;
}
void Events::inspectEvent(){
  int id = requestID();

  if(id != -1){
    interface.clearScreen();
    io.displayEntry(id);
    interface.Wait("");
  }else{
    //Do nothing;
  }
}
bool Events::yesOrNo()
{
  //Get into the loop and keep on getting input until you are done.
  std::string input;
  do{
      std::getline(std::cin, input);
      if((input == "Y" || input == "y" || input == "Yes" || input == "yes")){
        return true;
      }
      else if((input == "N" || input == "n" || input == "No" || input == "no")){
        return false;
      }else{
        std::cout << "Please type in 'y' or 'n' to say \"yes\" or \"no\" respectively\n";
      }
  }while(true);
}
std::string Events::sanitizeInput(std::string message, std::string disallowed){
  std::size_t found = 0;
  std::string input;
  std::cout << message;

  do {
		std::getline(std::cin,input);
		found = input.find_first_of(disallowed);
    if(found != std::string::npos){
      std::cout << disallowed << " cannot be in the input!\n";
    }
	} while (found != std::string::npos);

  return input;
}
