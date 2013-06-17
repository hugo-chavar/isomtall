#ifndef _BOW_H_
#define _BOW_H_

#ifndef ARROW_POOL_SIZE
#define ARROW_POOL_SIZE 5
#endif//ARROW_POOL_SIZE

#include "Arrow.h"
#include "Weapon.h"

class Bow: public Weapon {

public:
	Bow();
	~Bow();
	void strike(Daniable* target);
	std::vector<Arrow*>& getArrows();
	Arrow* getAvailableArrow();
	unsigned getAmmo();
	void setAmmo(unsigned ammo);
private:
	std::vector<Arrow*> arrows;
	unsigned ammo;
	unsigned nextArrowIndex;
	unsigned getNextArrowIndex();
	void setNextArrowIndex(unsigned value);
};



#endif // _BOW_H_