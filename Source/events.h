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
#include <unordered_map> 
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
  
  /**This method refers to the menu where someone takes a task from an event.
	 * @pre None
	 * @post lets an user take a task.
	 */  
  static void takeTask();
  
	/**This method deals with the UI regarding the tasks.
	 * @pre None
	 * @post None
	 * @return A string that represents the tasks.
	 */
	static void requestTasks();

};


#include "events.hpp"

#endif
