#include "SpriteAnimado.h"


SpriteAnimado::SpriteAnimado(AnimatedEntity* entity)
{
	this->inicializar(entity->pixelRefX(),entity->pixelRefY(),entity->baseWidth(),entity->baseHeight());
	comienzo_frame = SDL_GetTicks();
	delay = static_cast<float>(entity->delay()); 
	fps = static_cast<float>(entity->fps());
	cargarFrames(entity);
}


SpriteAnimado::~SpriteAnimado()
{
}

void SpriteAnimado::actualizarFrame()
{
	if(estado == 0)
	{
		if((SDL_GetTicks()-comienzo_frame)>=(1000/fps)+delay)
			{
				if(estado >= frames.size()-1)
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
		if(estado >= frames.size()-1)
			estado = 0;
		else
			estado = estado++;
		}
	}
}

void SpriteAnimado::cargarFrames(AnimatedEntity * entity)
{
	unsigned i = 0;
	entity->imagesPaths()->restartCurrentPosition();
	//if (imagesPaths->defaulted()){
	//	frames[0]->cargar(imagesPaths->getDefault());
	//	return;
	//}
	while (entity->imagesPaths()->hasNext()) {
		frames.push_back(new Frame());
		
		frames[i]->cargar(entity->imagesPaths()->nextFullPath());
		i++;
	}
}