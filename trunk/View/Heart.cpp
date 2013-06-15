#include "Heart.h"


Heart::Heart(string _name,unsigned _state,std::pair <int,int> _pos,Sprite* _hiddenSprite, Sprite* sprite,bool _canReviveForHimself) : ItemView(_name,_state,_pos,_hiddenSprite,sprite,_canReviveForHimself)
{
}


Heart::~Heart()
{
}

void Heart::modifyCharacter(Personaje* personaje)
{
	personaje->heal();
}