#ifndef EVENTS_H
#define EVENTS_H

#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include "interface.h"
#include "io.h"

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
};


#include "events.hpp"

#endif
