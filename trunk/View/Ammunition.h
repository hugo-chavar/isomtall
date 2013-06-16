#ifndef _AMMUNITION_H_
#define _AMMUNITION_H_

#ifndef ammoType_t
#define ammoType_t
enum ammoType_t {
	SWORD,
	ARROW,
	ICE_INCANTATION ,
	HAND_GRENADE,
	BOMB,
	ICE_BOMB
};
#endif

#include <string>
//#include "Entity.h"
//#include "Personaje.h"

class Ammunition {

protected:
	std::string owner;
	unsigned ammunitionType;
	float damage;
public:
	Ammunition();
	~Ammunition();
	std::string getOwner();
	void setOwner(std::string value);
	unsigned getAmmunitionType();
	void setAmmunitionType(unsigned value);
	float getDamage();
	void setDamage(float value);

};

#endif // _AMMUNITION_H_

