/**
*	@author	Team 3
*	@date 
*	@brief A header file for Input/Output (IO) class
*/

#ifndef IO_H
#define IO_H

#include <iostream>
#include <string>
#include "log.h"

class IO
{
	public:

	/** @pre None
	*   @post A file is opened with given name. It is created if it does not exist yet
	*/
	IO(std::string filename);

	/** @pre None
	*   @post A file is closed with given name
	*/
	~IO();

	/** @pre None
	*   @post Adds new event to file
	*   @return None
	*/
	static void addEntry();

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

	private:
    
	std::ofstream f;		//File stream
	std::string file;		//Name of file
	Log logFile;			//Log object
	int size;			//Number of entries in file
};

#include "io.hpp"

#endif
