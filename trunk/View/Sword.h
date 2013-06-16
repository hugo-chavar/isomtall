#ifndef _SWORD_H_
#define _SWORD_H_

#include "Weapon.h"

class Sword: public Weapon {

public:
	Sword();
	~Sword();
	void strike(Daniable* target);
};


#endif // _SWORD_H_