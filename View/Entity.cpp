#include "Entity.h"
#include "Game.h"
#include "StringUtilities.h"

Entity::Entity() {
}

Entity::Entity(int tileX,int tileY,Sprite* spriteCargado) {
	this->setFogged(true);
	this->setStatus(ENTITY_NORMAL);
	this->resetSpriteState();
	sprite = spriteCargado;
	this->setRectangle(std::make_pair(tileX, tileY), spriteCargado);
}

Entity::~Entity() {
}

void Entity::setRectangle(std::pair<int, int> pos, Sprite* sprite ) {
	this->spriteRect = posicionIsometricaPorTiles(pos.first, pos.second, sprite);
	this->spriteRect.w = (Uint16)(sprite->getCurrentSurface()->getSurface()->w);
	this->spriteRect.h = (Uint16)(sprite->getCurrentSurface()->getSurface()->h);
}

SDL_Rect Entity::posicionIsometricaPorTiles(int tileX,int tileY,Sprite* sprite) {
	SDL_Rect rectangulo;
	//unsigned pptx = Game::instance().world()->tileWidth();
	//unsigned ppty = Game::instance().world()->tileHeight();
	rectangulo.x = (Sint16)(this->getTileWidth()*tileX/2-this->getTileWidth()*tileY/2-sprite->relatx());
	rectangulo.y = (Sint16)(this->getTileHeight()*tileX/2+this->getTileHeight()*tileY/2-sprite->relaty());
	return rectangulo;
}

void Entity::update() {
	if (this->isImmobilized() && (this->freezedSpriteState < 0)) {
		freezedSpriteState = sprite->getCurrentSurfaceNumber();
		return;
	}
	if (!this->isImmobilized()) {
		this->resetSpriteState();
		return;
	}
	if (this->needsCountDown()) {
		this->decreaseEndStatusTime();
		if (this->endStatusTime == 0)
			this->setStatus(ENTITY_NORMAL);
	}
}

void Entity::setFogged(bool value) {
	this->fogged = value;
}

void Entity::resetSpriteState() {
	this->freezedSpriteState = -1;
}

bool Entity::isFogged() {
	return this->fogged;
}

void Entity::setStatus(unsigned status) {
	this->status = status;
}

unsigned Entity::getStatus() {
	return this->status;
}

bool Entity::isImmobilized() {
	return ((this->isFogged() )||(this->getStatus() == ENTITY_FROZEN));
}

void Entity::iceUp(float seconds) {
	this->setStatus(ENTITY_FROZEN);
	this->setEndStatusTime(seconds);
}

void Entity::decreaseEndStatusTime() {
	if ( this->getDeltaTime() < this->endStatusTime)
		this->endStatusTime -= this->getDeltaTime();
	else
		this->setEndStatusTime(0);
}

void Entity::setEndStatusTime(float endTime) {
	this->endStatusTime = endTime;
}

bool Entity::isItem() {
	return false;
}

bool Entity::needsCountDown() {
	switch (this->getStatus()) {
		case ITEM_WAITING_REGENERATION:
		case EXPLOSIVE_EXPLOSION_COUNTDOWN:
		case ENTITY_FROZEN:
			return true;
		break;
	}
	return false;
}

//devuelve verdadero para las entidades q deben ser borradas..
//o sea, el estado es "pendiente de borrado" .. el stage se va a encargar de borrarlas ("recoger la basura")
bool Entity::needsToBeCleaned() {
	switch (this->getStatus()) {
		case EXPLOSIVE_DUST_IN_THE_WIND:
			return true;
		break;
	}
	return false;
}

std::string Entity::statusToString() {
	return stringUtilities::unsignedToString(this->getStatus());
}

void Entity::setSprite(Sprite* sprite) {
	this->sprite = sprite;
}

Sprite* Entity::getSprite() {
	return this->sprite;
}

unsigned Entity::getTileWidth() {
	return Game::instance().world()->tileWidth();
}

unsigned Entity::getTileHeight() {
	return Game::instance().world()->tileHeight();
}

void Entity::updateRectanglePosition(int x, int y) {
	this->spriteRect.x = static_cast<Uint16>(x);
	this->spriteRect.y = static_cast<Uint16>(y);
}

bool Entity::isAlive() {
	return true;
}

std::string Entity::getName() {
	return this->name;
}

void Entity::setName(std::string value) {
	this->name = value;
}

void Entity::render(Camera& camera) {
	
	this->renderEntitySprite(this->spriteRect,this->sprite,camera);
}

void Entity::renderEntitySprite(SDL_Rect rect,Sprite * _sprite,Camera& camera)
{
	if (this->isImmobilized()) {
		if (this->isFogged())
			camera.render(rect,_sprite->getSurfaceAt(freezedSpriteState)->getBlackShadow());
		else
			camera.render(rect,_sprite->getSurfaceAt(freezedSpriteState)->getWhiteShadow());
	}
	camera.render(rect,_sprite->getSurfaceAt(freezedSpriteState)->getSurfaceToShow(this->isImmobilized()));
}