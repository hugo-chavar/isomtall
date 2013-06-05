#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "SDL.h"

namespace view {

	class Camera {
	private:
		//X axis camera offset in pixels.
		float offsetX;
		//Y axis camera offset in pixels.
		float offsetY;
		//Camera speed in pixels/seconds.
		unsigned int scrollSpeed;
		//Camera scroll box size
		unsigned int scrollBoxSize;
		void setScrollSpeed(unsigned int scrollSpeed);
		void setScrollBoxSize(unsigned int scrollBoxSize);
	public:
		static const SDL_Color WHITE_COLOR;
		static const SDL_Color RED_COLOR;
		static const SDL_Color BLUE_COLOR;
		static const SDL_Color BLACK_COLOR;
		static const SDL_Color GREEN_COLOR;
		Camera();
		void setOffsetX(float offsetX);
		void setOffsetY(float offsetY);
		//TODO: make getter.
		SDL_Surface* cameraSurface;
		float getOffsetX();
		float getOffsetY();
		unsigned int getScrollSpeed();
		unsigned int getScrollBoxSize();
		int getWidth();
		int getHeight();
		void initialize();
		void configure();
		void unconfigure();
		void update();
		void cleanUp();
		void render(SDL_Rect spriteRec,SDL_Surface* surface);
		void startScreen(unsigned width, unsigned height);
		~Camera();
	};

} // namespace model

#endif //_CAMERA_H_
