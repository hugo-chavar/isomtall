#include "Game.h"
#include "Constants.h"


#define PATH "test.yaml"


using namespace model;

Game::Game()
{
   
}


Game::~Game()
{
}

Game& Game::instance()
{
	static Game singleton;
	return singleton;
}

Stage& Game::world()
{
	return _world;
}

TimeManager& Game::time() {
	return this->_time;
}

void Game::initialize()
{
	yParser.parse(CONFIGFILE);
	_world = yParser.vStages()[0];
	unsigned stageActual = 0;
	unsigned personActual = 0;
	allEntities = yParser.allLists();
	_cameraModel = yParser.cameraModel();
	//selecciono el primero del primer stage
	_personaje = yParser.modelMainCharacters(stageActual,personActual); 
	//setear velocidad personaje

	this->_time.initializeTime();
	

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
		//string a = this->_personaje.animation
	}
	Logger::instance().nullPointer("function PersonajeModelo * Game::personaje");
	return NULL;
}

CameraModel* Game::cameraModel(){
	if (_cameraModel)
			return _cameraModel;
	Logger::instance().nullPointer("function CameraModel* Game::cameraModel");
	return NULL;
}