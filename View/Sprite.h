#pragma once
#include "Frame.h"
#include <iostream>
#include <vector>


class Sprite
{

protected:
	//Posicion relativa del Tile de referencia de la base respecto imagen
	int relx,rely;

	Sprite();

	unsigned estado;
	std::vector<Frame *> frames;
	unsigned nroFrames;

	float delay;
	float fps;
	int comienzo_frame;

	void cargarFrames(std::string path,std::string nombre,std::string formato,int nro);

public:
	Sprite(std::string path,std::string nombre,int nroFr,int relatx,int relaty);
	Sprite(std::string path,std::string nombre,int nroFr,int relatx,int relaty,float delay,float fps);
	
	virtual Frame* getFrameActual();
	~Sprite();
	void actualizar();
	int relatx();//getter
	int relaty();//getter
};

