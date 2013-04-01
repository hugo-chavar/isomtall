#ifndef _TILE_H_
#define _TILE_H_

#include <string>
#include "SDL.h"
#include "Surface.h"


namespace model {

//TODO: Not very clear which part of this tile should be in the view.
	//
	class Tile {
	private:
		//Speed lose in this tile in pixels/seconds.
		//TODO: Mariano este speed se refiere a que el tile se mueve o a la frecuencia de actualizacion del objeto?
		unsigned int speedPenalty;

		//X axis tile center in pixels.
		unsigned int centerX;

		//Y axis tile center in pixels.
		unsigned int centerY;

	public:
		//Constructor to load tile from image file.
		//TODO: Mariano aclará que representa offsetX y offsetY
		Tile(std::string filePath, unsigned int offsetX, unsigned int offsetY, unsigned int height, unsigned int width, unsigned int speedPenalty, unsigned int centerX, unsigned int centerY);

		//Constuctor to load tile from SDL surface, i.e. from a tileset.
		Tile(SDL_Surface* sourceSdlSurface, unsigned int offsetX, unsigned int offsetY, unsigned int height, unsigned int width, unsigned int speedPenalty, unsigned int centerX, unsigned int centerY);

		// TODO: There must be only one instance of every tile type all pointing to the same surface.
		// Es posible que sea necesario una lista de surfaces dentro del tile, x ejemplo el suelo mas un personaje q esta pasando por ahi?
		SDL_Surface* sdlSurface;

		unsigned int getSpeedPenalty();

		unsigned int getCenterX();

		unsigned int getCenterY();

		void cleanUp();

		~Tile();
	};

} // namespace model

#endif //_TILE_H_