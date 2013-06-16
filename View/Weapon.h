#ifndef _WEAPON_H_
#define _WEAPON_H_

#include <string>
#include "Daniable.h"

class Weapon {
private:
	bool active;
	unsigned int range;
	float damage;
	float precision;
	std::string owner;
	void setActive(bool active);
	void setRange(unsigned int range);
	void setDamage(float damage);
	void setPrecision(float precision);
public:
	Weapon();
	virtual ~Weapon();
	void initialize(bool active, unsigned int range, float damage, float precision);
	bool getActive();
	unsigned int getRange();
	float getDamage();
	float getPrecision();
	std::string getOwner();
	void setOwner(std::string value);
	virtual void strike(Daniable* target) = 0;
};



#endif // _WEAPON_H_