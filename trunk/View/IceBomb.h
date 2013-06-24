#pragma once

#include "Movable.h"
#include "Daniable.h"
#include "Explosive.h"
#include "Serializable.h"

class IceBomb: public Entity, public Explosive, public Positionable, public Serializable {

private:
	SpriteAnimado * explosionSprite;

public:
	IceBomb();
	~IceBomb();
	bool isAlive();
	void update();
	void startCountDown(float seconds);
	void render(Camera& camera);
	void deserialize(std::string in);
	std::string serialize();
};

