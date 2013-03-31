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