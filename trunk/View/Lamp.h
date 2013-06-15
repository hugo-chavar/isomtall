#pragma once
#include "ItemView.h"
class Lamp : public ItemView
{
private:
	int incremento;
public:
	Lamp(string _name,unsigned _state,std::pair <int,int> _pos,Sprite* _hiddenSprite, Sprite* sprite,bool _canReviveForHimself);
	~Lamp(void);
	void modifyCharacter(Personaje* personaje);
};

