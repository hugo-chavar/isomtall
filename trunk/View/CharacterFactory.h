#ifndef _CHARACTERFACTORY_H_
#define _CHARACTERFACTORY_H_

#include "PersonajeModelo.h"
#include "Personaje.h"


class CharacterFactory {
public:
	CharacterFactory();
	~CharacterFactory();
	PersonajeModelo* createModelCharacter(std::string entityName); //en el modelo queda el nombre de lo que viene del yaml, ej: "frodo"
	Personaje* createViewCharacter(std::string entityName, std::string playerName); //playerName es el nombre q ingresa el cliente

private:

};


#endif