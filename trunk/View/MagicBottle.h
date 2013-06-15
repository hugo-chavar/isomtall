#pragma once

#ifndef MAGICBOTTLE_H
#define MAGICBOTTLE_H

#include "ItemView.h"

class MagicBottle : public ItemView {

public:
	MagicBottle(string _name,unsigned _state,std::pair <int,int> _pos,Sprite* _hiddenSprite, Sprite* sprite,bool _canReviveForHimself);
	~MagicBottle(void);
	void modifyCharacter(Personaje* personaje);
};

#endif