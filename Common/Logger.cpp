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
	fd.open (path.c_str(), std::ios::out);
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