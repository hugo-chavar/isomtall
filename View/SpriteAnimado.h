#pragma once
#include "Sprite.h"

class SpriteAnimado: public Sprite {

private:
	float delay;
	float fps;
	float accumulatedTime;
	
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
	float getDelay();
	void setAccumulatedTime(float ticks);
	void advance();
};

