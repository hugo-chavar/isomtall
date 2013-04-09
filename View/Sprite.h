#pragma once
#include "Frame.h"
#include <iostream>
#include <vector>


class Sprite
{

private:

	// lo siguiente va al modelo y se obtienen con getters
	int relx,rely; //Posicion relativa del Tile de referencia de la base respecto imagen
	float delay;
	float fps;
	unsigned nroFrames;	
	


	unsigned estado; 
	std::vector<Frame *> frames;
	int comienzo_frame;

	void cargarFrames(std::string path,std::string nombre,std::string formato,int nro);

public:
	Sprite(std::string path,std::string nombre,int nroFr,int relatx,int relaty);
	Sprite(std::string path,std::string nombre,int nroFr,int relatx,int relaty,float delay,float fps);
	//SDL_Rect posicionIsometrica(int posx, int posy,int centroPantallax);
	Frame* getFrameActual();
	~Sprite();
	void actualizarFrame();
	int relatx();//getter
	int relaty();//getter
};

