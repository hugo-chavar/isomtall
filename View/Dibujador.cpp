#include "Dibujador.h"

#define ppty 32 //pixels por tile en y
#define pptx 64 //pixels por tile en x

Dibujador::Dibujador(int ancho,int alto)
{
	screen = SDL_SetVideoMode(ancho,alto,24,SDL_HWSURFACE|SDL_DOUBLEBUF);
	if(pantallaCreada())
	SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
}


Dibujador::~Dibujador()
{
}

void Dibujador::limpiarPantalla()
{
	SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
}

bool Dibujador::pantallaCreada()
{
	return (screen != NULL);
}

void Dibujador::cargarImagenEnTile(int tilex,int tiley,int centroPantallax,Sprite *sprite)
{
SDL_Rect rectangulo=this->posicionIsometricaPorTiles(tilex,tiley,centroPantallax,sprite);
SDL_BlitSurface(sprite->getFrameActual()->getSuperficie(), NULL, screen, &rectangulo);
}

//Corregir si es necesario
/*
void Dibujador::cargarImagenEnPixel(int pixelx,int pixely,int centroPantallax,Sprite *sprite)
{
SDL_Rect rectangulo=this->posicionIsometricaPorPixel(pixelx,pixely,centroPantallax,sprite);
SDL_BlitSurface(sprite->getFrameActual()->getSuperficie(), NULL, screen, &rectangulo);
}*/

SDL_Rect Dibujador::posicionIsometricaPorTiles(int posx, int posy,int centroPantallax,Sprite* sprite)
{
	SDL_Rect rectangulo;
	rectangulo.x= centroPantallax+pptx*posx/2-pptx*posy/2-sprite->relatx();
	rectangulo.y= ppty*posx/2+ppty*posy/2-sprite->relaty();
	return rectangulo;
}

//Corregir si es necesario

/*SDL_Rect Dibujador::posicionIsometricaPorPixel(int pixelx, int pixely,int centroPantallax,Sprite* sprite)
{
	SDL_Rect rectangulo;
	rectangulo.x= centroPantallax+0.25*pixelx-0.25*pixely-sprite->relatx();
	rectangulo.y= 0.5*pixelx+0.5*pixely-sprite->relaty();
	return rectangulo;

}*/

void Dibujador::dibujarPantalla()
{
	SDL_Flip(screen);
}