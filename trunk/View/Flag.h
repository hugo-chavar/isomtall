#pragma once
#ifndef __FLAG_H__
#define __FLAG_H__

#include "Daniable.h"
#include "Entity.h"
#include "AnimatedEntity.h"


class Flag : public Daniable, public Entity {

public:
	Flag();
	~Flag();
	string getName();
	void destroy();

private:
	AnimatedEntity* entity;

};


#endif