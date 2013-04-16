#include "AnimatedEntity.h"


AnimatedEntity::AnimatedEntity() {
	this->name("DEFAULT");
	this->loadImages(DEFAULT_ANIMATED_DIR);
	this->baseWidth(DEFAULT_BASE_WIDTH);
	this->baseHeight(DEFAULT_BASE_HEIGHT);
	this->pixelRefX(DEFAULT_PIXEL_REF_X);
	this->pixelRefY(DEFAULT_PIXEL_REF_Y);
	_fps = DEFAULT_FPS;
	_delay = DEFAULT_DELAY;
}

AnimatedEntity::~AnimatedEntity() {
	
}

bool AnimatedEntity::isAnimated() {
	return true;
}

bool AnimatedEntity::hasNoImages() {
	return _images.empty();
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

void AnimatedEntity::loadImages(string imageDir) {
	_images.clean();
	_images.setExtensionRequired(IMAGES_EXTENSION);
	if (this->_images.createFromDirectory(imageDir)) {
		if (this->_images.empty())
			Logger::instance().log("Parser Error: No '.png' images found in the directory '"+imageDir+"'.");
	}
	else
		Logger::instance().log("Parser Error: Image directory '"+imageDir+"' not found.");
}

unsigned AnimatedEntity::imagesCount()
{
	return _images.count();
}

DirList* AnimatedEntity::imagesPaths() {
	return &_images;
}