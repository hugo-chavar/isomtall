#ifndef __MAINCHARACTER_H_
#define __MAINCHARACTER_H_

#include "AnimatedEntity.h"


class MainCharacter {

public:
	MainCharacter();
	~MainCharacter();
	MainCharacter(AnimatedEntity *entityType, int x, int y): _entity_type(entityType), _x(x), _y(y) { };
	AnimatedEntity *entityType();
	int x();
	int y();
	int speed();
	void speed(int value);

private:
	AnimatedEntity *_entity_type;
	int _x;
	int _y;
	int _speed;
};


#endif