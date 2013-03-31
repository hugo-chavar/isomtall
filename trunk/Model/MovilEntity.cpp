#include "MovilEntity.h"

using namespace model;

int MovilEntity::velocity()
{
	return _velocity;
}

int MovilEntity::direction()
{
	return _direction;
}

void MovilEntity::direction(int value)
{
	_direction = value;
}

void MovilEntity::velocity(int value)
{
	_velocity = value;
}
