#ifndef _IMPACTAMMO_H_
#define _IMPACTAMMO_H_

#include "Movable.h"
#include "Ammunition.h"
#include "Daniable.h"
#include "Serializable.h"

class ImpactAmmo: public Ammunition, public Movable, public Serializable {

protected:
public:
	ImpactAmmo();
	~ImpactAmmo();
	void verify();
	virtual void impact(Daniable* ) = 0;
	void deserialize(std::string in);
	std::string serialize();
};


#endif // _AMMUNITION_H_

