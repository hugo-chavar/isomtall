#pragma once
#include "ItemView.h"
class Shield:public ItemView
{
private:
	float resistance;
	float absortion;
public:
	Shield(string _name,unsigned _state,std::pair <int,int> _pos,Sprite* _hiddenSprite, Sprite* sprite,bool _canReviveForHimself);
	~Shield(void);
	void modifyCharacter(Personaje* personaje);
};

