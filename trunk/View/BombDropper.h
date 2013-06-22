#ifndef _BOMB_DROPPER_H_
#define _BOMB_DROPPER_H_

#ifndef BOMB_POOL_SIZE
#define BOMB_POOL_SIZE 5
#endif//BOMB_POOL_SIZE

#include "Bomb.h"
#include "Weapon.h"


class BombDropper: public Weapon {

public:
	BombDropper();
	~BombDropper();
	void strike(Daniable* target);
	std::vector<Bomb*>& getBombs();
	Bomb* getAvailableBomb();
	//----- Functional methods  -----
	bool sameDirection(std::pair<int, int> tile);
	bool isInsideRange(std::pair<int, int> tile);
	bool needsToReposition(std::pair<int, int> tile);
	bool readyToStrike(std::pair<int, int> tile);
private:
	std::vector<Bomb*> bombs;
	unsigned nextBombIndex;
	unsigned getNextBombIndex();
	void setNextBombIndex(unsigned value);
};


#endif // _BOMB_DROPPER_H_