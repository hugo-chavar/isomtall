#ifndef _EXPLOSIVE_H_
#define _EXPLOSIVE_H_

#include <utility>
#include "Ammunition.h"
#include "Circle.h"
#include "Positionable.h"
#include "GameDependent.h"

class Explosive: public Ammunition{

protected:
	Circle range;
	//bool exploded;

public:
	Explosive();
	~Explosive();
	void setRange(int value);
	void setCenter(std::pair<int, int> value);
	//virtual void update() = 0;
	void activate();
	//virtual void impact(Daniable* ) = 0;
};


#endif // _EXPLOSIVE_H_

