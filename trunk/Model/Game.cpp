#include "Game.h"
#include "Constants.h"
//#include "ClientUpdater.h"


Game::Game() {
}

Game::~Game() {
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

bool Game::initialize() {
	yParser.parse(CONFIGFILE_DIRECTORY, false);
	_world = yParser.vStages()[this->getStageNumber()];
	_world.loadNamedChars();
	allEntities = yParser.allLists();
	_configuration = yParser.getConfig();
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

Configuration* Game::configuration() {
	return &_configuration;
}

int Game::getStageNumber() {
	return this->stageNumber;
}

void Game::setStageNumber(int stageNo) {
	this->stageNumber = stageNo;
}