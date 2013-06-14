#ifndef _IMPACTAMMO_H_
#define _IMPACTAMMO_H_

#include "Movable.h"
#include "Ammunition.h"

class ImpactAmmo: public Ammunition, public Movable {

protected:
	//std::string owner;
public:
	ImpactAmmo();
	~ImpactAmmo();
	//std::string getOwner();
	//void setOwner(std::string value);

};


#endif // _AMMUNITION_H_

