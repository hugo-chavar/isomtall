#include "Surface.h"
#include <SDL_image.h>

view::Surface::Surface() {
	this->surface = NULL;
	this->shadow = NULL;
}

SDL_Surface* view::Surface::getSurface() {
	return this->surface;
}

SDL_Surface* view::Surface::getShadow() {
	return this->shadow;
}

SDL_Surface* view::Surface::getSurfaceToShow(bool fogged) {
	if (fogged) {
		this->setTransparent();
	} else {
		this->setOpaque();
	}
	return this->getSurface();
}

void view::Surface::setSurface(SDL_Surface* surface) {
	this->surface = SDL_DisplayFormat(surface);
	SDL_SetColorKey(this->surface,SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB(this->surface->format,255,0,255));
}

void view::Surface::setShadowSurface(SDL_Surface* surface) {
	this->shadow = SDL_DisplayFormat(surface);
	SDL_SetColorKey(this->shadow,SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB(this->surface->format,255,0,255));
}

int view::Surface::getWidth() {
	return this->getSurface()->w;
}

int view::Surface::getHeight() {
	return this->getSurface()->h;
}

void view::Surface::setTransparent() {
	SDL_SetAlpha( this->surface, SDL_SRCALPHA, (SDL_ALPHA_TRANSPARENT + SDL_ALPHA_OPAQUE)/2 );
}


void view::Surface::setOpaque() {
	SDL_SetAlpha( this->surface, SDL_SRCALPHA, SDL_ALPHA_OPAQUE );
}

void view::Surface::load(std::string fileName) {
	SDL_Surface* tempSurface = NULL;

	tempSurface = IMG_Load(fileName.c_str());

	this->setSurface(tempSurface);

	SDL_FreeSurface(tempSurface);
}

void view::Surface::free() {
	SDL_FreeSurface(this->surface);
	if (this->shadow)
		SDL_FreeSurface(this->shadow);
}

view::Surface::~Surface() {
}

void view::Surface::createShadow() {
	bool mustBeLocked = SDL_MUSTLOCK(this->surface);
	if (mustBeLocked)
		SDL_LockSurface(this->surface);
	Uint32* shadowPixels;
	Uint32* sourceSinglePixel;
	Uint32* shadowSinglePixel;
	Uint32* sourcePixels = (Uint32 *) this->surface->pixels;
	Uint8 r, g, b, a; // nuestro transparente es r=255, g=0 y b=255

	SDL_Surface* shadowSurface = NULL;
	//creo la sombra
	shadowSurface = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCALPHA, this->surface->w, this->surface->h,32,0,0,0,0);
	shadowPixels = (Uint32*)shadowSurface->pixels;
	//la pinto de negro
	SDL_FillRect(shadowSurface, NULL, 0x00000000);

	for (int i = 0; i < this->surface->w; i++) {
		for (int j = 0; j < this->surface->h; j++) {
			sourceSinglePixel = sourcePixels + j*this->surface->pitch/4 + i; // Nota que trabajar con pixeles es un viaje de ida
			SDL_GetRGBA(*sourceSinglePixel, this->surface->format, &r, &g, &b, &a);

			//donde la imagen de origen era transparente pongo transparente la sombra
			if ((r==255) && (g == 0) && (b==255)){
				shadowSinglePixel = shadowPixels + j*shadowSurface->pitch/4 + i;
				*shadowSinglePixel = SDL_MapRGB(shadowSurface->format,255,0,255);
			}
		}
	}

	if (mustBeLocked)
		SDL_UnlockSurface(this->surface);
	this->setShadowSurface(shadowSurface);
	SDL_FreeSurface(shadowSurface);
}