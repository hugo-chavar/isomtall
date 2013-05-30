#ifndef _STRINGUTILITIES_H_
#define _STRINGUTILITIES_H_

#include <string>
#include <vector>


namespace stringUtilities {

	//Metodo para dividir un string según un separador indicado.
	void splitString(std::string string, std::vector<std::string>& splittedString, char delimiter);

	//Indica si el string es numerico.
	bool isNumeric(std::string string);

	//Metodo para rellenar a izquierda con el caracter indicado hasta la longitud indicada.
	std::string padLeft(std::string string, char padWith, unsigned int padTo);

	//Metodo para rellenar a derecha con el caracter indicado hasta la longitud indicada.
	std::string padRight(std::string string, char padWith, unsigned int padTo);

	//Metodo para convertir un string a int.
	int stringToInt(const std::string Text);

	//Metodo para convertir un string a unsigned.
	unsigned stringToUnsigned(const std::string Text);

	//Metodo para convertir un int a string.
	std::string intToString(int i);

	//Metodo para convertir un unsigned a string.
	std::string unsignedToString(unsigned i);

	//Metodo para convertir un long a string.
	std::string longToString(long int l);

	//Metodo para convertir un float a string.
	std::string floatToString(float f);

	//Metodo para remover los espacios en blanco al comienzo y al final del string.
	std::string trim(std::string string);

	std::string replaceCharForString(char charR,char* buff,int size,std::string replacer);

	//devuelve el tamanio del vector de chars;
	int replaceStringForChar(char charR,char* buff,std::string replaced,std::string toConvert);

	std::string pairIntToString(std::pair<int, int> key);

	std::string pairUnsignedToString(std::pair<unsigned, unsigned> key); 

	std::pair<int, int> stringToPairInt(std::string source);

	std::pair<unsigned, unsigned> pairUnsignedToString(std::string source); 

}

#endif // _STRINGUTILITIES_H_