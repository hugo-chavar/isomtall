#pragma once

#ifndef HECHIZOPROTECCION_H
#define HECHIZOPROTECCION_H

#include "Hechizo.h"

class HechizoProteccion : public Hechizo {

public:
	HechizoProteccion(float coste, std::string spellId);
	~HechizoProteccion();
	bool startSpell(std::string actualCaster);

};


#endif