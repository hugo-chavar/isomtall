#include "Game.h"
#include "Constants.h"
//#include "ClientUpdater.h"


Game::Game() { }

Game::~Game() {
}

Game& Game::instance() {
	static Game singleton;
	return singleton;
}

StageModel* Game::world() {
	return &_world;
}

TimeManager* Game::getTimer() {
	return &_time;
}

bool Game::initialize() {
	yParser.parse(CONFIGFILE_DIRECTORY, false);
	//_world = yParser.vStages()[this->getStageNumber()];
	//_world.loadNamedChars();
	srand((unsigned)time(NULL));
	this->startWorld();
	allEntities = yParser.allLists();
	_configuration = yParser.getConfig();
	this->_time.initializeTime();
	return true;
}

float Game::getRandom() {
	float max = 1.0;
	float min = 0.0;
	return (float)(((float) rand() / (((float)RAND_MAX) + 1.0)) * (max-min+1) + min);
}
void Game::restart() {
	this->_world = yParser.vStages()[this->getStageNumber()];
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

void Game::startWorld() {
	this->_world = yParser.vStages()[this->getStageNumber()];
	this->_world.loadNamedChars();
}