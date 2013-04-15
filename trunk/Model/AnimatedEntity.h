#ifndef _ANIMATEDENTITY_H_
#define _ANIMATEDENTITY_H_

#include <list>
#include <string>
#include "EntityObject.h"
#include "DirList.h"
#include "Logger.h"


using namespace common;



class AnimatedEntity: public EntityObject {

public:
	AnimatedEntity();
	~AnimatedEntity();
	//AnimatedEntity(string name, string imagePath, int baseWidth, int baseHeight, int pixelRefX, int pixelRefY, DirList* imagesPaths, int fps, int delay): 
	//	EntityObject(name, imagePath, baseWidth, baseHeight, pixelRefX, pixelRefY), _imagesPaths(imagesPaths), _fps(fps), _delay(delay) { };
	int fps();
	void fps(int);
	int delay();
	void delay(int);
	void loadImages(string);
	DirList* imagesPaths();
	unsigned imagesCount();
	bool isAnimated();
	bool hasNoImages();

private:
	int _fps;
	int _delay;
	DirList _images;
};


#endif