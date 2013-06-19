#pragma once

#ifndef HECHIZO_H
#define HECHIZO_H

#include <string>
#include "Explosive.h"

class Hechizo: public Explosive {

public:
	Hechizo(float coste, std::string spellId);
	~Hechizo();
	virtual bool startSpell(std::string actualCaster);
	std::string getSpellId();

protected:
	float cost;
	std::string spellId;
};

#endif