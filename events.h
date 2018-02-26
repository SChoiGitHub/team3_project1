#ifndef EVENTS_H
#define EVENTS_H

#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <cctype>
#include <stdexcept>
#include <ctime>
#include <list>
#include <set>
#include "io.h"
#include "interface.h"

class Events
{
	public:

	/** @pre None
	*   @post Start User Mode
	*   @return None
	*/
	static void userMode();

	/** @pre None
	*   @post Start Admin Mode
	*   @return None
	*/
	static void adminMode();

	private:

	/** @pre None
	*   @post Sets user's availability for a specific event
	*   @return None
	*/
	static void setAvailability();

	/** @pre None
	*   @post Creates new event specified by user
	*   @return None
	*/
	static void createEvent();
};


#include "events.hpp"

#endif
