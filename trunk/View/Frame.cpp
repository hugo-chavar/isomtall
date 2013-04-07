#include "Frame.h"

Frame::Frame(void)
{}


Frame::~Frame(void)
{}

int Frame::cargar(std::string path){
	superficie=IMG_Load(path.c_str());
	if(superficie==NULL)
		return 1;
	// Asignamos el color transparente al color rojo.
	SDL_SetColorKey(superficie,SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB(superficie->format,255,0,255));
	superficie=SDL_DisplayFormat(superficie);
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
	