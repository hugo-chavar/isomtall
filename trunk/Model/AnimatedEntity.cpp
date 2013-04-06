#include "AnimatedEntity.h"

using namespace model;



AnimatedEntity::AnimatedEntity() {
	// DEFINIR _fps, _delay
}

AnimatedEntity::~AnimatedEntity() { }

int AnimatedEntity::fps()
{
	return _fps;
}

int AnimatedEntity::delay()
{
	return _delay;
}

void AnimatedEntity::fps(int value)
{
	_fps = value;
}

void AnimatedEntity::delay(int value)
{
	_delay = value;
}