#include "Game.h"
#include "Constants.h"
//#include "yaml.h"


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
	YAMLParser yParser;
	yParser.parse(CONFIGFILE);
	_world = yParser.vStages()[0];
	_personaje = new PersonajeModelo(_world.vMainCharacters()[0]);
	_vEntitiesObject = yParser.vEntitiesObject();
	_vAnimatedEntities = yParser.vAnimatedEntities();

}

vector <EntityObject> Game::vEntitiesObject(){
	return _vEntitiesObject;
}

vector <AnimatedEntity> Game::vAnimatedEntities() {
	return _vAnimatedEntities;
}

PersonajeModelo * Game::personaje()
{
	return this->_personaje;
}