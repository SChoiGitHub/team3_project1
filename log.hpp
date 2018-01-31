/**
*	@author Team 3
*	@date 
*	@file log.hpp
*/

template <typename T>
Log<T>::Log()
{
	logFile.open("error.log", std::ios::out | std::ios::app);
}

template <typename T>
Log<T>::~Log() 
{
	logFile.close();
}

template <typename T>
void Log<T>::addEntry(std::string error_type, std::string function_responsible)
{
	time_t rawtime;
	time (&rawtime);

	logFile << "\nDate and Time: " << ctime(&rawtime) << "Type: " << error_type << "\n" << "Function: " << function_responsible << std::endl;

	++size;

	std::cout << "Error log entry added <- " << error_type << std::endl;
}
