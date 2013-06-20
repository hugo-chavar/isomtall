#ifndef _ICE_INCANTATION_H_
#define _ICE_INCANTATION_H_

#include "ImpactAmmo.h"
#include "Daniable.h"

class IceIncantation: public ImpactAmmo {

protected:
public:
	IceIncantation();
	~IceIncantation();
	void impact(Daniable* daniable);
};

#endif // _ICE_INCANTATION_H_

