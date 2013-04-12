#include "TimeManager.h"

#include "SDL.h"

model::TimeManager::TimeManager() {
	this->startTime = 0;
	this->deltaTime = 0;
}

void model::TimeManager::initializeTime() {
	startTime = SDL_GetTicks();
}

void model::TimeManager::updateTime() {
	deltaTime = (static_cast<float>(SDL_GetTicks() - startTime) / 1000);
	startTime = SDL_GetTicks();
}

float model::TimeManager::getDeltaTime() {
	return deltaTime;
}

model::TimeManager::~TimeManager() {
}