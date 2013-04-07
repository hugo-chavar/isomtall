#include "Sprite.h"
#include <sstream> 
#define ppty 32 //pixels por tile en y
#define pptx 64 //pixels por tile en x


Sprite::Sprite()
{}

Sprite::Sprite(std::string path,std::string nombre,int nroFr,int relatx,int relaty)
{
	delay=0;
	comienzo_frame=0;
	fps=0;
	estado=0;
	relx=relatx;
	rely=relaty;
	nroFrames=nroFr;
	cargarFrames(path,nombre,"png",1);//podria agregarle el parametro formato a el constructor
}

//Constructor por sobrecarga para entidades animadas
Sprite::Sprite(std::string path,std::string nombre,int nroFr,int relatx,int relaty,float Delay,float Fps)
{

	delay=Delay;
	fps=Fps;
	estado=0;
	relx=relatx;
	rely=relaty;
	nroFrames=nroFr;
	cargarFrames(path,nombre,"png",nroFr);
	comienzo_frame=SDL_GetTicks();
}

Sprite::~Sprite()
{
			frames[0]->liberar();
			delete frames[0];
}
	
void Sprite::cargarFrames(std::string path,std::string nombre,std::string formato,int nro)
{
	for (int i=0;i<nro;i++)
	{
		std::stringstream string_num;
		string_num << i;
		std::string pathCompleto=path+nombre+string_num.str()+"."+formato;
		frames.push_back(new Frame());
		frames[i]->cargar(pathCompleto);
	}
}


void Sprite::actualizar()
{
	if(estado==0)
	{
		if((SDL_GetTicks()-comienzo_frame)>=(1000/fps)+delay)
			{
				estado++;
				comienzo_frame=SDL_GetTicks();
			}
	}
	else
	{
	if((SDL_GetTicks()-comienzo_frame)>=(1000/fps))
		{
		comienzo_frame=SDL_GetTicks();
		if(estado>=nroFrames-1)
			estado=0;
		else
			estado=estado++;
		}
	}
}

Frame* Sprite::getFrameActual()
{
	return frames[0];
}

int Sprite::relatx()
{
	return relx;
}
int Sprite::relaty()
{
	return rely;
}