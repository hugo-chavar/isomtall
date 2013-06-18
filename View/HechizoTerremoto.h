#pragma once
#include "Hechizo.h"

class HechizoTerremoto : public Hechizo
{
public:
	HechizoTerremoto(float coste, std::string spellId);
	~HechizoTerremoto(void);
	bool startSpell(std::string actualCaster);
};

