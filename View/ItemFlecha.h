#pragma once
#include "ItemView.h"

class ItemFlecha:public ItemView
{
public:
	ItemFlecha(string _name,unsigned _state,std::pair <int,int> _pos,Sprite* _hiddenSprite, Sprite* sprite,bool _canReviveForHimself);
	~ItemFlecha(void);
	void modifyCharacter(Personaje* personaje);
};

