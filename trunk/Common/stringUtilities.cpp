#include "StringUtilities.h"

#include <sstream>

namespace stringUtilities {

	void splitString(std::string string, std::vector<std::string>& splittedString, char delimiter) {
		unsigned int from = 0;
		unsigned int to = 0;

		splittedString.clear();
		while (to != string.npos) {
			to = string.find(delimiter,from);
			splittedString.push_back(string.substr(from,(to-from)));
			from = to + 1;
		}
	}

	bool isNumeric(std::string string) {
		if (string == "") {
			return false;
		} else {
			for (unsigned int i = 0; i < string.size(); i++) {
				if (!isdigit(string[i])) {
					return false;
				}
			}
		}
		return true;
	}

	std::string padLeft(std::string string, char padWith, unsigned int padTo) {
		std::string paddedString = "";

		if (padTo >= string.size()) {
			for (unsigned int i = 0; i < (padTo - string.size()); i++) {
				paddedString += padWith;
			}
		}

		paddedString += string;

		return paddedString;
	}

	std::string padRight(std::string string, char padWith, unsigned int padTo) {
		std::string paddedString = string;

		if (padTo >= string.size()) {
			for (unsigned int i = 0; i < (padTo - string.size()); i++) {
				paddedString += padWith;
			}
		}

		return paddedString;
	}

	int stringToInt(const std::string Text) {
		int result;
		std::stringstream stringstream(Text);
		return stringstream >> result ? result : 0;
	}

	unsigned stringToUnsigned(const std::string Text){
		return static_cast<unsigned>(stringToInt(Text));
	}

	std::string intToString(int i) {
		std::stringstream stringstream;
		stringstream << i;
		return stringstream.str();
	}

	std::string unsignedToString(unsigned i) {
		int aux = static_cast<int>(i);
		return intToString(aux);
	}

	std::string floatToString(float f) {
		std::stringstream stringstream;
		stringstream << f;
		return stringstream.str();
	}

	std::string trim(std::string string) {
		unsigned int from = 0;
		unsigned int to = string.size();
		bool finished = false;

		for (unsigned int i = 0; (i < string.size()) && !finished; i++) {
			if (string[i] == ' ')
				from++;
			else
				finished = true;
		}

		finished = false;
		for (unsigned int i = string.size() - 1; (i >= 0) && !finished; i--) {
			if (string[i] == ' ')
				to--;
			else
				finished = true;
		}

		return string.substr(from,to);
	}

	std::string replaceCharForString(char charR,char* buff,int size,std::string replacer)
	{
		std::string result="";
		for(int i=0;i<size;i++)
		{
			if(buff[i]==charR)
			{
				result+=replacer;
			}
			else
				result+=buff[i];
		}
		return result;
	}
	std::string pairIntToString(std::pair<int, int> key) {
		std::string aux = intToString(key.first)+","+intToString(key.second);
		return aux;
	}

	std::string pairUnsignedToString(std::pair<unsigned, unsigned> key) {
		std::string aux = unsignedToString(key.first)+","+unsignedToString(key.second);
		return aux;
	}

	std::pair<int, int> stringToPairInt(std::string source) {
		std::vector <std::string> auxVector;
		splitString(source, auxVector, ',');
		std::pair<int, int> auxPair = std::make_pair(stringToInt(auxVector[0]), stringToInt(auxVector[1]));
		return auxPair;
	}

	std::pair<unsigned, unsigned> pairUnsignedToString(std::string source) {
		std::vector <std::string> auxVector;
		splitString(source, auxVector, ',');
		std::pair<unsigned, unsigned> auxPair = std::make_pair(stringToUnsigned(auxVector[0]), stringToUnsigned(auxVector[1]));
		return auxPair;
	}



	int replaceStringForChar(char charR,char* buff,std::string replaced,std::string toConvert)
	{
		std::vector<int> posiciones; 
		int posicion=toConvert.find(replaced,0);
		while(posicion!=-1)
		{
			posiciones.push_back(posicion);
			posicion=toConvert.find(replaced,posicion+1);
		}
		int i=0;
		int chars=0;
		int pos=0;
		while(i<posiciones.size())
		{	
			while(pos<posiciones[i])
			{
				buff[chars]=toConvert[pos];
				chars++;
				pos++;
			}
			buff[chars]=charR;
			chars++;
			pos+=replaced.size();
			i++;
		}
		while(pos<toConvert.size())
		{
			buff[chars]=toConvert[pos];
			chars++;
			pos++;
		}

		return chars;
	}

} // namespace StringUtilities