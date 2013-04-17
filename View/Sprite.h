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

	int relx,rely,_baseWidth,_baseHeight; //Posicion relativa del Tile de referencia de la base respecto imagen
	float delay;
	float fps;
	unsigned nroFrames;
	//EntityObject* eo;

	unsigned estado; 
	std::vector<Frame*> frames;
	int comienzo_frame;

	int baseWidth();
	int baseHeight();

	void cargarFrames(std::string path,std::string nombre,std::string formato,int nro);
	void cargarFrames(string imagePath);
	void cargarFrames(DirList *imagesPaths);

public:
	Sprite(std::string path,std::string nombre,int nroFr,int relatx,int relaty);
	Sprite(std::string path,std::string nombre,int nroFr,int relatx,int relaty,float delay,float fps);
	Sprite(EntityObject *entity);
	Sprite(AnimatedEntity* entity);
	//SDL_Rect posicionIsometrica(int posx, int posy,int centroPantallax);
	Frame* getFrameActual();
	~Sprite();
	void actualizarFrame();
	int relatx();
	int relaty();
};

#endif