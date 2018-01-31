/**
*	@author Team 3
*	@date 
*	@file interface.hpp
*/

template <typename T>
Interface<T>::Interface()
{

}

template <typename T>
Interface<T>::~Interface() 
{
	
}

template <typename T>
void Interface<T>::clearScreen()
{
	std::cout << "\033[2J\033[1;1H";
}
