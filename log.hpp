/**
*	@author Team 3
*	@date 
*	@file log.hpp
*/

Log::Log()
{
	logFile.open("error.log", std::ios::out | std::ios::app);
}

Log::~Log() 
{
	logFile.close();
}

void Log::addEntry(std::string error_type, std::string function_responsible)
{
	time_t rawtime;
	time (&rawtime);

	logFile << "\nDate and Time: " << ctime(&rawtime) << "Type: " << error_type << "\n" << "Function: " << function_responsible << std::endl;

	++size;

	std::cout << "Error log entry added <- " << error_type << std::endl;
}
