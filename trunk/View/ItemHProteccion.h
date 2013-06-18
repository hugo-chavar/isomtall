#pragma once

#ifndef ITEMHPROTECCION_H
#define ITEMHPROTECCION_H

#include "ItemView.h"

class ItemHProteccion : public ItemView {

public:
	ItemHProteccion(string _name,unsigned _state,std::pair <int,int> _pos,Sprite* _hiddenSprite, Sprite* sprite,bool _canReviveForHimself);
	~ItemHProteccion(void);
	void modifyCharacter(Personaje* personaje);
};

#endif