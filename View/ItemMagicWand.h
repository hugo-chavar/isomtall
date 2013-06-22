#pragma once

#include "ItemView.h"

class ItemMagicWand : public ItemView
{
public:
	ItemMagicWand(string _name,unsigned _state,std::pair <int,int> _pos,Sprite* _hiddenSprite, Sprite* sprite,bool _canReviveForHimself);
	~ItemMagicWand(void);
	void modifyCharacter(Personaje* personaje);
};

