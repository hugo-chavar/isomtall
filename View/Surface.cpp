#include "Surface.h"
#include <SDL_image.h>

view::Surface::Surface() {
	this->sdlSurface = NULL;
}

SDL_Surface* view::Surface::getSdlSurface() {
	return this->sdlSurface;
}

void view::Surface::setSdlSurface(SDL_Surface* surface) {
	this->sdlSurface = SDL_DisplayFormat(surface);
	SDL_SetColorKey(this->sdlSurface,SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB(this->sdlSurface->format,255,0,255));
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

void view::Surface::setTransparent() {
	SDL_SetAlpha( this->sdlSurface, SDL_SRCALPHA, (SDL_ALPHA_TRANSPARENT + SDL_ALPHA_OPAQUE)/2 );
}

void view::Surface::load(std::string fileName) {
	SDL_Surface* tempSurface = NULL;

	tempSurface = IMG_Load(fileName.c_str());

	this->setSdlSurface(tempSurface); //SDL_DisplayFormatAlpha(

	SDL_FreeSurface(tempSurface);
}

void view::Surface::free() {
	SDL_FreeSurface(this->sdlSurface);
}

view::Surface::~Surface() {
}

//void view::Surface::setShadow(SDL_Surface* source){
//	//this->sdlSurface = this->createShadow(source);
//
//	this->setSdlSurface(this->createShadow(source));
//}

void view::Surface::createShadow(SDL_Surface* source) {
	bool mustBeLocked = SDL_MUSTLOCK(source);
	if (mustBeLocked)
		SDL_LockSurface(source);
	//Uint32 rmask, gmask, bmask, amask;
	Uint32* shadowPixels;
	Uint32* sourceSinglePixel;
	Uint32* shadowSinglePixel;
	Uint32* sourcePixels = (Uint32 *) source->pixels;
	Uint8 r, g, b, a; // nuestro transparente es r=255, g=0 y b=255-> 
	
//#if SDL_BYTEORDER == SDL_BIG_ENDIAN
//	rmask = 0xff000000;
//	gmask = 0x00ff0000;
//	bmask = 0x0000ff00;
//	amask = 0x000000ff;
//#else
//	rmask = 0x000000ff;
//	gmask = 0x0000ff00;
//	bmask = 0x00ff0000;
//	amask = 0xff000000;
//#endif
	//Uint8 ourTransparentMask = rmask | bmask; //un OR a nivel bits

	SDL_Surface* shadowSurface = NULL;
	//creo la sombra FF00FF 
	shadowSurface = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCALPHA,source->w,source->h,32,0,0,0,0);
	shadowPixels = (Uint32*)shadowSurface->pixels;
	//la pinto de negro
	SDL_FillRect(shadowSurface, NULL, 0x00000000);

	for (int i = 0; i < source->w; i++) {
		for (int j = 0; j < source->h; j++) {
			//*sourceSinglePixel = sourcePixels[(j * source->w) + i];
			sourceSinglePixel = sourcePixels + j*source->pitch/4 + i; // Nota que trabajar con pixeles es un viaje de ida
			SDL_GetRGBA(*sourceSinglePixel, source->format, &r, &g, &b, &a);

			//donde la imagen de origen era transparente pongo transparente la sombra
			if ((r==255) && g==0 && (b=255)){
				shadowSinglePixel = shadowPixels + j*shadowSurface->pitch/4 + i;
				*shadowSinglePixel = SDL_MapRGB(shadowSurface->format,255,0,255);
			}
		}
	}

	if (mustBeLocked)
		SDL_UnlockSurface(source);
	//SDL_SetColorKey(shadowSurface,SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB(shadowSurface->format,255,0,255));
	this->setSdlSurface(shadowSurface);
	SDL_FreeSurface(shadowSurface);
}