#pragma once
#include "Sprite.h"

class SpriteAnimado: public Sprite {

private:
	float delay;
	float fps;
	float accumulatedTime;
	void advance();
	bool timeIsOver();
	
	void loadSurfaces();
public:
	void initialize();
	void updateFrame();
	void getNextFrame();
	SpriteAnimado(AnimatedEntity* entity);
	bool lastFrame();
	~SpriteAnimado();
	void addSticks(float ticks);
};

