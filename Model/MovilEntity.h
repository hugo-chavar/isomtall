#ifndef _MOVILENTITY_H_
#define _MOVILENTITY_H_

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
#endif //_MOVILENTITY_H_