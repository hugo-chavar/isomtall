#include "TileView.h"

//using namespace model;
using namespace view;


TileView::TileView(std::string filePath, unsigned int offsetX, unsigned int offsetY, unsigned int height, unsigned int width, unsigned int speedPenalty, unsigned int centerX, unsigned int centerY) {
	this->speedPenalty = speedPenalty;
	this->centerX = centerX;
	this->centerY = centerY;

	SDL_Surface* tempSurface = Surface::loadFromBMP(filePath.c_str());

	Surface::draw(tempSurface,offsetX,offsetY,height,width,this->sdlSurface,0,0);

	//TODO ver si se usarán transparencias.
	SDL_SetColorKey(this->sdlSurface,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(this->sdlSurface->format,0,0,0));

	SDL_FreeSurface(tempSurface);
}

TileView::TileView(SDL_Surface* sourceSdlSurface, unsigned int offsetX, unsigned int offsetY, unsigned int height, unsigned int width, unsigned int speedPenalty, unsigned int centerX, unsigned int centerY) {
	this->speedPenalty = speedPenalty;
	this->centerX = centerX;
	this->centerY = centerY;

	this->sdlSurface = SDL_CreateRGBSurface(SDL_SWSURFACE,width,height,32,0,0,0,0);

	Surface::draw(sourceSdlSurface,offsetX,offsetY,height,width,this->sdlSurface,0,0);

	//TODO ver si se usarán transparencias.
	SDL_SetColorKey(this->sdlSurface,SDL_SRCCOLORKEY | SDL_RLEACCEL,SDL_MapRGB(this->sdlSurface->format,0,0,0));
}

unsigned int TileView::getSpeedPenalty() {
	return this->speedPenalty;
}

unsigned int TileView::getCenterX() {
	return this->centerX;
}

unsigned int TileView::getCenterY() {
	return this->centerY;
}

void TileView::cleanUp() {
	SDL_FreeSurface(this->sdlSurface);
}

TileView::~TileView() {
}