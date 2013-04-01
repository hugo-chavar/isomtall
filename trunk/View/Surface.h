#ifndef _SURFACE_H_
#define _SURFACE_H_

#include "SDL.h"
#include <string>

//TODO: static class completely copied from SDL tutorials. This methos shoud be in an abstract class from which all views should inherit.
//Esta clase vendria a ser el equivalente en la vista de la clase EntityObject del modelo, son dos estructuras conectadas
namespace view{
	class Surface {
		public:
			Surface();

			static SDL_Surface* loadFromBMP(std::string fileName);

			static bool draw(SDL_Surface* source, SDL_Surface* destination, unsigned int destinationOffsetX, unsigned int destinationOffsetY);

			static bool draw(SDL_Surface* source, unsigned int sourceOffsetX, unsigned int sourceOffsetY, unsigned int sourceHeight, unsigned int sourceWidth, SDL_Surface* destination, unsigned int destinationOffsetX, unsigned int destinationOffsetY);

			~Surface();
	};
}
 
#endif //_SURFACE_H_