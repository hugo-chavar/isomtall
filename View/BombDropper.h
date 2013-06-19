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
	unsigned getAmmo();
	void setAmmo(unsigned ammo);

private:
	std::vector<Bomb*> bombs;
	unsigned ammo;
	unsigned nextBombIndex;
	unsigned getNextBombIndex();
	void setNextBombIndex(unsigned value);
};


#endif // _BOMB_DROPPER_H_