#include "Camera.h"

#include "World.h"
#include <cmath>
#include "TimeManager.h"

using namespace view;

Camera::Camera() {
	this->offsetX = 0;
	this->offsetY = 0;
	this->scrollSpeed = 0;
	this->scrollBoxSize = 0;
	this->cameraSurface = NULL;
}

int Camera::getOffsetX() {
	return this->offsetX;
}

void Camera::setOffsetX(int offsetX) {
	this->offsetX = offsetX;
}

int Camera::getOffsetY() {
	return this->offsetY;
}

void Camera::setOffsetY(int offsetY) {
	this->offsetY = offsetY;
}

unsigned int Camera::getScrollSpeed() {
	return this->scrollSpeed;
}

void Camera::setScrollSpeed(unsigned int scrollSpeed) {
	this->scrollSpeed = scrollSpeed;
}


unsigned int Camera::getScrollBoxSize() {
	return this->scrollBoxSize;
}

void Camera::setScrollBoxSize(unsigned int scrollBoxSize) {
	this->scrollBoxSize = scrollBoxSize;
}

 int Camera::getWidth() {
	return this->cameraSurface->w;
}

 int Camera::getHeight() {
	return this->cameraSurface->h;
}

void Camera::initialize(unsigned int width, unsigned int height, unsigned int bpp, unsigned int scrollSpeed, unsigned int scrollBoxSize, int offsetX, int offsetY) {
	this->setScrollSpeed(scrollSpeed);
	this->setScrollBoxSize(scrollBoxSize);
	this->setOffsetX(offsetX); 
	this->setOffsetY(offsetY);
	this->cameraSurface = SDL_SetVideoMode(width,height,bpp,SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WarpMouse(width/2,height/2);
}

void Camera::update() {
	int x;
	int y;
	int newOffset = 0;
	std::pair<int,int> cameraCenterInTiles;

	SDL_GetMouseState(&x,&y);

	if (x > int(this->getWidth() - this->getScrollBoxSize())) {
		newOffset = int(ceil(this->getOffsetX() + this->getScrollSpeed() * model::TimeManager::getDeltaTime()));
		cameraCenterInTiles = this->pixelToTileCoordinates(std::make_pair<int,int>(newOffset + (this->getWidth() / 2),this->getOffsetY() + (this->getHeight() / 2)));
		//TODO: harcoded value. Mus be obtained from the model.
		if ( (cameraCenterInTiles.first < -30) || (cameraCenterInTiles.first > 30) || (cameraCenterInTiles.second < -30) || (cameraCenterInTiles.second > 30) ) {
			newOffset = this->getOffsetX();
		}
		this->setOffsetX(newOffset);
	}

	if (x < int(this->getScrollBoxSize())) {
		newOffset = int(ceil(this->getOffsetX() - this->getScrollSpeed() * model::TimeManager::getDeltaTime()));
		cameraCenterInTiles = this->pixelToTileCoordinates(std::make_pair<int,int>(newOffset + (this->getWidth() / 2),this->getOffsetY() + (this->getHeight() / 2)));
		//TODO: harcoded value. Mus be obtained from the model.
		if ( (cameraCenterInTiles.first < -30) || (cameraCenterInTiles.first > 30) || (cameraCenterInTiles.second < -30) || (cameraCenterInTiles.second > 30) ) {
			newOffset = this->getOffsetX();
		}
		this->setOffsetX(newOffset);
	}

	if (y > int(this->getHeight() - this->getScrollBoxSize())) {
		newOffset = int(ceil(this->getOffsetY() + this->getScrollSpeed() * model::TimeManager::getDeltaTime()));
		cameraCenterInTiles = this->pixelToTileCoordinates(std::make_pair<int,int>(this->getOffsetX() + (this->getWidth() / 2),newOffset + (this->getHeight() / 2)));
		if ( (cameraCenterInTiles.first < -30) || (cameraCenterInTiles.first > 30) || (cameraCenterInTiles.second < -30) || (cameraCenterInTiles.second > 30) ) {
			newOffset = this->getOffsetY();
		}
		this->setOffsetY(newOffset);
	}

	if (y < int(this->getScrollBoxSize())) {
		newOffset = int(ceil(this->getOffsetY() - this->getScrollSpeed() * model::TimeManager::getDeltaTime()));
		cameraCenterInTiles = this->pixelToTileCoordinates(std::make_pair<int,int>(this->getOffsetX() + (this->getWidth() / 2),newOffset + (this->getHeight() / 2)));
		if ( (cameraCenterInTiles.first < -30) || (cameraCenterInTiles.first > 30) || (cameraCenterInTiles.second < -30) || (cameraCenterInTiles.second > 30) ) {
			newOffset = this->getOffsetY();
		}
		this->setOffsetY(newOffset);
	}
}

void Camera::cleanUp() {
	SDL_FreeSurface(this->cameraSurface);
}

void Camera::render(SDL_Rect spriteRec,SDL_Surface* surface)
{

if((spriteRec.x>offsetX-spriteRec.w)&&(spriteRec.y>offsetY-spriteRec.h)&&(spriteRec.x<offsetX+getWidth())&&(spriteRec.y<offsetY+getHeight()))
	
	{
	SDL_Rect rectangulo;
	rectangulo.x=spriteRec.x-offsetX;
	rectangulo.y=spriteRec.y-offsetY;
	SDL_BlitSurface(surface, NULL,cameraSurface,&rectangulo);
	}
}


Camera::~Camera() {
}

//TODO: Method copied from model::world and harcoded. Move to proper location.
std::pair<int,int> Camera::pixelToTileCoordinates(std::pair<int,int> pixelCoordinates) {
	float a = 0;
	float b = 0;
	int c = 0;

	c = pixelCoordinates.first - ((30 * 62) / 2);
	a = (static_cast<float>(pixelCoordinates.second) / 31);
	b = (static_cast<float>(c) / 62);

	return std::make_pair<int,int>(int(a + b),int(a - b));
}