#include "AnimatedEntity.h"


AnimatedEntity::AnimatedEntity() {
	_fps = DEFAULT_FPS;
	_delay = DEFAULT_DELAY;
	imagePath(DEFAULT_ANIMATED_DIR);
	_nFrames = DEFAULT_NUMBER_OF_FRAMES;
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

int AnimatedEntity::nFrames() {
	return _nFrames;
}