#include "CharacterFactory.h"
#include "Game.h"
#include "GameView.h"


CharacterFactory::CharacterFactory() {
}

CharacterFactory::~CharacterFactory() {
	std::vector <std::pair<std::string, Personaje*> >::iterator it;
	it = this->poolPersonajes.begin();
	while (it != poolPersonajes.end()) {
		if (it->second) {
			delete it->second;
		}
		it++;

	}
	this->poolPersonajes.clear();
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
	std::vector <std::pair<std::string, Personaje*> >::iterator it;
	it = poolPersonajes.begin();
	Personaje* aux = NULL;
	bool found = false;
	while (!found && (it != poolPersonajes.end()) ) {
		if (it->first == entityName) {
			if (it->second->isAvailable()) {
				found = true;
				aux = it->second;
			}
		}
		it++;
	}

	if (!found) {
		aux = this->create(entityName);
		this->poolPersonajes.push_back(std::make_pair<std::string, Personaje *>(entityName, aux));
	}
	aux->setAvailable(false);
	aux->setPlayerName(playerName);
	return aux;
}

Personaje* CharacterFactory::create(std::string entityName) {
	Personaje* newViewCharacter = new Personaje(this->createModelCharacter(entityName));
	newViewCharacter->setFont(GameView::instance().getFontSize(12));
	newViewCharacter->loadSprites();
	newViewCharacter->loadWeapons();
	newViewCharacter->setAvailable(true);
	return newViewCharacter;
}

void CharacterFactory::initialize() {
	std::string name = "frodo";
	Personaje* personaje = this->create(name);
	this->poolPersonajes.push_back(std::make_pair<std::string, Personaje *>(name, personaje));
	personaje = NULL;
	name = "mago";
	personaje = this->create(name);
	this->poolPersonajes.push_back(std::make_pair<std::string, Personaje *>(name, personaje));
}

void CharacterFactory::remove(Personaje* character) {
	std::vector <std::pair<std::string, Personaje*> >::iterator it;
	it = this->poolPersonajes.begin();
	bool found = false;
	while (!found && (it != poolPersonajes.end()) ) {
		if (it->second == character) {
			if (!it->second->isAvailable()) {
				found = true;
			}
		}
		if (!found)
			it++;
	}
	this->poolPersonajes.erase(it);
	delete character;
}