#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "SDL.h"

#include <utility>

namespace model {

	class Camera {
	private:
		//X axis camera offset in pixels.
		int offsetX;
		//Y axis camera offset in pixels.
		int offsetY;
		//Camera speed in pixels/seconds.
		unsigned int scrollSpeed;
		//Camera scroll box size
		unsigned int scrollBoxSize;
		void setOffsetX(int offsetX);
		void setOffsetY(int offsetY);
		void setScrollSpeed(unsigned int scrollSpeed);
		void setScrollBoxSize(unsigned int scrollBoxSize);
	public:
		Camera();
		SDL_Surface* cameraSurface;
		int getOffsetX();
		int getOffsetY();
		unsigned int getScrollSpeed();
		unsigned int getScrollBoxSize();
		unsigned int getWidth();
		unsigned int getHeight();
		void initialize(unsigned int width, unsigned int height, unsigned int bpp, unsigned int scrollSpeed, unsigned int scrollBoxSize, int offsetX, int offsetY);
		void update();
		void cleanUp();
		~Camera();
		std::pair<int,int> pixelToTileCoordinates(std::pair<int,int> pixelCoordinates);
	};

} // namespace model

#endif //_CAMERA_H_
