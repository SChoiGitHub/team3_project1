/**
 *    @author Team 3
 *    @date
 *    @file io.hpp
 */

bool IO::timeFormat = false;

IO::IO() : EVENTS_FILE("events.csv"), TASKS_FILE("tasks.csv"), SCHEDULES_FILE("schedules.csv"), ATTENDENCE_FILE("attendence.csv"){
    int n_lines = 0;
    std::string dummy_string;

    eventsFile.open(EVENTS_FILE, std::fstream::app | std::fstream::out | std::fstream::in);
    tasksFile.open(TASKS_FILE, std::fstream::app | std::fstream::out | std::fstream::in);
    schedulesFile.open(SCHEDULES_FILE, std::fstream::app | std::fstream::out | std::fstream::in);
    attendenceFile.open(ATTENDENCE_FILE, std::fstream::app | std::fstream::out | std::fstream::in);

    while(std::getline(eventsFile, dummy_string))
        ++n_lines;

    size = n_lines;
    numEvents = n_lines;
}

IO::~IO(){
    eventsFile.close();
    tasksFile.close();
    schedulesFile.close();
    attendenceFile.close();
}


void IO::addEntry(std::fstream& file, std::string data){
    file.clear();
	file.seekg(0,std::fstream::end);
	file << data << std::endl;
}


std::string IO::retrieveElement(int ID, std::string elementName){
/*    //IDs start at 0
    if( ID >= size )
    {
        std::cout << "The requested event does not exist.\n";
        return "-1";
    }

    //Make sure stream is at beginning of file
    file.clear();    //It is necessary to clear the eof flag
    file.seekg(0, std::ios::beg);

    std::string line;

    std::string element;

    for( int i = 0 ; i <= ID ; ++i )
    {
        std::getline(file,line);
    }

    //Must always be declared after line has been read from file
    std::stringstream ss(line);

    if(elementName == "ID")
    {
        std::getline(ss, element, ',');
    }

    if(elementName == "name")
    {
        for(int i = 0 ; i < 2 ; ++i)
            std::getline(ss, element, ',');
    }

    if(elementName == "date")
    {
        for(int i = 0 ; i < 3 ; ++i)
            std::getline(ss, element, ',');
    }

    if(elementName == "total_slots")
    {
        for(int i = 0 ; i < 4 ; ++i)
            std::getline(ss, element, ',');
    }

    if(elementName == "slots")
    {
        //Loop through line
        for(int i = 0 ; i < 5 ; ++ i)
            std::getline(ss, element, ',');

        //Get total number of slots
        std::string slots = retrieveElement(ID,"total_slots");
        //Convert to int
        int nelem = atoi(slots.c_str());
        slots = element;

        //Write slots' line
        for(int i = 0 ; i < nelem*2 - 1 ; ++i)
        {
            std::getline(ss, element, ',');
            slots = slots + ',' + element;
        }

        //Ready to return slots' line
        element = slots;
    }

    if(elementName == "total_attendees")
    {

        std::string subLine = retrieveElement(ID,"total_slots");
        int nelem = atoi(subLine.c_str());

        for(int i = 0 ; i <= 4 + 2*nelem ; ++i)
            std::getline(ss, element, ',');
    }

    if(elementName == "attendees")
    {
        //Get total number of attendees
        std::string subLine = retrieveElement(ID,"total_slots");
        //Convert string to int
        int nelem = atoi(subLine.c_str());

        //Loop through line to position stream
        for(int i = 0 ; i <= 4 + 2*nelem ; ++i)
            std::getline(ss, element, ',');

        //Get all attendees
        std::getline(ss, element, '\n');
    }
*/
    return "";
}


void IO::updateElement(int ID, std::string elementName, void* value){
/*    std::fstream file_;
	file_.open("event.list", std::ios::in | std::ios::out);

    //IDs start at 0
    if( ID >= size )
    {
        std::cout << "The requested event does not exist.\n";
        return;
    }

    int dummy_int = 0;
    std::string lineBefore, lineRemainder;
    int strings2save = size - ID - 1;
    std::string stringSaved[strings2save];
    std::string search;
    std::string element;

    //Make sure stream is at beginning of file
    file_.clear(); //It is necessary to clear the eof flag
    file_.seekg(0, std::fstream::beg);


    //Get to desired line
    for(int i = 0 ; i <= ID ; i++)
        std::getline(file_,search);


    //Save all other lines after that
    for(int i = 0 ; i < strings2save ; ++i)
        std::getline(file_, stringSaved[i]);

    //Reposition file stream to beginning of file
    file_.clear();
    file_.seekg(0, std::ios::beg);

    //Get to desired line again
    for(int i = 0 ; i <= ID ; i++)
        std::getline(file_, search);

    //Set line string stream
    std::stringstream ss(search);


    //The only possibility that the first character is an s is if the element to be updated is the number of
    //people in a slot
    if( elementName[0] == 's' )
    {
	//If the size of elementName is greater than 5, then the slot number is greater than or equal to 10
        if( elementName.size() > 5)
            dummy_int = 10 * (elementName[4]-'0') + (elementName[5] - '0');
        else
            dummy_int = elementName[4] - '0';


        //Get total number of slots this event
        for(int i = 0 ; i < 4 ; ++i)
            std::getline(ss, element, ',');

        //If the slot requested to be changed is greater than the number of slots available then the slot is invalid
        if( dummy_int > atoi(element.c_str()) || (dummy_int <= 0))
            std::cout << "Invalid slot." << std::endl;

        else
        {
	    //Reposition line string stream at beginnning of line
            ss.seekg(0, std::ios::beg);

	    //Loop through line until getting to that slot's current number of attendees
            for ( int i = 0 ; i < 4 + 2*dummy_int ; ++i )
            {
                std::getline(ss, element, ',');

		//Take the opportunity to save the part of the string before the element that is going to be altered
		if( i != 4 + 2*dummy_int - 1)
			lineBefore = lineBefore + element + ',';
            }

	    //Get the rest of the string that is after the element that is going to be altered
            std::getline(ss, lineRemainder, '\0');

	    //Turn the number of people in the slot to an integer
            dummy_int = atoi(element.c_str());

	    //Increment that integer
            ++dummy_int;

	    //Reposition file stream to beginnning of file
	    file_.clear();
    	    file_.seekg(0, std::ios::beg);

	    //Loop until the line we wanted to alter
   	    for(int i = 0 ; i < ID ; i++)
       		    std::getline(file_, search);

	    //Re-write updated event line
            file_ << lineBefore << dummy_int << ',' << lineRemainder << '\n';

	}
    }

    else if( elementName == "total_attendees" )
    {

	//Get total number of slots
	for(int i = 0 ; i < 4 ; ++i)
	{
            std::getline(ss, element, ',');
	    lineBefore = lineBefore + element + ',';
	}

	dummy_int = atoi(element.c_str());

	for(int i = 0 ; i < 2*dummy_int + 1 ; ++i)
	{
	    std::getline(ss, element, ',');
	    //Take the opportunity to save the part of the string before the element that is going to be altered
	    if( i != 2*dummy_int )
		lineBefore = lineBefore + element + ',';
	}

	//Get the rest of the string that is after the element that is going to be altered
        std::getline(ss, lineRemainder, '\0');

	dummy_int = atoi(element.c_str());

	++dummy_int;

	//Reposition file stream to beginnning of file
	file_.clear();
    	file_.seekg(0, std::ios::beg);

	//Loop until the line we wanted to alter
   	for(int i = 0 ; i < ID ; i++)
       	   std::getline(file_, search);

	//Re-write updated event line
        file_ << lineBefore << dummy_int << ',' << lineRemainder << '\n';
    }

    else if( elementName == "attendees" )
    {
	element = (char *) value;

	//Reposition file stream to beginnning of file
	file_.clear();
    	file_.seekg(0, std::ios::beg);

	//Loop until the line we wanted to alter
   	for(int i = 0 ; i < ID ; i++)
       	   std::getline(file_, lineRemainder);

	file_ << search << ',' << element << '\n';

    }

    //Re-write overwritten strings
    for(int i = 0 ; i < strings2save ; ++i)
        file_ << stringSaved[i];
*/
}

void IO::displayEntries()
{
    std::string element;
    int nelem;

    //Make sure stream is at beginning of file
    file.clear();    //It is necessary to clear the eof flag
    file.seekg(0, std::ios::beg);
//?
	file.clear();    //It is necessary to clear the eof flag
    file.seekg(0, std::ios::beg);

    for(int i = 0; i < size; ++i)
    {
        //Display ID, name, date and number of attendees
        std::cout << "-- Event " << i+1 << " --" << std::endl;
        std::cout << "ID: " << retrieveElement(i,"ID") << "\n";
        std::cout << "Name: " << retrieveElement(i,"name") << "\n";
        std::cout << "Date: " << retrieveElement(i,"date") << "\n";
        std::cout << "Total Attendees: " << retrieveElement(i,"total_attendees") << "\n";

        std::cout << "Attendees: ";
        element = retrieveElement(i,"total_attendees");

        //Convert number of attendees to int
        nelem = atoi(element.c_str());
        //Get string of attendees' names
        element = retrieveElement(i,"attendees");
        std::string attendee[nelem];
        std::stringstream sa(element);

        for(int j = 0 ; j < nelem ; ++j)
            std::getline(sa,attendee[j],',');

        //Print attendees' names
        for(int j = 0 ; j < nelem ; ++j)
        {
            std::cout << attendee[j];
            if( j == 0)
                std::cout << " (creator)";
            std::cout << "; ";

        }
        std::cout << "\n";

        std::cout << "Slots Available: ";
        element = retrieveElement(i,"total_slots");
        nelem = atoi(element.c_str());
        element = retrieveElement(i,"slots");
        std::string slot[2*nelem];
        std::stringstream ss(element);

        for(int j = 0 ; j < 2*nelem ; ++j)
            std::getline(ss,slot[j],',');

        //Print slots available
        for(int j = 0 ; j < 2*nelem ; j += 2)
        {
            if( timeFormat == true )
                std::cout << slot[j] << " - " << slot[j+1] << " attendee(s); ";
            else
                std::cout << timeFormatter(slot[j]) << " - " << slot[j+1] << " attendee(s); ";
        }
        std::cout << "\n\n";

    }
}

std::string IO::timeFormatter(std::string slot)
{
    std::stringstream ss(slot);
    int s_size = slot.size();
    int hours = 0;
    std::string meridiem;
    std::string formatted_slot;
    //05:30am   17:30
    //12-hour format -> will have the extra am or pm characters that the 24-hour format does not have
    if(s_size + 1 > 6)
    {
        meridiem = slot[s_size-2];

        if(meridiem == "a")
        {
            getline(ss, formatted_slot, ':');
            hours = atoi(formatted_slot.c_str());
            getline(ss, formatted_slot, 'a');
              //12:40am  06:50am 00:30am wrong!!
            if( hours == 12 )
                formatted_slot = "00:" + formatted_slot;
            else
                if(hours == 0)
                    formatted_slot = std::to_string(hours) + "0:" + formatted_slot;
                else
                    formatted_slot = std::to_string(hours) + ":" + formatted_slot;
        }
        else
        {   //05:30pm
            getline(ss, formatted_slot, ':');
            hours = atoi(formatted_slot.c_str());

            if(hours != 12)
                hours += 12;

            getline(ss, formatted_slot, 'p');
            formatted_slot = std::to_string(hours) + ':' + formatted_slot;
        }
    }
    else
    {
        getline(ss,meridiem,':');
        hours = atoi(meridiem.c_str());
        getline(ss, formatted_slot);

        if( hours < 12 )
        {
            formatted_slot = meridiem + ':' + formatted_slot + "am";
        }
        else
        {
            if( hours != 12 )
                hours -= 12;

            formatted_slot = std::to_string(hours) + ':' + formatted_slot + "pm";
        }
    }

    return formatted_slot;
}


//Retrives and Stores General Task information
int IO::storeEvent(std::string name, std::string creator){
    std::string line = std::to_string(numEvents) + "," + name + "," + creator;

    addEntry(eventsFile, line);

    numEvents += 1;
}


//Retrives and Stores Dates and times for events
void IO::storeSchedule(int id, std::string date, std::list<std::string> times){
    std::string line = id + "," + date;

    for(auto const& i : times){
        line += "," + i;
    }

    addEntry(schedulesFile, line);
}


//Retrives and Stores Tasks and related information
void IO::storeTask(int id, std::string name, bool taken, std::string assignee){
    std::string line = id + "," + name;

    if(taken){
        line += "true," +assignee;
    }else{
        line +=  ",false";
    }

    addEntry(tasksFile, line);
}


//Retrieves and Stores Attendees
void IO::storeAttendees(int id, std::string date, std::string time, std::list<std::string> attendees){
    std::string line = id + "," + date + "," + time;

    for(auto const& i : attendees){
        line += "," + i;
    }

    addEntry(attendenceFile, line);
}
