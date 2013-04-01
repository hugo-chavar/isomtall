#include "Camera.h"

#include "World.h"
#include <cmath>
#include "TimeManager.h"

model::Camera::Camera() {
	this->offsetX = 0;
	this->offsetY = 0;
	this->scrollSpeed = 0;
	this->scrollBoxSize = 0;
	this->cameraSurface = NULL;
}

int model::Camera::getOffsetX() {
	return this->offsetX;
}

void model::Camera::setOffsetX(int offsetX) {
	this->offsetX = offsetX;
}

int model::Camera::getOffsetY() {
	return this->offsetY;
}

void model::Camera::setOffsetY(int offsetY) {
	this->offsetY = offsetY;
}

unsigned int model::Camera::getScrollSpeed() {
	return this->scrollSpeed;
}

void model::Camera::setScrollSpeed(unsigned int scrollSpeed) {
	this->scrollSpeed = scrollSpeed;
}


unsigned int model::Camera::getScrollBoxSize() {
	return this->scrollBoxSize;
}

void model::Camera::setScrollBoxSize(unsigned int scrollBoxSize) {
	this->scrollBoxSize = scrollBoxSize;
}

unsigned int model::Camera::getWidth() {
	return this->cameraSurface->w;
}

unsigned int model::Camera::getHeight() {
	return this->cameraSurface->h;
}

void model::Camera::initialize(unsigned int width, unsigned int height, unsigned int bpp, unsigned int scrollSpeed, unsigned int scrollBoxSize, int offsetX, int offsetY) {
	this->setScrollSpeed(scrollSpeed);
	this->setScrollBoxSize(scrollBoxSize);
	this->setOffsetX(offsetX); 
	this->setOffsetY(offsetY);
	this->cameraSurface = SDL_SetVideoMode(width,height,bpp,SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WarpMouse(width/2,height/2);
}

void model::Camera::update() {
	int x;
	int y;
	int newOffset = 0;
	std::pair<int,int> cameraCenterInTiles;

	SDL_GetMouseState(&x,&y);

	if (x > (this->getWidth() - this->getScrollBoxSize())) {
		newOffset = ceil(this->getOffsetX() + this->getScrollSpeed() * model::TimeManager::getDeltaTime());
		cameraCenterInTiles = this->pixelToTileCoordinates(std::make_pair<int,int>(newOffset + (this->getWidth() / 2),this->getOffsetY() + (this->getHeight() / 2)));
		//TODO: harcoded value. Mus be obtained from the model.
		if ( (cameraCenterInTiles.first < 0) || (cameraCenterInTiles.first > 30) || (cameraCenterInTiles.second < 0) || (cameraCenterInTiles.second > 30) ) {
			newOffset = this->getOffsetX();
		}
		this->setOffsetX(newOffset);
	}

	if (x < this->getScrollBoxSize()) {
		newOffset = ceil(this->getOffsetX() - this->getScrollSpeed() * model::TimeManager::getDeltaTime());
		cameraCenterInTiles = this->pixelToTileCoordinates(std::make_pair<int,int>(newOffset + (this->getWidth() / 2),this->getOffsetY() + (this->getHeight() / 2)));
		//TODO: harcoded value. Mus be obtained from the model.
		if ( (cameraCenterInTiles.first < 0) || (cameraCenterInTiles.first > 30) || (cameraCenterInTiles.second < 0) || (cameraCenterInTiles.second > 30) ) {
			newOffset = this->getOffsetX();
		}
		this->setOffsetX(newOffset);
	}

	if (y > (this->getHeight() - this->getScrollBoxSize())) {
		newOffset = ceil(this->getOffsetY() + this->getScrollSpeed() * model::TimeManager::getDeltaTime());
		cameraCenterInTiles = this->pixelToTileCoordinates(std::make_pair<int,int>(this->getOffsetX() + (this->getWidth() / 2),newOffset + (this->getHeight() / 2)));
		if ( (cameraCenterInTiles.first < 0) || (cameraCenterInTiles.first > 30) || (cameraCenterInTiles.second < 0) || (cameraCenterInTiles.second > 30) ) {
			newOffset = this->getOffsetY();
		}
		this->setOffsetY(newOffset);
	}

	if (y < this->getScrollBoxSize()) {
		newOffset = ceil(this->getOffsetY() - this->getScrollSpeed() * model::TimeManager::getDeltaTime());
		cameraCenterInTiles = this->pixelToTileCoordinates(std::make_pair<int,int>(this->getOffsetX() + (this->getWidth() / 2),newOffset + (this->getHeight() / 2)));
		if ( (cameraCenterInTiles.first < 0) || (cameraCenterInTiles.first > 30) || (cameraCenterInTiles.second < 0) || (cameraCenterInTiles.second > 30) ) {
			newOffset = this->getOffsetY();
		}
		this->setOffsetY(newOffset);
	}
}

void model::Camera::cleanUp() {
	SDL_FreeSurface(this->cameraSurface);
}

model::Camera::~Camera() {
}

//TODO: Method copied from model::world and harcoded. Move to proper location.
std::pair<int,int> model::Camera::pixelToTileCoordinates(std::pair<int,int> pixelCoordinates) {
	float a = 0;
	float b = 0;
	int c = 0;

	c = pixelCoordinates.first - ((30 * 62) / 2);
	a = (static_cast<float>(pixelCoordinates.second) / 31);
	b = (static_cast<float>(c) / 62);

	return std::make_pair<int,int>(a + b,a - b);
}