#ifndef _SURFACE_H_
#define _SURFACE_H_

#include "SDL.h"
#include <string>

namespace view{
	class Surface {
		private:
			SDL_Surface* sdlSurface;

			void setSdlSurface(SDL_Surface* sdlSurface);

		public:
			Surface();

			SDL_Surface* getSdlSurface();

			void load(std::string fileName);

			void createTransparent();

			int getWidth();

			int getHeight();

			void free();

			~Surface();
	};
}
 
#endif //_SURFACE_H_