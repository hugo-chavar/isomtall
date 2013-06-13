#include "Movable.h"
#include "Game.h"

Movable::Movable()//:Entity(tileX,tileY,spriteCargado)
{
	this->velocity = 0;
	this->remaining = std::make_pair<float, float>(0, 0);

}
//
//string Movable::getName() {
//	return this->name;
//}

Movable::~Movable() {
}

void Movable::update() {
	Entity::update();
	this->move();
}

void Movable::render(Camera& camera) {
	camera.render(this->spriteRect,this->sprite->getSurfaceAt(freezedSpriteState)->getSurfaceToShow(false));
}

void Movable::setVelocity(float veloc) {
	this->velocity = veloc;
}

float Movable::getVelocity() {
	return this->velocity;
}

void Movable::move() {
	std::pair<float, float> deltaMovement;
	float deltaVelocity = this->getVelocity()*this->getDeltaTime();
	deltaMovement.first = deltaVelocity*this->getDirection().first + this->remaining.first;
	deltaMovement.second = deltaVelocity*this->getDirection().second/2 + this->remaining.second;
	this->remaining.first = deltaMovement.first - std::floor(deltaMovement.first);
	this->remaining.second = deltaMovement.second - std::floor(deltaMovement.second);
	std::pair<int, int> newPosition;
	newPosition.first = this->getPosition().first + static_cast<int>(std::floor(deltaMovement.first));
	newPosition.second = this->getPosition().second + static_cast<int>(std::floor(deltaMovement.second));
	if (this->validTilePosition(newPosition))
		this->setPosition(newPosition);
}

std::pair<int, int> Movable::getTilePosition(std::pair<int, int> pixelPosition) {
	return (Game::instance().world())->pixelToTileCoordinates(pixelPosition);
}

bool Movable::validTilePosition(std::pair<int, int> pixelPosition) {
	std::pair<int, int> tilePosition = this->getTilePosition(pixelPosition);
	return (Game::instance().world())->isInsideWorld(tilePosition);
}