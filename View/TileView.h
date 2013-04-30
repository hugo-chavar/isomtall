#ifndef _TILEVIEW_H_
#define _TILEVIEW_H_

#include <string>
//#include "SDL.h"
#include "TileModel.h"
#include "Surface.h"



	class TileView {
	private:
		//unsigned int speedPenalty;
		//unsigned int centerX;
		//unsigned int centerY;

		TileModel* tileModel;
		TileView * nextDrawableTile;
	public:
		//Constructor to load tile from image file.
		//TileView(std::string filePath, unsigned int offsetX, unsigned int offsetY, unsigned int height, unsigned int width, unsigned int speedPenalty, unsigned int centerX, unsigned int centerY);

		//Constuctor to load tile from SDL surface, i.e. from a tileset.
		//TileView(SDL_Surface* sourceSdlSurface, unsigned int offsetX, unsigned int offsetY, unsigned int height, unsigned int width, unsigned int speedPenalty, unsigned int centerX, unsigned int centerY);

		// TODO: There must be only one instance of every tile type all pointing to the same surface.
		//SDL_Surface* sdlSurface;

		//unsigned int getSpeedPenalty();

		//unsigned int getCenterX();

		//unsigned int getCenterY();

		void cleanUp();

		~TileView();
	};



#endif //_TILE_H_