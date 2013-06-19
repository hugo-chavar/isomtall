#ifndef _WEAPON_H_
#define _WEAPON_H_

#include <string>
#include "Daniable.h"
#include "Positionable.h"
#include "Directionable.h"
#include "Circle.h"

class Weapon: public Positionable, public Directionable {
private:
	bool active;
	//unsigned int range;
	float damage;
	float precision;
	std::string owner;
	Circle range;

public:
	Weapon();
	virtual ~Weapon();
	void initialize(bool active, unsigned range, float damage, float precision);
	//----- Getters/Setters methods -----
	bool getActive();
	int getRange();
	float getDamage();
	float getPrecision();
	std::string getOwner();
	void setOwner(std::string value);
	void setActive(bool active);
	void setRange(int range);
	void setDamage(float damage);
	void setPrecision(float precision);
	virtual unsigned getAmmo() = 0;
	//----- Functional methods  -----
	bool sameDirection(std::pair<int, int> tile);
	bool isInsideRange(std::pair<int, int> tile);
	bool needsToReposition(std::pair<int, int> tile);
	bool readyToStrike(std::pair<int, int> tile);
	std::pair<int, int> calculateRepositionToStrike(std::pair<int, int> tile);
	virtual void strike(Daniable* target) = 0;
};



#endif // _WEAPON_H_