#include "Surface.h"

using namespace view;

Surface::Surface() {
}
 
SDL_Surface* Surface::loadFromBMP(std::string fileName) {
	SDL_Surface* tempSurface = NULL;
	SDL_Surface* surface = NULL;

	if((tempSurface = SDL_LoadBMP(fileName.c_str())) == NULL) {
		return NULL;
	}

	surface = SDL_DisplayFormat(tempSurface);
	SDL_FreeSurface(tempSurface);

	return surface;
}

bool Surface::draw(SDL_Surface* source, SDL_Surface* destination, unsigned int destinationOffsetX, unsigned int destinationOffsetY) {
	if(source == NULL || destination == NULL) {
		return false;
	}

	SDL_Rect destinationRectangle;
	destinationRectangle.x = (Sint16) destinationOffsetX;
	destinationRectangle.y = (Sint16) destinationOffsetY;

	SDL_BlitSurface(source,NULL,destination,&destinationRectangle);

	return true;
}

bool Surface::draw(SDL_Surface* source, unsigned int sourceOffsetX, unsigned int sourceOffsetY, unsigned int sourceHeight, unsigned int sourceWidth, SDL_Surface* destination, unsigned int destinationOffsetX, unsigned int destinationOffsetY) {
	if(source == NULL || destination == NULL) {
		return false;
	}

	SDL_Rect destinationRectangle;
	destinationRectangle.x = (Sint16) destinationOffsetX;
	destinationRectangle.y = (Sint16) destinationOffsetY;

	SDL_Rect sourceRectangle;
	sourceRectangle.x = (Sint16) sourceOffsetX;
	sourceRectangle.y = (Sint16) sourceOffsetY;
	sourceRectangle.h = (Uint16) sourceHeight;
	sourceRectangle.w = (Uint16) sourceWidth;

	SDL_BlitSurface(source,&sourceRectangle,destination,&destinationRectangle);

    return true;
}

Surface::~Surface() {
}