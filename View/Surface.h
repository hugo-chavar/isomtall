#ifndef _SURFACE_H_
#define _SURFACE_H_

#include "SDL.h"
#include <string>
#include <vector>

namespace view{
	class Surface {
		private:
			SDL_Surface* surface;
			std::vector <SDL_Surface*> shadows;
			void setSurface(SDL_Surface* surface);
			void addShadowSurface(SDL_Surface* surface);

		public:
			static const Uint32 HEXA_WHITE_COLOR;
			static const Uint32 HEXA_RED_COLOR;
			static const Uint32 HEXA_BLUE_COLOR;
			static const Uint32 HEXA_LIGHT_BLUE_COLOR;
			static const Uint32 HEXA_BLACK_COLOR;
			static const Uint32 HEXA_GREEN_COLOR;
			Surface();
			SDL_Surface* getSurface();
			SDL_Surface* getBlackShadow();
			SDL_Surface* getWhiteShadow();
			SDL_Surface* getSurfaceToShow(bool fogged);
			void load(std::string fileName);
			int getWidth();
			int getHeight();
			void free();
			~Surface();
			void setTransparent();
			void setOpaque();
			void createShadow(Uint32 color);
			void createShadows();

	};
}
 
#endif //_SURFACE_H_