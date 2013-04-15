#include "Camera.h"

#include <cmath>

#include "World.h"
#include "TimeManager.h"
#include "Game.h"

using namespace view;

Camera::Camera() {
	this->offsetX = 0;
	this->offsetY = 0;
	this->scrollSpeed = 0;
	this->scrollBoxSize = 0;
	this->cameraSurface = NULL;
}

float Camera::getOffsetX() {
	return this->offsetX;
}

void Camera::setOffsetX(float offsetX) {
	this->offsetX = offsetX;
}

float Camera::getOffsetY() {
	return this->offsetY;
}

void Camera::setOffsetY(float offsetY) {
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


bool Camera::initialize() {  
	unsigned speed,scrollm,width,height;
	if (!Game::instance().cameraModel()){
		return false;
	}
	scrollm = Game::instance().cameraModel()->scroll();
	speed = Game::instance().cameraModel()->speed();
	width = Game::instance().cameraModel()->width();
	height = Game::instance().cameraModel()->height();
	this->setScrollSpeed(150);
	this->setScrollBoxSize(scrollm);
	//traer la posicion relativa del personaje
	//asi se centra la camara al principio
	this->setOffsetX(0);
	this->setOffsetY(0);
	this->cameraSurface = SDL_SetVideoMode(width,height,DEFAULT_VIDEO_BPP,SDL_HWSURFACE | SDL_DOUBLEBUF);
	if(this->cameraSurface==NULL)
		{
			width=DEFAULT_SCREEN_WIDTH;
			height=DEFAULT_SCREEN_HEIGHT;
			this->cameraSurface = SDL_SetVideoMode(width,height,DEFAULT_VIDEO_BPP,SDL_HWSURFACE | SDL_DOUBLEBUF);
		}
	SDL_WarpMouse(static_cast<Uint16>(width/2),static_cast<Uint16>(height/2));
	return true;
}

void Camera::update() {
	int x;
	int y;
	float newOffset = 0;
	float scrollFactor = 0;
	std::pair<int,int> cameraCenterInTiles;
	//std::pair<int,int> cameraCenterInTiles = std::make_pair<int,int>(0,0);

	SDL_GetMouseState(&x,&y);

	if (x > static_cast<int>(this->getWidth() - this->getScrollBoxSize())) {
		scrollFactor = static_cast<float>(this->getScrollBoxSize() - (this->getWidth() - x)) / this->getScrollBoxSize();
		newOffset = this->getOffsetX() + this->getScrollSpeed() * Game::instance().time().getDeltaTime() * scrollFactor;
		cameraCenterInTiles = Game::instance().world().pixelToTileCoordinates(std::make_pair<int,int>(static_cast<int>(newOffset + (this->getWidth() / 2)),static_cast<int>(this->getOffsetY() + (this->getHeight() / 2))));
		if (!Game::instance().world().isInsideWorld(cameraCenterInTiles)) {
			newOffset = this->getOffsetX();
		}
		this->setOffsetX(newOffset);
	}

	if (x < static_cast<int>(this->getScrollBoxSize())) {
		scrollFactor = static_cast<float>(this->getScrollBoxSize() - x) / this->getScrollBoxSize();
		newOffset = this->getOffsetX() - this->getScrollSpeed() * Game::instance().time().getDeltaTime() * scrollFactor;
		cameraCenterInTiles = Game::instance().world().pixelToTileCoordinates(std::make_pair<int,int>(static_cast<int>(newOffset + (this->getWidth() / 2)),static_cast<int>(this->getOffsetY() + (this->getHeight() / 2))));
				if (!Game::instance().world().isInsideWorld(cameraCenterInTiles)) {
			newOffset = this->getOffsetX();
		}
		this->setOffsetX(newOffset);
	}

	if (y > static_cast<int>(this->getHeight() - this->getScrollBoxSize())) {
		scrollFactor = static_cast<float>(this->getScrollBoxSize() - (this->getHeight() - y)) / this->getScrollBoxSize();
		newOffset = this->getOffsetY() + this->getScrollSpeed() * Game::instance().time().getDeltaTime() * scrollFactor;
		cameraCenterInTiles = Game::instance().world().pixelToTileCoordinates(std::make_pair<int,int>(static_cast<int>(this->getOffsetX() + (this->getWidth() / 2)),static_cast<int>(newOffset + (this->getHeight() / 2))));
		if (!Game::instance().world().isInsideWorld(cameraCenterInTiles)) {
			newOffset = this->getOffsetY();
		}
		this->setOffsetY(newOffset);
	}

	if (y < static_cast<int>(this->getScrollBoxSize())) {
		scrollFactor = static_cast<float>(this->getScrollBoxSize() - y) / this->getScrollBoxSize();
		newOffset = this->getOffsetY() - this->getScrollSpeed() * Game::instance().time().getDeltaTime() * scrollFactor;
		cameraCenterInTiles = Game::instance().world().pixelToTileCoordinates(std::make_pair<int,int>(static_cast<int>(this->getOffsetX() + (this->getWidth() / 2)),static_cast<int>(newOffset + (this->getHeight() / 2))));
		if (!Game::instance().world().isInsideWorld(cameraCenterInTiles)) {
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
	rectangulo.x = spriteRec.x - static_cast<Sint16>(offsetX);
	rectangulo.y = spriteRec.y - static_cast<Sint16>(offsetY);
	SDL_BlitSurface(surface, NULL,cameraSurface,&rectangulo);
	}
}


Camera::~Camera() {
}
