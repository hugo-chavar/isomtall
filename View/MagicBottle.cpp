#include "MagicBottle.h"


MagicBottle::MagicBottle(string _name,unsigned _state,std::pair <int,int> _pos,Sprite* _hiddenSprite, Sprite* sprite,bool _canReviveForHimself) : ItemView(_name,_state,_pos,_hiddenSprite,sprite,_canReviveForHimself)
{
}


MagicBottle::~MagicBottle()
{
}

void MagicBottle::modifyCharacter(Personaje* personaje)
{
	personaje->rechargeMagic();
}