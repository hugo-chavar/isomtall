#ifndef _ANIMATEDENTITY_H_
#define _ANIMATEDENTITY_H_

#include "EntityObject.h"


class AnimatedEntity: public EntityObject {

public:
	AnimatedEntity();
	~AnimatedEntity();
	AnimatedEntity(string name, string imagePath, int baseWidth, int baseHeight, int pixelRefX, int pixelRefY, int nFrames, int fps, int delay): 
		EntityObject(name, imagePath, baseWidth, baseHeight, pixelRefX, pixelRefY), _nFrames(nFrames), _fps(fps), _delay(delay) { };
	int fps();
	void fps(int);
	int delay();
	void delay(int);
	int nFrames();

private:
	int _fps;
	int _delay;
	int _nFrames;
};


#endif