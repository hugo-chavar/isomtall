#include "Movable.h"

Movable::Movable()/*:Entity()*/ {
	this->setVelocity(0);
	this->remaining = std::make_pair<float, float>(0, 0);
	this->setTargetReached(false);
	this->setCouldContinue(true);

}

Movable::~Movable() {
}

//------------- Getters / Setters methods  ---------------------

void Movable::setVelocity(float value) {
	this->velocity = value;
}

float Movable::getVelocity() {
	return this->velocity;
}

void Movable::setTargetTile(std::pair<int, int> value) {
	this->targetTile = value;
}

std::pair<int, int> Movable::getTargetTile() {
	return this->targetTile;
}

void Movable::setInitialTile(std::pair<int, int> value) {
	this->initialTile = value;
}

std::pair<int, int> Movable::getInitialTile() {
	return this->initialTile;
}

void Movable::setTargetReached(bool value) {
	this->targetReached = value;
}

bool Movable::isTargetReached() {
	return this->targetReached;
}

void Movable::setCouldContinue(bool value) {
	this->_couldContinue = value;
}

bool Movable::couldContinue() {
	return this->_couldContinue;
}

bool Movable::isItem() {
	return false;
}

//
//string Movable::getName() {
//	return this->name;
//}

// ------------------- Functional methods -------------------
void Movable::update() {
	//TODO: al metodo isAlive() llamar fuera de la clase y no entrar acá
	if (!this->isAlive())
		return;
	Entity::update();
	this->move();
	this->verify();
}

void Movable::render(Camera& camera) {
	//TODO: al metodo isAlive() llamar fuera de la clase y no entrar acá
	if (!this->isAlive())
		return;
	this->updateRectanglePosition(this->getPosition().first, this->getPosition().second);
	camera.render(this->spriteRect,this->sprite->getSurfaceAt(freezedSpriteState)->getSurfaceToShow(false));
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
	else
		this->setCouldContinue(false);
}

bool Movable::validTilePosition(std::pair<int, int> pixelPosition) {
	return this->isInsideWorld(this->pixelToTileCoordinates(pixelPosition));
}

void Movable::calculateWayForward() {
	this->setDirection(this->getInitialTile(), this->getTargetTile());
}

void Movable::verify() {
	if (this->pixelToTileCoordinates(this->getPosition()) == this->getTargetTile())
		this->setTargetReached(true);
	if (!this->canCross(this->pixelToTileCoordinates(this->getPosition())))
		this->setCouldContinue(false);
}

bool Movable::isAlive() {
	return (!this->isTargetReached() || this->couldContinue());
}