#ifndef _AMMUNITION_H_
#define _AMMUNITION_H_

#ifndef ammoType_t
#define ammoType_t
enum ammoType_t {
	SWORD,
	IMPACT_AMMO,
	HAND_GRENADE,
	BOMB,
	ICE_BOMB
};
#endif

#include <string>


class Ammunition {

private:
	// ----- Static class members ----
	static unsigned ammo_id_counter;

protected:
	// ----- Non-static class members ----
	std::string owner;
	unsigned ammunitionType;
	float damage;
	std::string ammo_id;
	bool available;
public:
	
	Ammunition();
	~Ammunition();
	std::string getOwner();
	void setOwner(std::string value);
	std::string getAmmoId();
	void setAmmoID(std::string value);
	unsigned getAmmunitionType();
	void setAmmunitionType(unsigned value);
	float getDamage();
	void setDamage(float value);
	bool isAvailable();
	void setAvailable(bool value);
	virtual bool needsUpdates();
};

#endif // _AMMUNITION_H_

