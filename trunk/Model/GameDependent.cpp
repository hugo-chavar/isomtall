#include "GameDependent.h"
#include "Game.h"
#include "../View/GameView.h"

GameDependent::GameDependent() {
}

GameDependent::~GameDependent() {
}

float GameDependent::getDeltaTime() {
	return Game::instance().getTimer()->getDeltaTime();
}

std::pair<int, int> GameDependent::pixelToTileCoordinates(std::pair<int, int> pixelPosition) {
	return Game::instance().world()->pixelToTileCoordinates(pixelPosition);
}

bool GameDependent::isInsideWorld(std::pair<int, int> tilePosition) {
	return Game::instance().world()->isInsideWorld(tilePosition);
}

bool GameDependent::canCross(std::pair<int, int> tilePosition) {
	return (Game::instance().world()->cost(tilePosition.first, tilePosition.second) == 1);
}

Sprite* GameDependent::getSpriteWithName(std::string value) {
	return GameView::instance().getWorldView()->getSpriteWithName(value);
}