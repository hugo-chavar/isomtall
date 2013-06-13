#ifndef _MOVABLE_H_
#define _MOVABLE_H_

#include "Entity.h"
#include "Directionable.h"
#include "Positionable.h"

class Movable: public Entity, Positionable, Directionable {

private:
	float velocity;
	std::pair<float, float> remaining;
	std::pair<int, int> targetTile;
	std::pair<int, int> initialTile;
	std::pair<int, int> currentTile;
	std::pair<int, int> lastTile;
	bool targetReached;
	bool _couldContinue;
	//string name;

public:
	Movable();
	~Movable();
	//----- Getters/Setters methods -----
	void setVelocity(float value);
	float getVelocity();
	void setTargetTile(std::pair<int, int> value);
	std::pair<int, int> getTargetTile();
	void setInitialTile(std::pair<int, int> value);
	std::pair<int, int> getInitialTile();
	void setTargetReached(bool value);
	bool isTargetReached();
	void setCouldContinue(bool value);
	bool couldContinue();
	//----- Functional methods  -----
	void update();
	void render(Camera& camera);
	void move();
	bool validTilePosition(std::pair<int, int> pixelPosition);
	void calculateWayForward();
	void verify();
	bool isAlive();
	//------ Maybe useful in the future ----
	bool isItem();
	//string getName();
	//std::pair<int, int> getTraslation();
};

#endif // _MOVABLE_H_

