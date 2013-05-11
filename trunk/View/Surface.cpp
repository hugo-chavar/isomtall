#include "Surface.h"
#include <SDL_image.h>

view::Surface::Surface() {
	this->sdlSurface = NULL;
}

SDL_Surface* view::Surface::getSdlSurface() {
	return this->sdlSurface;
}

void view::Surface::setSdlSurface(SDL_Surface* sdlSurface) {
	this->sdlSurface = sdlSurface;
}

int view::Surface::getWidth() {
	return this->getSdlSurface()->w;
}

int view::Surface::getHeight() {
	return this->getSdlSurface()->h;
}

void view::Surface::createTransparent() {
	SDL_Surface* tempSurface = NULL;

	tempSurface = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCALPHA,800,600,32,0,0,0,0);

	this->setSdlSurface(SDL_DisplayFormatAlpha(tempSurface));

	SDL_FillRect(this->getSdlSurface(),NULL,SDL_MapRGBA(this->getSdlSurface()->format,0,0,0,0));

	SDL_FreeSurface(tempSurface);
}

void view::Surface::load(std::string fileName) {
	SDL_Surface* tempSurface = NULL;

	tempSurface = IMG_Load(fileName.c_str());

	this->setSdlSurface(SDL_DisplayFormatAlpha(tempSurface));

	SDL_FreeSurface(tempSurface);
}

void view::Surface::free() {
	SDL_FreeSurface(this->getSdlSurface());
}

view::Surface::~Surface() {
}