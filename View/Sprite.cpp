#include "Sprite.h"
#include "AnimatedEntity.h"
#include "DirList.h"
#include <sstream> 
#define ppty 32 //pixels por tile en y
#define pptx 64 //pixels por tile en x


Sprite::Sprite(std::string path,std::string nombre,int nroFr,int relatx,int relaty)
{
	//propiedades q tienen que ver con la entidad concreta (es externo al sprite porque muchas entidades pueden apuntar al mismo sprite)
	comienzo_frame=0; // sacar este campo a una entidad externa y obtenerla x parametro en todos los metodos para calcular
	estado=0; // sacar este campo a una entidad externa y obtenerla x parametro en todos los metodos para calcular

	
	//propiedades q tienen q ver con el Sprite
	//debe tener un constructor que solo reciba un puntero a la entidad del modelo (Hugo)
	//y obtener estos datos de esa entidad
	delay=0; // cada llamada se reemplaza por algo asi, this->entidad->getDelay();
	fps=0;
	relx=relatx;
	rely=relaty;
	nroFrames=nroFr;
	//TODO: Hugo: reemplazar por una lista de archivos tipo el tp de datos
	//cargarFrames(this->entitad.getListaImagenes());
	cargarFrames(path,nombre,"png",nroFr);//podria agregarle el parametro formato a el constructor
}

//Constructor por sobrecarga para entidades animadas
//debe tener un constructor que solo reciba un puntero a la entidad del modelo (Hugo)
Sprite::Sprite(std::string path,std::string nombre,int nroFr,int relatx,int relaty,float Delay,float Fps)
{

	
	comienzo_frame=SDL_GetTicks();
	estado=0;


	delay=Delay;
	fps=Fps;
	relx=relatx;
	rely=relaty;
	nroFrames=nroFr;
	cargarFrames(path,nombre,"png",nroFr);
	
}

Sprite::Sprite(EntityObject *entity)
{
	comienzo_frame=SDL_GetTicks();
	estado=0;
	relx=entity->pixelRefX();
	rely=entity->pixelRefY();
	nroFrames = 1; //entity->imagePath().size();
	cargarFrames(entity->imagePath());
}

Sprite::Sprite(AnimatedEntity* entity)
{
	comienzo_frame = SDL_GetTicks();
	estado = 0;
	delay = static_cast<float>(entity->delay()); 
	fps = static_cast<float>(entity->fps());
	relx = entity->pixelRefX();
	rely = entity->pixelRefY();
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
	for (int i=0;i<nro;i++)
	{
		std::stringstream string_num;
		string_num << i;
		std::string pathCompleto=path+nombre+string_num.str()+"."+formato;
		frames.push_back(new Frame());
		frames[i]->cargar(pathCompleto);
	}
}

void Sprite::cargarFrames(std::string imagePath)
{
	frames.push_back(new Frame());
	frames[0]->cargar(imagePath);
}

void Sprite::cargarFrames(DirList *imagesPaths)
{
	unsigned i = 0;
	while (imagesPaths->hasNext()) {
		frames.push_back(new Frame());
		frames[i]->cargar(imagesPaths->nextFullPath());
		i++;
	}
}

void Sprite::actualizarFrame()
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