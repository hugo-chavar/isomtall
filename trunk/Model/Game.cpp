#include "Game.h"
#include "Constants.h"


Game::Game() {
}

Game::~Game() {
	_login.cleanUp();
}

Game& Game::instance() {
	static Game singleton;
	return singleton;
}

StageModel* Game::world() {
	return &_world;
}

TimeManager* Game::time() {
	return &_time;
}

bool Game::initialize(string nombreJugador) {
	yParser.parse();
	_world = yParser.vStages()[0];
	unsigned stageActual = 0;
	unsigned personActual = 0;
	allEntities = yParser.allLists();
	_configuration = yParser.getConfig();
	//selecciono el primero del primer stage
	_personaje = yParser.modelMainCharacters(stageActual,personActual); 

	//si hubieron problemas salgo
	if( (!_configuration) || (!_personaje) )
		return false;

	_personaje->setVelocidad(_configuration->mainCharacterSpeed());
	_personaje->setName(nombreJugador);
	_personaje->createVision(_configuration->visionRange());
	this->_time.initializeTime();
	_login.initialize();
	return true;
}

EntityObject* Game::entityObjectAt(unsigned pos) {
	if (allEntities.vEntitiesObject.size() > pos)
		return allEntities.vEntitiesObject.at(pos);
	Logger::instance().nullPointer("function EntityObject* Game::animatedEntityAt");
	return NULL;
}


AnimatedEntity* Game::animatedEntityAt(unsigned pos) {
	if (allEntities.vAnimatedEntities.size() > pos)
		return allEntities.vAnimatedEntities.at(pos);
	Logger::instance().nullPointer("function AnimatedEntity* Game::animatedEntityAt");
	return NULL;
}

PersonajeModelo * Game::personaje() {
	if (this->_personaje){
		return this->_personaje;
	}
	Logger::instance().nullPointer("function PersonajeModelo * Game::personaje");
	return NULL;
}

Configuration* Game::configuration() {
	if (_configuration)
			return _configuration;
	Logger::instance().nullPointer("Configuration* Game::configuration");
	return NULL;
}

bool Game::insidePlayerVision(std::pair<int,int> pos){
	bool inside = this->_personaje->getVision()->isInsideVision(pos);

	if (!inside) {
		TileModel* relatedTile = Game::instance().world()->getTileAt(pos)->getRelatedTile();
		if (relatedTile) {//TODO: mejorar para optimizar codigo
			// preguntar si es drawable() e ir salteando..
			while ( (!inside) && (relatedTile != Game::instance().world()->getTileAt(pos)) ) {
				pair<int, int> posRelated = relatedTile->getPosition();
				inside = this->_personaje->getVision()->isInsideVision(posRelated);
				relatedTile = relatedTile->getRelatedTile();
			}
		}
	}
	return inside;
}

bool Game::isKnownByPlayer(std::pair<int,int> pos) {
	return this->_personaje->getVision()->testPosition(pos);
}