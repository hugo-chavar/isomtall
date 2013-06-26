#ifndef _CHARACTERFACTORY_H_
#define _CHARACTERFACTORY_H_

#include <vector>
#include <string>
#include "PersonajeModelo.h"
#include "Personaje.h"


class CharacterFactory {
public:
	CharacterFactory();
	~CharacterFactory();
	void initialize();
	PersonajeModelo* createModelCharacter(std::string entityName); //en el modelo queda el nombre de lo que viene del yaml, ej: "frodo"
	Personaje* createViewCharacter(std::string entityName, std::string playerName); //playerName es el nombre q ingresa el cliente
	Personaje* create(std::string entityName);
	void remove(Personaje* character);

private:
	std::vector <std::pair<std::string, Personaje*> > poolPersonajes;

};


#endif