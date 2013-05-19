#include "CharacterFactory.h"
#include "Game.h"


CharacterFactory::CharacterFactory() {
}

CharacterFactory::~CharacterFactory() {
}

PersonajeModelo* CharacterFactory::createModelCharacter(std::string entityName) {
	PersonajeModelo* newCharacter = new PersonajeModelo();
	PersonajeModelo* source = Game::instance().world()->getCharacter(entityName); //devuelve default si no existe entityName
	if (source == NULL)
		return NULL;
	*newCharacter = (*source);
	newCharacter->setVelocidad(Game::instance().configuration()->mainCharacterSpeed());
	newCharacter->createVision(Game::instance().configuration()->visionRange());
	return newCharacter;
}

Personaje* CharacterFactory::createViewCharacter(std::string entityName, std::string playerName) {
	Personaje* newViewCharacter = new Personaje(this->createModelCharacter(entityName));
	newViewCharacter->setPlayerName(playerName);
	newViewCharacter->loadSprites();
	return newViewCharacter;
}
