#include "TimeManager.h"

#include "SDL.h"

TimeManager::TimeManager() {
	this->startTime = 0;
	this->deltaTime = 0;
}

void TimeManager::initializeTime() {
	startTime = SDL_GetTicks();
}

void TimeManager::updateTime() {
	deltaTime = (static_cast<float>(SDL_GetTicks() - startTime) / 1000);
	startTime = SDL_GetTicks();
}

float TimeManager::getDeltaTime() {
	return deltaTime;
}

TimeManager::~TimeManager() {
}