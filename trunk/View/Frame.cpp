#include "Frame.h"
#include "Logger.h"

using namespace common;

Frame::Frame(void)
{}


Frame::~Frame(void)
{}

int Frame::cargar(std::string path){
	SDL_Surface * superficie1=IMG_Load(path.c_str());
	if(superficie1==NULL)
		{Logger::instance().log(path);
		return 1;
		}
	
	superficie=SDL_DisplayFormat(superficie1);
	SDL_FreeSurface(superficie1);
	// Asignamos el color transparente al color rojo.
	SDL_SetColorKey(superficie,SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB(superficie->format,255,0,255));
	return 0;
}
	
void Frame::liberar()
	{
		SDL_FreeSurface(superficie);
	}

SDL_Surface* Frame::getSuperficie()
{
	return superficie;
}
	
void Frame::setSuperficie(SDL_Surface* superf)
{
	superficie=superf;
}
	