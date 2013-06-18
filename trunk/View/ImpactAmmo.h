#ifndef _IMPACTAMMO_H_
#define _IMPACTAMMO_H_

#include "Movable.h"
#include "Ammunition.h"
#include "Daniable.h"

class ImpactAmmo: public Ammunition, public Movable {

protected:
public:
	ImpactAmmo();
	~ImpactAmmo();
	void verify();
	virtual void impact(Daniable* ) = 0;
};


#endif // _AMMUNITION_H_

