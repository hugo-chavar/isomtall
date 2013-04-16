#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <fstream>
#include <string>

using namespace std;

namespace common
{
	class Logger
	{
	public:
		~Logger();

		static Logger& instance();

		void log(string line);
		void logUnexpected(string line);
		void logSyntaxError(string file,string line);
		void logInvalidValue(string entity,string field, string affectedConfig, string expected);
		void logFieldNotDefined(string entity, string field, string affectedConfig);
		void logFatalError(string line);
		void nullPointer(string line);
		void setFile(string path);
		
	private:
		Logger();

		ofstream fd;
	};
};

#endif