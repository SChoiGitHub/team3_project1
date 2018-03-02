/**
 *    @author    Team 3
 *    @date
 *    @brief A header file for Input/Output (IO) class
 */

#ifndef IO_H
#define IO_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <list>
#include "log.h"

class IO{
public:

    static bool timeFormat;
    int size;        //Number of entries in file

    /*
     *   @post Files are opened with the appropriate name
     */
    IO();

    /*
     *   @post Files are closed
     */
    ~IO();



    /**
     * @note this method is depricated and should no longer be used
     * @pre ID is the event's unique identifier. elementName is the name of the element to retrieve
     * @post Retrieves some event's specific element value from the events file
     * @return Returns event's specific element (string or int)
     */
    std::string retrieveElement(int ID, std::string elementName);

    /**
     * @note this method is depricated and should no longer be used.
     *   @pre ID is the event's unique identifier. elementName is the name of the element to update, value is
     *     the element's new value
     *   @post Updates some event's specific element
     *   @return None
     */
    void updateElement(int ID, std::string elementName, void* value);

    /** @pre None
     *   @post Displays all elements in file, one at a time
     *   @return None
     */
    void displayEntries();


    /** @pre slot has the time value that needs to be formatted
     *   @post Formats time between 12-hour format and 24-hour format
     *   @return String with slot in new time format
     */
    std::string timeFormatter(std::string slot);

    //--Event-----------------------------------------------------------------//

    /**
    * Adds a task to the tasks file
    * @param id - the event id
    * @param name - the event's name
    * @param creator - the name of the events creator
    * @pre this is a new event
    * @post new task is add to the tasks file
    * @return event's id
    */
    int storeEvent(std::string name, std::string creator);

    /**
    * Gets an event
    * @param id - id of the event
    * @pre id coresponds to an event
    * @return a pair that contains the event's name and creator
    */
    std::pair<std::string, std::string> obtainEvent(int id);

    //--Schedules-------------------------------------------------------------//

    /**
    * Adds a date and respective times to the schedules file
    * @param id - id of the event to which the schedule belongs
    * @param date - a date that is part of the event
    * @param times - list of times on the day
    * @post new schedule is added to the schedules file
    */
    void storeSchedule(int id, std::string date, std::list<std::string> times);

    /**
    * Returns all the schedules
    * @note an empty list will be returned if there are no stored schedules
    * @param id - id of the event for which you are trying to retrieve all the schedules
    * @pre the id is a valid id that has some schedule
    * @return a list of schedules which are a date and times for that date
    */
    std::list<std::pair<std::string, std::list<std::string>>>* obtainSchedules(int id);

    /**
    * Returns a schedule
    * @note an null pointer will be returned if no schedule is found
    * @param id - id of the event for which the is needed
    * @param date - the date for which the schedule is needed
    * @pre the id is a valid id
    * @return a list of times
    */
    std::list<std::string>* obtainSchedule(int id, std::string date);

    //--TASK------------------------------------------------------------------//

    /**
    * Adds a task to the tasks file
    * @param id - id of the event to which the task belongs
    * @param name - name/description of the task
    * @param taken - true if task has assignee false otherwise
    * @param assignee - name of the person responsible for the task
    * @post new task is added to the tasks file
    */
    void storeTask(int id, std::string name);

    /**
    * Sets the person assigned to complete a task.
    * @param id - the id of the event
    * @param name - the name of the task
    * @param assignee - person to be assigned
    * @pre Task is already stored in the file
    * @post task has an assignee
    */
    void storeTaskAssignee(int id, std::string name, std::string assignee);

    //--Attendence------------------------------------------------------------//

    /**
    * Adds an attendee to a date and time
    * @param id - id of the event
    * @param date - date of the time slot
    * @param time - time of the time slot
    * @param attendee - name of the attendee
    * @pre Assumes a valid date and time
    * @post attendee is added stored in appropriate file
    */
    void storeAttendee(int id, std::string date, std::string time, std::string attendee);

    /**
    * Adds the attendees for a specific date and time to files
    * @param id - id of the event to which the schedule belongs
    * @param date - one date that is part of an event
    * @param time - one time in the day of the event
    * @param atendees - list of attendees that are attending at specified times
    * @post a new list of attendence is added to the files
    */
    void storeAttendees(int id, std::string date, std::string time, std::list<std::string> attendees);

    /**
    * Gets the attendees for a specific date.
    * @note Will return a null pointer if a list of attendees can not be found
    * @param id - id of the event for which the attendees are needed
    * @param date - the day for which the attendees are needed
    * @param time - the time for which attendees are needed
    * @return list of attendees
    */
    std::list<std::string>* obtainAttendees(int id, std::string date, std::string time);

private:
    Log logFile;            //Log object
    int numEvents;

    const std::string EVENTS_FILE;
    const std::string TASKS_FILE;
    const std::string SCHEDULES_FILE;
    const std::string ATTENDENCE_FILE;

    std::fstream eventsFile;
    std::fstream tasksFile;
    std::fstream schedulesFile;
    std::fstream attendenceFile;

    //--File Manipulation-----------------------------------------------------//
    /**
    * Generic method that gets a line from a file.
    * @note Should be used in situations where the identifier is unique
    * @note Will not return the identifier with the entry
    * @param file - file stream to read from
    * @param identifier - part of an entry that will identify the entry
    * @return string that is corisponding entry
    */
    std::string getEntry(std::fstream& file, std::string identifier);

    /**
    * Generic method that returns entries from a file
    * @note Should be used when there are multiple entries with the same identifier
    * @note Will not return the identifier as part of the entries
    * @param file - file stream to read from
    * @param identifier - part of an entry that will identify the entry
    * @return list of entries
    */
    std::list<std::string>* getEntries(std::fstream& file, std::string identifier);

    /**
    * Generic method that adds a line to a file
    * @param file - file to store data in
    * @param data - string of csv data to store
    * @post Adds new event to file
    */
    void addEntry(std::fstream& file, std::string data);

    /**
    * Generic method that replaces a line in a file
    * @param file - file that needs to be modified
    * @param fileName - the name of the file that is part of the file stream
    * @param identifier - a unique string that will identify the entry that needs replaced
    * @param revised - the new version of the entry
    * @pre line is in the file
    * @post line in a file is replaced with a new value
    */
    void replaceEntry(std::fstream& file, std::string fileName, std::string identifier, std::string revised);

};

#include "io.hpp"

#endif
