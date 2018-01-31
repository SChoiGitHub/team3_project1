/**
*	@author Team 3
*	@date 
*	@file io.hpp
*/

template <typename T>
IO<T>::IO(std::string filename) : file(filename)
{
	f.open(file, std::ios::out | std::ios::app);
}

template <typename T>
IO<T>::~IO() 
{
	f.close();
}

template <typename T>
void IO<T>::addEvent()
{
	
}

template <typename T>
T IO<T>::retrieveElement(int ID, std::string elementName)
{
	
}

template <typename T>
void IO<T>::updateElement(int ID, std::string elementName, void* value)
{
	
}


