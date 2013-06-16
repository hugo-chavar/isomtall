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
	//TODO: al metodo isAlive() llamar fuera de la clase y no entrar ac�
	if (!this->isAlive())
		return;
	Entity::update();
	this->move();
	this->verify();
}

void Movable::render(Camera& camera) {
	//TODO: al metodo isAlive() llamar fuera de la clase y no entrar ac�
	if (!this->isAlive())
		return;
	//TODO: ver si necesito datos de la camara para calcular la posicion
	this->updateRectanglePosition(this->getPosition().first, this->getPosition().second);
	camera.render(this->spriteRect,this->sprite->getSurfaceAt(this->getOrientation())->getSurfaceToShow(false));
}

void Movable::move() {
	std::pair<float, float> deltaMovement;
	float deltaVelocity = this->getVelocity()*this->getDeltaTime();
	deltaMovement.first = deltaVelocity*this->getPixelDirection().first + this->remaining.first;
	deltaMovement.second = deltaVelocity*this->getPixelDirection().second/2 + this->remaining.second;
	this->remaining.first = deltaMovement.first - std::floor(deltaMovement.first);
	this->remaining.second = deltaMovement.second - std::floor(deltaMovement.second);
	std::pair<int, int> newPixelPosition;
	newPixelPosition.first = this->getPosition().first + static_cast<int>(std::floor(deltaMovement.first));
	newPixelPosition.second = this->getPosition().second + static_cast<int>(std::floor(deltaMovement.second));
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

bool Movable::validTilePosition(std::pair<int, int> tilePosition) {
	return this->isInsideWorld(tilePosition);
}

void Movable::calculateWayForward() {
	this->setDirection(this->getInitialTile(), this->getTargetTile());
}

void Movable::verify() {
	if (this->getCurrentTile() == this->getTargetTile())
		this->setTargetReached(true);
	if (!this->canCross(this->getCurrentTile()))
		this->setCouldContinue(false);
}

bool Movable::isAlive() {
	return (!this->isTargetReached() && this->couldContinue());
}

void Movable::initialize() {
	this->setSprite(this->getSpriteWithName(this->getName()));
	this->setCurrentTile(this->getInitialTile());
	this->setLastTile(this->getInitialTile());
	int x, y, aux1, aux2;
	aux1 = (this->getInitialTile().first - this->getInitialTile().second)/2;
	aux2 = (this->getInitialTile().first + this->getInitialTile().second)/2;
	x = this->getTileWidth()*aux1 - this->getSprite()->relatx();
	y = this->getTileHeight()*aux2 - this->getSprite()->relaty();
	this->setPosition(std::make_pair(x, y));
	this->setRectangle(this->getInitialTile(),this->getSprite());
}

std::pair<int, int> Movable::whichTile(std::pair<int, int> pix) {
	return this->pixelToTileCoordinates(std::make_pair(pix.first + this->getSprite()->relatx(), pix.second + this->getSprite()->relaty()));
}