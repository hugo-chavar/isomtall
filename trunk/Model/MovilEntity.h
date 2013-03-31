#include "EntityObject.h"

namespace model
{
	class MovilEntity: public EntityObject
	{
	public:
		int velocity();
		void velocity(int);
		int direction();
		void direction(int);
	private:
		int _direction;
		int _velocity;
	};

}