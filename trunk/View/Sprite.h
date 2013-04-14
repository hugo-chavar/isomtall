#pragma once

#ifndef _SPRITE_H_
#define _SPRITE_H_


#include <iostream>
#include <vector>
#include <list>
#include "Frame.h"
#include "AnimatedEntity.h"



class Sprite
{

private:

	// lo siguiente va al modelo y se obtienen con getters
	int relx,rely; //Posicion relativa del Tile de referencia de la base respecto imagen
	float delay;
	float fps;
	unsigned nroFrames;
	EntityObject* eo;

	unsigned estado; 
	std::vector<Frame*> frames;
	int comienzo_frame;

	void cargarFrames(std::string path,std::string nombre,std::string formato,int nro);
	void cargarFrames(std::list<std::string> imagesPaths); // Para que funcione por ahora

public:
	Sprite(std::string path,std::string nombre,int nroFr,int relatx,int relaty);
	Sprite(std::string path,std::string nombre,int nroFr,int relatx,int relaty,float delay,float fps);
	Sprite(std::list<std::string>imagesPaths,int relatx,int relaty,float delay,float fps); // Para que funcione por ahora
	Sprite(AnimatedEntity*); // Para que funcione por ahora
	//SDL_Rect posicionIsometrica(int posx, int posy,int centroPantallax);
	Frame* getFrameActual();
	~Sprite();
	void actualizarFrame();
	int relatx();
	int relaty();
};

#endif