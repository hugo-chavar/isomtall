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
		void initialize(unsigned int width, unsigned int height, unsigned int bpp, unsigned int scrollSpeed, unsigned int scrollBoxSize); //,float offsetX, float offsetY);
		void update();
		void cleanUp();
		void render(SDL_Rect spriteRec,SDL_Surface* surface);
		~Camera();
	};

} // namespace model

#endif //_CAMERA_H_
