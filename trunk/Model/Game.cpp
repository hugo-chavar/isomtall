#include "Game.h"
#include "Constants.h"


Game::Game()
{
   
}

Game::~Game(){
	//_world.deleteMap();
}

Game& Game::instance(){
	static Game singleton;
	return singleton;
}

StageModel* Game::world(){
	return &_world;
}

TimeManager* Game::time(){
	return &_time;
}

bool Game::initialize()
{
	yParser.parse();
	_world = yParser.vStages()[0];
	//_world.generateMap();
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

	this->_time.initializeTime();
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

PersonajeModelo * Game::personaje()
{
	if (this->_personaje){
		return this->_personaje;
	}
	Logger::instance().nullPointer("function PersonajeModelo * Game::personaje");
	return NULL;
}

Configuration* Game::configuration(){
	if (_configuration)
			return _configuration;
	Logger::instance().nullPointer("Configuration* Game::configuration");
	return NULL;
}