#ifndef _SURFACE_H_
#define _SURFACE_H_

#include "SDL.h"
#include <string>

namespace view{
	class Surface {
		private:
			SDL_Surface* surface;

			SDL_Surface* shadow;

			void setSurface(SDL_Surface* surface);

			void setShadowSurface(SDL_Surface* surface);

		public:
			Surface();

			SDL_Surface* getSurface();

			SDL_Surface* getShadow();

			SDL_Surface* getSurfaceToShow(bool fogged);

			void load(std::string fileName);

			int getWidth();

			int getHeight();

			void free();

			~Surface();

			void setTransparent();

			void setOpaque();

			void createShadow();

	};
}
 
#endif //_SURFACE_H_