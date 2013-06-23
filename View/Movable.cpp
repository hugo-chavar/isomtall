#include "Movable.h"
#include "Logger.h"
#include "../Common/StringUtilities.h"

Movable::Movable() {
	this->setVelocity(0);
	this->remaining = std::make_pair<float, float>(0, 0);
	this->setTargetReached(false);
	this->setCouldContinue(true);
	//this->setBouncing(false);

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

void Movable::setCurrentTile(std::pair<int, int> value) {
	this->currentTile = value;
}

std::pair<int, int> Movable::getCurrentTile() {
	return this->currentTile;
}

void Movable::setLastTile(std::pair<int, int> value) {
	this->lastTile = value;
}

std::pair<int, int> Movable::getLastTile() {
	return this->lastTile;
}

void Movable::setTargetReached(bool value) {
	this->targetReached = value;
}

bool Movable::isTargetReached() {
	return this->targetReached;
}
//
//void Movable::setBouncing(bool value) {
//	this->bouncing = value;
//}
//
//bool Movable::isBouncing() {
//	return this->bouncing;
//}

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
	//TODO: ver si necesito datos de la camara para calcular la posicion
	this->updateRectanglePosition(this->getPosition().first, this->getPosition().second);
	camera.render(this->spriteRect,this->sprite->getSurfaceAt(this->getOrientation())->getSurfaceToShow(false));
}

void Movable::move() {
	std::pair<float, float> deltaMovement;
	float deltaTime = this->getDeltaTime();
	float deltaVelocity = this->getVelocity()*deltaTime;//0.02;//
	deltaMovement.first = deltaVelocity*this->getPixelDirection().first + this->remaining.first;
	deltaMovement.second = deltaVelocity*this->getPixelDirection().second/2 + this->remaining.second;
	float deltaFirst = (deltaMovement.first < 0) ? std::ceil(deltaMovement.first) : std::floor(deltaMovement.first);
	float deltaSecond = (deltaMovement.second < 0) ? std::ceil(deltaMovement.second):std::floor(deltaMovement.second);
	if ( this->goingDiagonal() && (std::abs(deltaFirst) > 0) && (std::abs(deltaSecond) == 0) && (std::abs(deltaMovement.second) > 0)) {
		this->remaining.first = deltaMovement.first;
		this->remaining.second = deltaMovement.second;
	} else {
		
		this->remaining.first = deltaMovement.first - deltaFirst;
		this->remaining.second = deltaMovement.second - deltaSecond;
		std::pair<int, int> newPixelPosition;
		newPixelPosition.first = this->getPosition().first + static_cast<int>(deltaFirst);
		newPixelPosition.second = this->getPosition().second + static_cast<int>(deltaSecond);
		this->setPosition(newPixelPosition);
		std::pair<int, int> newTilePosition = this->whichTile(newPixelPosition);
		if (this->getCurrentTile() != newTilePosition) {
			if (this->validTilePosition(newTilePosition)) {
				this->setLastTile(this->getCurrentTile());
				this->setCurrentTile(newTilePosition);
			} else {
				this->setCouldContinue(false);
			}
		}
	}
}

bool Movable::validTilePosition(std::pair<int, int> tilePosition) {
	return this->isInsideWorld(tilePosition);
}

void Movable::calculateWayForward() {
	this->setDirection(this->getInitialTile(), this->getTargetTile());
}

void Movable::verify() {
	if (!this->canCross(this->getCurrentTile())) {
		this->setCouldContinue(false);
	}
	if (this->getCurrentTile() == this->getTargetTile())
		this->setTargetReached(true);
}

bool Movable::isAlive() {
	return (!this->isTargetReached() && this->couldContinue());
}

void Movable::initialize() {
	this->setCurrentTile(this->getInitialTile());
	this->setLastTile(this->getInitialTile());
	int x, y;
	x = static_cast<int>(this->getTileWidth())*(this->getInitialTile().first - this->getInitialTile().second)/2 - this->getSprite()->relatx();
	y = static_cast<int>(this->getTileHeight())*(1 + this->getInitialTile().first + this->getInitialTile().second)/2 - this->getSprite()->relaty();
	this->setPosition(std::make_pair(x, y));
	this->setRectangle(this->getInitialTile(),this->getSprite());
}

std::pair<int, int> Movable::whichTile(std::pair<int, int> pix) {
	return this->pixelToTileCoordinates(std::make_pair(pix.first + this->getSprite()->relatx(), pix.second + this->getSprite()->relaty()));
}

bool Movable::goingDiagonal() {
	return ((this->getPixelDirection().first != 0) && (this->getPixelDirection().second != 0));
}