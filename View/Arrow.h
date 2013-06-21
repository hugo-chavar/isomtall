#ifndef _ARROW_H_
#define _ARROW_H_

#include "ImpactAmmo.h"
#include "Daniable.h"

class Arrow: public ImpactAmmo {

protected:
public:
	Arrow();
	~Arrow();
	void impact(Daniable* daniable);
	/*void deserialize(std::string in);
	std::string serialize();*/
};

#endif // _ARROW_H_

