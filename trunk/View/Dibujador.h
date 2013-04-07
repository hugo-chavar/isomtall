#pragma once

#include "Sprite.h"


class Dibujador
{
private:
	SDL_Surface* screen;

	SDL_Rect posicionIsometricaPorTiles(int posx, int posy,int centroPantallax,Sprite* sprite);
	//SDL_Rect posicionIsometricaPorPixel(int pixelx, int pixely,int centroPantallax,Sprite* sprite);
public:
	void cargarImagenEnTile(int tilex,int tiley,int centroPantallax,Sprite* sprite);
	void dibujarPantalla();
	void limpiarPantalla();
	//void cargarImagenEnPixel(int pixelx, int pixely,int centroPantallax,Sprite* sprite);
	Dibujador(int ancho,int alto);
	~Dibujador();
	bool pantallaCreada();
};

