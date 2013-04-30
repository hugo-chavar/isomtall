#include "AnimatedEntity.h"


AnimatedEntity::AnimatedEntity() {
	this->name("DEFAULT ANIMATED ENTITY");
	this->loadImages(DEFAULT_ANIMATED_DIR); 
	this->baseWidth(DEFAULT_BASE_WIDTH);
	this->baseHeight(DEFAULT_BASE_HEIGHT);
	this->pixelRefX(DEFAULT_ANIMATED_ENTITY_PIXEL_REF_X);
	this->pixelRefY(DEFAULT_ANIMATED_ENTITY_PIXEL_REF_Y);
	this->fps(DEFAULT_FPS);
	this->delay(DEFAULT_DELAY);
}

AnimatedEntity::~AnimatedEntity() {
	
}

void AnimatedEntity::copy(AnimatedEntity* entity){
	this->baseWidth(entity->baseWidth());
	this->baseHeight(entity->baseHeight());
	this->pixelRefX(entity->pixelRefX());
	this->pixelRefY(entity->pixelRefY());
	this->fps(entity->fps());
	this->delay(entity->delay());
}

bool AnimatedEntity::hasNoImages() {
	return _images.empty();// && (_images.emptyDir())
}

bool AnimatedEntity::hasNoDir() {
	return _images.emptyDir();
}

bool AnimatedEntity::hasNextDir() {
	return _images.hasNextDir();
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
	this->clearImages();
	_images.setExtensionRequired(IMAGES_EXTENSION);
	if (this->_images.createFromDirectory(imageDir)) {
		if ((this->_images.empty())&&(this->_images.emptyDir()))
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

void AnimatedEntity::clearImages(){
	_images.clean();
}

string AnimatedEntity::nextDirectory(){
	return _images.nextFullPathDir();
}

bool AnimatedEntity::isGround(){
	return false;
}

bool AnimatedEntity::isAnimated(){
	return true;
}