#include "Surface.h"
#include <SDL_image.h>


const Uint32 view::Surface::HEXA_WHITE_COLOR = 0xFFFFFF;
const Uint32 view::Surface::HEXA_BLUE_COLOR = 0x0000FF;
const Uint32 view::Surface::HEXA_LIGHT_BLUE_COLOR = 0x00DCFF;
const Uint32 view::Surface::HEXA_BLACK_COLOR = 0x000000;
const Uint32 view::Surface::HEXA_RED_COLOR = 0xFF0000;
const Uint32 view::Surface::HEXA_GREEN_COLOR = 0x22B14C;

view::Surface::Surface() {
	this->surface = NULL;
	this->shadows.clear();
}

SDL_Surface* view::Surface::getSurface() {
	return this->surface;
}

SDL_Surface* view::Surface::getBlackShadow() {
	return this->shadows[0];
}

SDL_Surface* view::Surface::getWhiteShadow() {
	return this->shadows[1];
}

SDL_Surface* view::Surface::getSurfaceToShow(bool transparent) {
	if (transparent) {
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

void view::Surface::addShadowSurface(SDL_Surface* surface) {
	SDL_Surface* aux = SDL_DisplayFormat(surface);
	//this->shadow = SDL_DisplayFormat(surface);
	SDL_SetColorKey(aux, SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB(aux->format, 255, 0, 255));
	this->shadows.push_back(aux);
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
	for (unsigned i = 0; i < this->shadows.size(); i++) {
		if (this->shadows[i]) {
			SDL_FreeSurface(this->shadows[i]);
			this->shadows[i] = NULL;
		}
	}
	this->shadows.clear();
}

view::Surface::~Surface() {
}

void view::Surface::createShadow(Uint32 color) {
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
	//la pinto del color dado
	SDL_FillRect(shadowSurface, NULL, color);

	for (int i = 0; i < this->surface->w; i++) {
		for (int j = 0; j < this->surface->h; j++) {
			sourceSinglePixel = sourcePixels + j*this->surface->pitch/4 + i; 
			SDL_GetRGBA(*sourceSinglePixel, this->surface->format, &r, &g, &b, &a);

			//donde la imagen de origen era transparente pongo transparente la sombra
			if ((r == 255) && (g == 0) && (b == 255)){
				shadowSinglePixel = shadowPixels + j*shadowSurface->pitch/4 + i;
				*shadowSinglePixel = SDL_MapRGB(shadowSurface->format, r, g, b);
			} else {

				if (color != HEXA_BLACK_COLOR) {
					if ((r <= 12) && (g <= 9) && (b <= 5)){
						shadowSinglePixel = shadowPixels + j*shadowSurface->pitch/4 + i;
						*shadowSinglePixel = SDL_MapRGB(shadowSurface->format, r, g, b);
					}
				}
			}
		}
	}

	if (mustBeLocked)
		SDL_UnlockSurface(this->surface);
	this->addShadowSurface(shadowSurface);
	SDL_FreeSurface(shadowSurface);
}

void view::Surface::createShadows() {
	this->createShadow(HEXA_BLACK_COLOR);
	this->createShadow(HEXA_LIGHT_BLUE_COLOR);
	this->createShadow(HEXA_BLUE_COLOR);
}