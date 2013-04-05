#ifndef _ANIMATEDENTITY_H_
#define _ANIMATEDENTITY_H_

#include "EntityObject.h"

namespace model
{
	class AnimatedEntity: public EntityObject
	{
	public:
		int fps();
		void fps(int);
		int delay();
		void delay(int);
	private:
		int _fps;
		int _delay;
	};

}

#endif //_ANIMATEDENTITY_H_