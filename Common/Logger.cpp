#include <iostream>
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
	if (fd)
	{
		fd << line << std::endl; 
	}
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