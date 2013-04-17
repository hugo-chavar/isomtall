#include <sstream> 
#include "Sprite.h"
#include "AnimatedEntity.h"
#include "DirList.h"
//#define ppty 32 //pixels por tile en y
//#define pptx 64 //pixels por tile en x


Sprite::Sprite(std::string path,std::string nombre,int nroFr,int relatx,int relaty)
{
	comienzo_frame = 0;
	estado = 0;
	delay = 0;
	fps = 0;
	relx = relatx;
	rely = relaty;
	nroFrames = nroFr;
	cargarFrames(path, nombre, "png", nroFr);
}

Sprite::Sprite(std::string path,std::string nombre,int nroFr,int relatx,int relaty,float Delay,float Fps)
{
	comienzo_frame = SDL_GetTicks();
	estado = 0;
	delay = Delay;
	fps = Fps;
	relx = relatx;
	rely = relaty;
	nroFrames = nroFr;
	cargarFrames(path,nombre,"png",nroFr);
}

Sprite::Sprite(EntityObject *entity)
{
	comienzo_frame = SDL_GetTicks();
	estado = 0;
	relx = entity->pixelRefX();
	rely = entity->pixelRefY();
	_baseWidth = entity->baseWidth();
	_baseHeight = entity->baseHeight();
	nroFrames = 1;
	cargarFrames(entity->imagePath());
	//usar herencia para resolver esto
	delay = 0;
	fps = 0;
}

Sprite::Sprite(AnimatedEntity* entity)
{
	comienzo_frame = SDL_GetTicks();
	estado = 0;
	delay = static_cast<float>(entity->delay()); 
	fps = static_cast<float>(entity->fps());
	relx = entity->pixelRefX();
	rely = entity->pixelRefY();
	_baseWidth = entity->baseWidth();
	_baseHeight = entity->baseHeight();
	this->cargarFrames(entity->imagesPaths());	
}

Sprite::~Sprite(void)
{
	for(unsigned i=0;i<nroFrames;i++)
	{
		frames[i]->liberar();
		delete frames[i];
	}

}

	
void Sprite::cargarFrames(std::string path,std::string nombre,std::string formato,int nro)
{
	for (int i = 0; i < nro; i++)
	{
		std::stringstream string_num;
		string_num << i;
		std::string pathCompleto = path+nombre+string_num.str()+"."+formato;
		frames.push_back(new Frame());
		frames[i]->cargar(pathCompleto);
	}
}

void Sprite::cargarFrames(std::string imagePath)
{
	frames.push_back(new Frame());
	frames[0]->cargar(imagePath);
	nroFrames = 1;
}

void Sprite::cargarFrames(DirList *imagesPaths)
{
	unsigned i = 0;
	imagesPaths->restartCurrentPosition();
	while (imagesPaths->hasNext()) {
		frames.push_back(new Frame());
		frames[i]->cargar(imagesPaths->nextFullPath());
		i++;
	}
	nroFrames = imagesPaths->count();
}

bool Sprite::isAnimated(){
	return (fps > 0);
}

void Sprite::actualizarFrame()
{
	if (!isAnimated())
		return;
	if(estado == 0)
	{
		if((SDL_GetTicks()-comienzo_frame)>=(1000/fps)+delay)
			{
				if(estado >= nroFrames-1)
					estado = 0;
				else
					estado=estado++;
				comienzo_frame=SDL_GetTicks();
			}
	}
	else
	{
	if((SDL_GetTicks()-comienzo_frame) >= (1000/fps))
		{
		comienzo_frame=SDL_GetTicks();
		if(estado >= nroFrames-1)
			estado = 0;
		else
			estado = estado++;
		}
	}
}

Frame* Sprite::getFrameActual()
{
	return frames[estado];
}

int Sprite::relatx()
{
	return relx;
}

int Sprite::relaty()
{
	return rely;
}

int Sprite::baseWidth()
{
	return _baseWidth;
}
int Sprite::baseHeight()
{
	return _baseHeight;
}