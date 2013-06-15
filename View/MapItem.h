#pragma once
#include "ItemView.h"
class MapItem : public ItemView
{
public:
	MapItem(string _name,unsigned _state,std::pair <int,int> _pos,Sprite* _hiddenSprite, Sprite* sprite,bool _canReviveForHimself);
	~MapItem(void);
	void modifyCharacter(Personaje* personaje);
};

