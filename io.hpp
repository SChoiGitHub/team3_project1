/**
*	@author Team 3
*	@date 
*	@file io.hpp
*/

IO::IO(const std::string fileName) : fileName_(fileName)
{
	int n_lines = 0;
	std::string dummy_string;

	file.open(fileName_, std::fstream::in | std::fstream::out | std::fstream::app);
	
	while(std::getline(file, dummy_string))
        	++n_lines;
	
	size = n_lines;
}

IO::~IO() 
{
	file.close();
}


void IO::addEntry()
{
	//This adds lines to file events.list	







}


std::string IO::retrieveElement(int ID, std::string elementName)
{
	//IDs start at 0
	if( ID >= size )
	{
		std::cout << "The requested event does not exist.\n";
		return "-1";
	}

	//Make sure stream is at beginning of file
	file.clear();	//It is necessary to clear the eof flag
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

	return element;
}


void IO::updateElement(int ID, std::string elementName, void* value)
{
	
}

void IO::displayEntries()
{
	std::string element;
	int nelem;

	//Make sure stream is at beginning of file
	file.clear();	//It is necessary to clear the eof flag
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
			std::cout << slot[j] << " - " << slot[j+1] << " attendee(s); ";
		std::cout << "\n\n";
		
	}
}

std::string IO::timeFormatter(std::string slot)
{
	//12-hour format -> will have the extra am or pm characters that the 24-hour format does not have
	if(slot.size() > 6)
	{
		std::cout << "Hello\n";
	}
	
	return "hi\n";
}








