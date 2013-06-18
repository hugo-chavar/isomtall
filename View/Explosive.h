#ifndef _EXPLOSIVE_H_
#define _EXPLOSIVE_H_

#include "Ammunition.h"
#include "Circle.h"

class Explosive: public Ammunition {

protected:

public:
	Explosive();
	~Explosive();
	void update();
	//virtual void impact(Daniable* ) = 0;
};


#endif // _EXPLOSIVE_H_

