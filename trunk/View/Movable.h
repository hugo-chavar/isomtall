#ifndef _MOVABLE_H_
#define _MOVABLE_H_

#include "Entity.h"
#include "Directionable.h"
#include "Positionable.h"

class Movable: public Entity, Positionable, Directionable {

private:
	//string name;
	float velocity;
	std::pair<float, float> remaining;

public:

	//string getName();
	Movable();
	~Movable();
	void update();
	void render(Camera& camera);
	void setVelocity(float veloc);
	float getVelocity();
	void move();
	std::pair<int, int> getTilePosition(std::pair<int, int> pixelPosition);
	bool validTilePosition(std::pair<int, int> pixelPosition);
};

#endif // _MOVABLE_H_

