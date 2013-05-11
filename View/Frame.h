#pragma once
#include <SDL.h>
#include <string>
#include <SDL_image.h>

class Frame
{
private:
	SDL_Surface* superficie;
public:
	Frame();
	int cargar(std::string path);
	void liberar();
	SDL_Surface* Frame::getSuperficie(bool freezed);
	SDL_Surface* Frame::getSuperficie();
	~Frame();
	void setSuperficie(SDL_Surface* superf);
};

