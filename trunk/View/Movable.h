#ifndef _MOVABLE_H_
#define _MOVABLE_H_

#include "Entity.h"
#include "Directionable.h"
#include "Positionable.h"

class Movable: public Entity, public Positionable, public Directionable {

private:
	float velocity;
	std::pair<float, float> remaining;
	std::pair<int, int> targetTile;
	std::pair<int, int> initialTile;
	std::pair<int, int> currentTile;
	std::pair<int, int> lastTile;
	bool targetReached;
	bool _couldContinue;
	//bool bouncing;

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
	void setCurrentTile(std::pair<int, int> value);
	std::pair<int, int> getCurrentTile();
	void setLastTile(std::pair<int, int> value);
	std::pair<int, int> getLastTile();
	void setTargetReached(bool value);
	bool isTargetReached();
	void setCouldContinue(bool value);
	bool couldContinue();
	//void setBouncing(bool value);
	//bool isBouncing();
	//----- Functional methods  -----
	void update();
	void render(Camera& camera);
	void move();
	bool validTilePosition(std::pair<int, int> pixelPosition);
	std::pair<int, int> whichTile(std::pair<int, int> pixel);
	void calculateWayForward();
	virtual void verify();
	bool isAlive();
	void initialize();
	bool isItem();
	bool goingDiagonal();
};

#endif // _MOVABLE_H_

