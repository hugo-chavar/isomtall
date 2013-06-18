#pragma once
#include "ItemView.h"

class ItemTerremoto : public ItemView{

public:
	ItemTerremoto(string _name,unsigned _state,std::pair <int,int> _pos,Sprite* _hiddenSprite, Sprite* sprite,bool _canReviveForHimself);
	~ItemTerremoto(void);
	void modifyCharacter(Personaje* personaje);
};

