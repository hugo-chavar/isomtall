#pragma once
#include "ItemView.h"

class ItemCrystallBall : public ItemView
{ 
public:
	ItemCrystallBall(string _name,unsigned _state,std::pair <int,int> _pos,Sprite* _hiddenSprite, Sprite* sprite,bool _canReviveForHimself);
	~ItemCrystallBall(void);
	void modifyCharacter(Personaje* personaje);
};

