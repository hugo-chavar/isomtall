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

//Metodo para convertir un int a string.
std::string intToString(int i);

//Metodo para convertir un unsigned a string.
std::string unsignedToString(unsigned i);

//Metodo para convertir un float a string.
std::string floatToString(float f);

//Metodo para remover los espacios en blanco al comienzo y al final del string.
std::string trim(std::string string);

}

#endif // _STRINGUTILITIES_H_