#include "AnimatedEntity.h"


AnimatedEntity::AnimatedEntity() {
	_fps = DEFAULT_FPS;
	_delay = DEFAULT_DELAY;
}

AnimatedEntity::~AnimatedEntity() {
	
}

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

DirList* AnimatedEntity::imagesPaths() {
	return _imagesPaths;
}

void AnimatedEntity::destroy(){
	delete _imagesPaths;
}