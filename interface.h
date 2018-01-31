#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>

template <typename T>
class Interface
{
	public:

	/** @pre None
	*   @post Start terminal interface object
	*/
	Interface();

	/** @pre None
	*   @post Destroy terminal interface object
	*/
	~Interface();

	/** @pre None
	*   @post Clears terminal
	*   @return None
	*/
	void clearScreen();


	private:
    
	
};

#include "interface.hpp"

#endif
