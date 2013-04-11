#include "AnimatedEntity.h"


AnimatedEntity::AnimatedEntity() {
	DirList dirList;
	dirList.createFromDirectory(DEFAULT_ANIMATED_DIR);
	while (dirList.hasNext()) {
		_imagesPaths.push_back(dirList.nextFullPath());
	}
	_fps = DEFAULT_FPS;
	_delay = DEFAULT_DELAY;
	imagePath("");
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

list <string> AnimatedEntity::imagesPaths() {
	return _imagesPaths;
}