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
#include <algorithm>
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
    
    
    static time_t t; /**Time pointer*/
    static tm* timePtr; /**Time pointer*/
    static int current_year; /**The current year of the execution*/
    static int current_month; /**The current month of the execution*/
    static int current_day; /**The current day of the execution*/
    static Interface interface; /**The interface, or UI.*/
    static IO io; /**The file IO object*/

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
    static std::list<std::string> requestTasks();
    /**This method deals with the UI regarding a single date.
     * @pre None
     * @post None
     * @return A string representing the date
     */
    static std::string requestDate();
    /**This method deals with the UI regarding the time slots of a day.
     * @pre None
     * @post None
     * @return A string representing the time slots on a day.
     */
    static std::string requestTimeSlots();
    /**This method deals with the UI regarding the request of an event ID.
     * @pre None
     * @post None
     * @return An int that is the event id of an event if it exists, otherwise it returns -1.
     */
    static int requestID();
    /**This method deals with the UI regarding the inspection of an event.
     * @pre None
     * @post None
     */
    static void inspectEvent();
    /**
     * This method is a helper method to check user input
     * @return boolean of if user input is yes or no
     */
    static bool yesOrNo();
    /**
     * This method is a helper method to sanitize user input.
     * @param disallowed the item that should not be in the input.
     * @return An input that is guaranteed to not have the disallowedChar
     */
    static std::string sanitizeInput(std::string message, std::string disallowed);
};


#include "events.hpp"

#endif
