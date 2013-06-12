#include <cmath>
#include "Game.h"
#include "Camera.h"
#include "Stage.h"
#include "TimeManager.h"

using namespace view;

const SDL_Color Camera::WHITE_COLOR = {255, 255, 255};
const SDL_Color Camera::BLUE_COLOR = {0, 0, 255};
const SDL_Color Camera::BLACK_COLOR = {0, 0, 0};
const SDL_Color Camera::RED_COLOR = {255, 0, 0};
const SDL_Color Camera::GREEN_COLOR = {34, 177, 76};

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


 void Camera::initialize() {  
	 unsigned width,height;
	 width = Game::instance().configuration()->cameraWidth();
	 height = Game::instance().configuration()->cameraHeight();

	 this->startScreen(width,height);

	 SDL_WarpMouse(static_cast<Uint16>(width/2),static_cast<Uint16>(height/2));
 }

 void Camera::configure() {
	 unsigned speed,scrollm;
	 scrollm = Game::instance().configuration()->cameraMarginScroll();
	 speed = Game::instance().configuration()->cameraSpeed();
	 this->setScrollSpeed(speed);
	 this->setScrollBoxSize(scrollm);
	 this->setOffsetX(0);
	 this->setOffsetY(0);
 }
 
 void Camera::unconfigure() {
	 this->setScrollSpeed(0);
	 this->setScrollBoxSize(0);
	 this->setOffsetX(0);
	 this->setOffsetY(0);
 }

void Camera::update() {
	int x;
	int y;
	float newOffset = 0;
	float scrollFactor = 0;
	std::pair<int,int> cameraCenterInTiles;
	//std::pair<int,int> cameraCenterInTiles = std::make_pair<int,int>(0,0);

	SDL_GetMouseState(&x,&y);

	if ((x > static_cast<int>(this->getWidth() - this->getScrollBoxSize()))&&(x < static_cast<int>(this->getWidth()) - 5)) {
		scrollFactor = static_cast<float>(this->getScrollBoxSize() - (this->getWidth() - x)) / this->getScrollBoxSize();
		newOffset = this->getOffsetX() + this->getScrollSpeed() * (Game::instance().getTimer())->getDeltaTime() * scrollFactor;
		cameraCenterInTiles = (Game::instance().world())->pixelToTileCoordinates(std::make_pair<int,int>(static_cast<int>(newOffset + (this->getWidth() / 2)),static_cast<int>(this->getOffsetY() + (this->getHeight() / 2))));
		if (!(Game::instance().world())->isInsideWorld(cameraCenterInTiles)) {
			newOffset = this->getOffsetX();
		}
		this->setOffsetX(newOffset);
	}

	if ((x < static_cast<int>(this->getScrollBoxSize()))&&(x > 5)) {
		scrollFactor = static_cast<float>(this->getScrollBoxSize() - x) / this->getScrollBoxSize();
		newOffset = this->getOffsetX() - this->getScrollSpeed() * (Game::instance().getTimer())->getDeltaTime() * scrollFactor;
		cameraCenterInTiles = (Game::instance().world())->pixelToTileCoordinates(std::make_pair<int,int>(static_cast<int>(newOffset + (this->getWidth() / 2)),static_cast<int>(this->getOffsetY() + (this->getHeight() / 2))));
		if (!(Game::instance().world())->isInsideWorld(cameraCenterInTiles)) {
			newOffset = this->getOffsetX();
		}
		this->setOffsetX(newOffset);
	}

	if ((y > static_cast<int>(this->getHeight() - this->getScrollBoxSize()))&&(y < static_cast<int>(this->getHeight()) - 5)) {
		scrollFactor = static_cast<float>(this->getScrollBoxSize() - (this->getHeight() - y)) / this->getScrollBoxSize();
		newOffset = this->getOffsetY() + this->getScrollSpeed() * (Game::instance().getTimer())->getDeltaTime() * scrollFactor;
		cameraCenterInTiles = (Game::instance().world())->pixelToTileCoordinates(std::make_pair<int,int>(static_cast<int>(this->getOffsetX() + (this->getWidth() / 2)),static_cast<int>(newOffset + (this->getHeight() / 2))));
		if (!(Game::instance().world())->isInsideWorld(cameraCenterInTiles)) {
			newOffset = this->getOffsetY();
		}
		this->setOffsetY(newOffset);
	}

	if ((y < static_cast<int>(this->getScrollBoxSize())) && (y > 5)) {
		scrollFactor = static_cast<float>(this->getScrollBoxSize() - y) / this->getScrollBoxSize();
		newOffset = this->getOffsetY() - this->getScrollSpeed() * (Game::instance().getTimer())->getDeltaTime() * scrollFactor;
		cameraCenterInTiles = (Game::instance().world())->pixelToTileCoordinates(std::make_pair<int,int>(static_cast<int>(this->getOffsetX() + (this->getWidth() / 2)),static_cast<int>(newOffset + (this->getHeight() / 2))));
		if (!(Game::instance().world())->isInsideWorld(cameraCenterInTiles)) {
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

void Camera::startScreen(unsigned width, unsigned height) {
	this->cameraSurface = SDL_SetVideoMode(width,height,DEFAULT_VIDEO_BPP,SDL_HWSURFACE | SDL_DOUBLEBUF);
	if(this->cameraSurface == NULL)	{
		this->cameraSurface = SDL_SetVideoMode(DEFAULT_SCREEN_WIDTH,DEFAULT_SCREEN_HEIGHT,DEFAULT_VIDEO_BPP,SDL_HWSURFACE | SDL_DOUBLEBUF);
	}
}

Camera::~Camera() {
}

void Camera::setCenterPixel(std::pair<int,int> center) {
	this->setOffsetX(static_cast<float>(2*center.first-this->getWidth())/2);
	this->setOffsetY(static_cast<float>(2*center.second-this->getHeight())/2);
}
