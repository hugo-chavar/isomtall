#ifndef _ANIMATEDENTITY_H_
#define _ANIMATEDENTITY_H_

#include "EntityObject.h"
#include "DirList.h"
#include <list>


class AnimatedEntity: public EntityObject {

public:
	AnimatedEntity();
	~AnimatedEntity();
	AnimatedEntity(string name, string imagePath, int baseWidth, int baseHeight, int pixelRefX, int pixelRefY, DirList* imagesPaths, int fps, int delay): 
		EntityObject(name, imagePath, baseWidth, baseHeight, pixelRefX, pixelRefY), _imagesPaths(imagesPaths), _fps(fps), _delay(delay) { };
	int fps();
	void fps(int);
	void destroy(); //llamar en algun lado
	int delay();
	void delay(int);
	DirList* imagesPaths();

private:
	int _fps;
	int _delay;
	DirList* _imagesPaths;
};


#endif