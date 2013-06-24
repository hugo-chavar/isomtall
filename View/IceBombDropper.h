#pragma once

#ifndef BOMB_POOL_SIZE
#define BOMB_POOL_SIZE 5
#endif//BOMB_POOL_SIZE

#include "IceBomb.h"
#include "Weapon.h"


class IceBombDropper: public Weapon {

public:
	IceBombDropper();
	~IceBombDropper();
	void strike(Daniable* target);
	std::vector<IceBomb*>& getBombs();
	IceBomb* getAvailableBomb();
	//----- Functional methods  -----
	bool sameDirection(std::pair<int, int> tile);
	bool isInsideRange(std::pair<int, int> tile);
	bool needsToReposition(std::pair<int, int> tile);
	bool readyToStrike(std::pair<int, int> tile);
private:
	std::vector<IceBomb*> bombs;
	unsigned nextBombIndex;
	unsigned getNextBombIndex();
	void setNextBombIndex(unsigned value);
};
