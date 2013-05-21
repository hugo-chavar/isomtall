#include <iostream>
//#include <ctime>
#include <time.h>
#include "Logger.h"
using namespace common;

 
Logger::Logger()
{
   
}

Logger::~Logger()
{
	fd.close();
}
Logger& Logger::instance()
{
	static Logger singleton;
	return singleton;
}

void Logger::setFile(string path)
{
	fd.open (path.c_str(), std::ios::trunc|std::ios::out);
	if (!fd)
	{
		std::cerr<<"No se pudo abrir el archivo de log."<<std::endl;
	}
}

void Logger::log(string line)
{
	string message = "["+ this->timeStamp()+"] ";
	message.append(line);
	this->logWithoutTimeStamp(message);
}

void Logger::logUnexpected(string line)
{
	string message = "Parser error: Unexpected error ocurred described by: \n";
	message.append(line);
	this->log(message);
}

void Logger::logSyntaxError(string file, string line)
{
	string message = "Parser error: Unable to load '"+file+"' Parser returned this error:\n";
	message.append(line);
	this->log(message);
}

void Logger::logInvalidValue(string entity,string field, string affectedConfig, string expected)
{
	string message = "Parser Error: Invalid value in field '"+field+"' in "+affectedConfig+" '"+entity+"' "+expected+" was expected.";
	this->log(message);
}

void Logger::logFieldNotDefined(string entity, string field, string affectedConfig)
{
	string message = "Parser Error: Field '"+field+"' is not defined in "+affectedConfig+" '"+entity+"'.";
	this->log(message);
}

void Logger::logFatalError(string line)
{
	string message = "Fatal aplication error: ";
	message.append(line);
	this->log(message);
}

void Logger::nullPointer(string line)
{
	string message = line;
	message.append(" returned a NULL pointer.");
	this->logFatalError(message);
}

std::string Logger::timeStamp() {
       struct tm newtime;
        char am_pm[] = "AM";
        __time64_t long_time;
        char timebuf[26];
		char result[28];
        errno_t err;

        // Get time as 64-bit integer.
        _time64( &long_time ); 
        // Convert to local time.
        err = _localtime64_s( &newtime, &long_time ); 
        if (err)
        {
           return "";
        }
        if( newtime.tm_hour > 12 )        // Set up extension. 
                strcpy_s( am_pm, sizeof(am_pm), "PM" );
        if( newtime.tm_hour > 12 )        // Convert from 24-hour 
                newtime.tm_hour -= 12;    // to 12-hour clock. 
        if( newtime.tm_hour == 0 )        // Set hour to 12 if midnight.
                newtime.tm_hour = 12;

        // Convert to an ASCII representation. 
        err = asctime_s(timebuf, 26, &newtime);
        if (err)
        {
           return "";
        }
		strcpy_s (result,timebuf);
		strcat_s(result, 28, am_pm);
		std::string x(timebuf);
		return x;
        //printf( "%.19s %s\n", timebuf, am_pm );
}

void Logger::logWithoutTimeStamp(string line) {
	if (fd)	{
		fd << line << std::endl; 
	}
}