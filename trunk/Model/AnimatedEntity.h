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
	int fps();
	void fps(int);
	int delay();
	void delay(int);
	void loadImages(string);
	DirList* imagesPaths();
	unsigned imagesCount();
	bool hasNoImages();
	bool hasNextDir();
	string nextDirectory();
	void clearImages();
	void copy(AnimatedEntity*);
	bool hasNoDir();
	bool isGround();
	bool isAnimated();
private:
	int _fps;
	int _delay;
	DirList _images;
};


#endif