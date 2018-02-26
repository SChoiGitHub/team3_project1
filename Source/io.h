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

class IO
{
public:

    static bool timeFormat;
    int size;        //Number of entries in file

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
    * @pre none
    * @post new task is add to the tasks file
    * @return none
    */
    void storeEvent(int id, std::string name, std::string creator);



    /*
    * Adds a date and respective times to the schedules file
    * @param id - id of the event to which the schedule belongs
    * @param date - a date that is part of the event
    * @param times - list of times on the day
    * @post new schedule is added to the schedules file
    */
    void storeDate(int id, std::string date, std::list<std::string> times);



    /*
    * Adds a task to the tasks file
    * @param id - id of the event to which the task belongs
    * @param name - name/description of the task
    * @param taken - true if task has assignee false otherwise
    * @param assignee - name of the person responsible for the task
    * @post new task is added to the tasks file
    */
    void storeTask(int id, std::string name, bool taken, std::string assignee);

private:

    std::fstream file;        //File stream
    std::string fileName_;        //Name of file
    Log logFile;            //Log object

};

#include "io.hpp"

#endif
