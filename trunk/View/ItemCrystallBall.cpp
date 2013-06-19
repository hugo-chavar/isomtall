#include "ItemCrystallBall.h"


ItemCrystallBall::ItemCrystallBall(string _name,unsigned _state,std::pair <int,int> _pos,Sprite* _hiddenSprite, Sprite* sprite,bool _canReviveForHimself) : ItemView(_name,_state,_pos,_hiddenSprite,sprite,_canReviveForHimself)
{
}


ItemCrystallBall::~ItemCrystallBall(void)
{
}

void ItemCrystallBall::modifyCharacter(Personaje* personaje)
{

}