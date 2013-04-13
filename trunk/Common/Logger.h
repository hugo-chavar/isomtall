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
		void logInvalidValueInEntity(string entity,string field,string expected);
		void logInvalidValueInEntityDef(string entityDef,string field,string expected);
		void logInvalidValueInMainCharacter(string mainCharacter,string field,string expected);
		void logInvalidValueInStage(string stage,string field,string expected);
		void logInvalidValueInConfiguration(string configuration,string field,string expected);
		void setFile(string path);
		
	private:
		Logger();

		ofstream fd;
	};
};

#endif