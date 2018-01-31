/**
*	@author	Team 3
*	@date 
*	@brief A header file Log class
*/

#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <string>
#include <fstream>
#include <time.h> 
#include "interface.h"

template <typename T>
class Log
{
	public:

	/** @pre None
	*   @post A file is opened with given name. It is created if it does not exist yet
	*/
	Log();

	/** @pre None
	*   @post A file is closed with given name
	*/
	~Log();

	/** @pre timeNdate refers to the specific time and date the error occurred, error_type specifies the
	*	 type of error encoutered, function_responsible specifies where the error occurred in the code
	*   @post Keeps log file of encountered errors in the running program. Shows error message to user
	*   @return None
	*/
	void addEntry(std::string error_type, std::string function_responsible);
	

	private:
    
	std::ofstream logFile;			//Output stream for error log file
	int size;				//Number of entries in file
};

#include "log.hpp"

#endif
