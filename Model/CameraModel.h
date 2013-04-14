#ifndef _CAMERAMODEL_H_
#define _CAMERAMODEL_H_

#include "Constants.h"
#include "Logger.h"

namespace model
{

	class CameraModel
	{
	public:
		CameraModel();
		~CameraModel();
		unsigned int width();
		unsigned int height();
		void width(int);
		void height(int);
		unsigned int scroll();
		void scroll(int);
		unsigned int speed();
		void initialize(int dimentionX, int dimentionY, int scrollMargin);
	private:
		unsigned int _width;
		unsigned int _height;
		unsigned int _scroll;
		unsigned int _speed;
	};

	

}
#endif //_CAMERAMODEL_H_