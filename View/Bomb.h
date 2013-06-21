#ifndef _BOMB_H_
#define _BOMB_H_

#include "Movable.h"
#include "Daniable.h"
#include "Explosive.h"
#include "Serializable.h"

class Bomb: public Entity, public Explosive, public Positionable, public Serializable {

private:
	SpriteAnimado * explosionSprite;

public:
	Bomb();
	~Bomb();
	bool isAlive();
	void update();
	void startCountDown(float seconds);
	void render(Camera& camera);
	void deserialize(std::string in);
	std::string serialize();
};


#endif // _BOMB_H_