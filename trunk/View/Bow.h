#ifndef _BOW_H_
#define _BOW_H_

#include "ProjectileWeapon.h"

class Bow : public ProjectileWeapon {

public:
	Bow();
	~Bow();
	void strike(Daniable* target);
};



#endif // _BOW_H_