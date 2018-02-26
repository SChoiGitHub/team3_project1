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



    /** @pre ID is the event's unique identifier. elementName is the name of the element to retrieve
     *   @post Retrieves some event's specific element value from the events file
     *   @return Returns event's specific element (string or int)
     */
    std::string retrieveElement(int ID, std::string elementName);

    /** @pre ID is the event's unique identifier. elementName is the name of the element to update, value is
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

//----------------------------------------------------------------------------//
    /*
    * Adds a task to the tasks file
    * @param id - the event id
    * @param name - the event's name
    * @param creator - the name of the events creator
    * @pre this is a new event
    * @post new task is add to the tasks file
    * @return event's id
    */
    int storeEvent(std::string name, std::string creator);



    /*
    * Adds a date and respective times to the schedules file
    * @param id - id of the event to which the schedule belongs
    * @param date - a date that is part of the event
    * @param times - list of times on the day
    * @post new schedule is added to the schedules file
    */
    void storeSchedule(int id, std::string date, std::list<std::string> times);



    /*
    * Adds a task to the tasks file
    * @param id - id of the event to which the task belongs
    * @param name - name/description of the task
    * @param taken - true if task has assignee false otherwise
    * @param assignee - name of the person responsible for the task
    * @post new task is added to the tasks file
    */
    void storeTask(int id, std::string name, bool taken, std::string assignee);



    /*
    * Adds the attendees for a specific date and time to files
    * @param id - id of the event to which the schedule belongs
    * @param date - one date that is part of an event
    * @param time - one time in the day of the event
    * @param atendees - list of attendees that are attending at specified times
    * @post a new list of attendence is added to the files
    */
    void storeAttendees(int id, std::string date, std::string time, std::list<std::string> attendees);

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

    /*
    * Generic method that addes a line to a file
    * @param file - file to store data in
    * @param data - string of csv data to store
    * @post Adds new event to file
    */
    void addEntry(std::fstream file, std::string data);

};

#include "io.hpp"

#endif