/**
*	@author	Team 3
*	@date
*	@brief A header file for Input/Output (IO) class
*/

#ifndef IO_H
#define IO_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "log.h"

class IO
{
	public:

	bool timeFormat = false;

	/** @pre None
	*   @post A file is opened with given name. It is created if it does not exist yet
	*/
	IO(const std::string fileName);

	/** @pre None
	*   @post A file is closed with given name
	*/
	~IO();

	/** @pre None
	*   @post Adds new event to file
	*   @return None
	*/
	void addEntry(std::string store);

	/** @pre ID is the event's unique identifier. elementName is the name of the element to retrieve
	*   @post Retrieves some event's specific element value from the events file
	*   @return Returns event's specific element (string or int)
	*/
	std::string retrieveElement(int ID, std::string elementName);

	/** @pre ID is the event's unique identifier. elementName is the name of the element to update, value is
	*	 the element's new value
	*   @post Updates some event's specific element
	*   @return None
	*/
	void updateElement(int ID, std::string elementName, void* value);

	/** @pre None
	*   @post Displays all elements in file, one at a time
	*   @return None
	*/
	void displayEntries();

	private:

	/** @pre slot has the time value that needs to be formatted
	*   @post Formats time between 12-hour format and 24-hour format
	*   @return String with slot in new time format
	*/
	std::string timeFormatter(std::string slot);

	int size;		//Number of entries in file
	std::fstream file;		//File stream
	std::string fileName_;		//Name of file
	Log logFile;			//Log object

};

#include "io.hpp"

#endif
