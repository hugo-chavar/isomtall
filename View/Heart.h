#pragma once

#ifndef HEART_H
#define HEART_H

#include "ItemView.h"

class Heart : public ItemView {

public:
	Heart(string _name,unsigned _state,std::pair <int,int> _pos,Sprite* _hiddenSprite, Sprite* sprite,bool _canReviveForHimself);
	~Heart(void);
	void modifyCharacter(Personaje* personaje);
};

#endif