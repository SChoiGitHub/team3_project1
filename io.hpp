/**
*	@author Team 3
*	@date 
*	@file io.hpp
*/

IO::IO(std::string filename) : file(filename)
{
	f.open(file, std::ios::out | std::ios::app);
}

IO::~IO() 
{
	f.close();
}


void IO::addEntry()
{
	
}


std::string IO::retrieveElement(int ID, std::string elementName)
{
	return NULL;
}


void IO::updateElement(int ID, std::string elementName, void* value)
{
	
}


