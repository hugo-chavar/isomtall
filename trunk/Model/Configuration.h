#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

#include "Constants.h"
#include "Logger.h"

namespace model
{

	class Configuration
	{
	public:
		Configuration();
		~Configuration();
		unsigned int cameraWidth();
		unsigned int cameraHeight();
		void cameraWidth(int);
		void cameraHeight(int);
		unsigned int cameraMarginScroll();
		void cameraMarginScroll(int);
		unsigned int cameraSpeed();
		void initialize(int dimentionX, int dimentionY, int scrollMargin);
		unsigned int serverPort();
		void serverPort(int);
		unsigned int visionRange();
		void visionRange(int);
	private:
		unsigned int _serverPort;
		unsigned int _cameraWidth;
		unsigned int _cameraHeight;
		unsigned int _cameraMarginScroll;
		unsigned int _cameraScrollSpeed;
		unsigned int _visionRange;
	};

	

}
#endif //_CONFIGURATION_H_