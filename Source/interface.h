#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include "log.h"
#include "io.h"

class Interface
{
public:
    
    /** @pre None
     *   @post Constructor
     */
    Interface();
    
    /** @pre None
     *   @post Destructor
     */
    ~Interface();
    
    /** @pre None
     *   @post Clears terminal
     *   @return None
     */
    static void clearScreen();
    
    /** @pre wait_string is a message shown to the user while waiting
     *   @post Waits for the user to press enter
     *   @return None
     */
    static void Wait(std::string wait_string);
    
    /** @pre None
     *   @post Toggles the time format between 12-hour and 24-hour formats
     *   @return None
     */
    static void toggleTimeFormat();

    /** 
     * Method for extracting a comma-free name from the end-user
     * @pre none
     * @post none
     * @return A string sanitized of commas
     */
    std::string getName();

    class Menu
    {
    public:
        
        /** @pre options is a vector of pairs, where each pair is composed of a string (referring to
         *    a menu option, and a pointer to the corresponding callback function
         *   @post Constructor for Menu class object
         */
        Menu(const std::vector<std::pair<std::string, void (*)()>> &options);
        
        /** @pre None
         *   @post A menu loop
         *   @return None
         */
        void Loop();
        
	/** @pre None
         *   @post Draws a header for a menu
         *   @return None
         */
        void Header();

    private:
        
        std::vector<std::pair<std::string, void (*)()>> option_list;    //Vector of pairs
        
        /** @pre None
         *   @post Draws a menu
         *   @return None
         */
        void Draw();

	/** @pre message is the input request message string presented to the user
	 *   @post requests user input
	 *   @return Returns the user's given input
	 */
	static std::string getInput(const char *message); 
    };
    
    
    
private:
    
    Log logFile;
    
};

#include "interface.hpp"

#endif

