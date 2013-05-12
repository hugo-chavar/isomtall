#pragma once

#ifndef _SPRITE_H_
#define _SPRITE_H_


#include <iostream>
#include <vector>
#include <list>
#include "Frame.h"
#include "Surface.h"
#include "AnimatedEntity.h"



class Sprite {

protected:

	int relx,rely,_baseWidth,_baseHeight; //Posicion relativa del Tile de referencia de la base respecto imagen
	//float delay;
	//float fps;
	//unsigned nroFrames;
	EntityObject* spriteEntity;

	unsigned estado; 
	//std::vector<Frame*> frames;
	std::vector<view::Surface* > surfaces;
	//int comienzo_frame;

	//void cargarFrames(std::string path,std::string nombre,std::string formato,int nro);
	//void cargarFrame(EntityObject* entity);
	//virtual void loadSurfaces(EntityObject* entity);
	virtual void loadSurfaces();
	//void cargarFrames(DirList *imagesPaths);
	//void inicializar(int refX,int refY,int baseWidth,int baseHeight);
	virtual void initialize();

public:
	//Sprite(std::string path,std::string nombre,int nroFr,int relatx,int relaty);
	//Sprite(std::string path,std::string nombre,int nroFr,int relatx,int relaty,float delay,float fps);
	Sprite(EntityObject *entity);
	Sprite();
	
	//Sprite(AnimatedEntity* entity);
	//SDL_Rect posicionIsometrica(int posx, int posy,int centroPantallax);
	//Frame* getFrameActual();
	~Sprite();
	virtual void actualizarFrame();
	int relatx();
	int relaty();
	int baseWidth();
	int baseHeight();
	unsigned getCurrentState();
	//Frame* getFrameAt(int state);
	view::Surface* getSurfaceAt(int state);
	view::Surface* getCurrentSurface();
	void addSurface(std::string path);
};

#endif