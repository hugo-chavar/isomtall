#ifndef __MAINCHARACTER__
#define __MAINCHARACTER_H__

#include "AnimatedEntity.h"


namespace model {
	class MainCharacter {

	public:
		MainCharacter();
		~MainCharacter();
		MainCharacter(AnimatedEntity *entityType, int x, int y): _entity_type(entityType), _x(x), _y(y) { };
		AnimatedEntity *entityType();
		int x();
		int y();

	private:
		AnimatedEntity *_entity_type;
		int _x;
		int _y;
	};
}


#endif