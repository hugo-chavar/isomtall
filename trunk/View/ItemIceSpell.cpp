#include "ItemIceSpell.h"


ItemIceSpell::ItemIceSpell(string _name,unsigned _state,std::pair <int,int> _pos,Sprite* _hiddenSprite, Sprite* sprite,bool _canReviveForHimself) : ItemView(_name,_state,_pos,_hiddenSprite,sprite,_canReviveForHimself)
{
}


ItemIceSpell::~ItemIceSpell(void)
{
}

void ItemIceSpell::modifyCharacter(Personaje* personaje)
{
	personaje->setIceSpell(true);
}