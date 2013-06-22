#include "ItemMagicWand.h"
#include "../Model/PersonajeConstantes.h"

ItemMagicWand::ItemMagicWand(string _name,unsigned _state,std::pair <int,int> _pos,Sprite* _hiddenSprite, Sprite* sprite,bool _canReviveForHimself) : ItemView(_name,_state,_pos,_hiddenSprite,sprite,_canReviveForHimself)
{
}


ItemMagicWand::~ItemMagicWand(void)
{
}

void ItemMagicWand::modifyCharacter(Personaje* personaje)
{
	personaje->getWeapons()[WEAPON_ICE_INCANTATOR]->setAmmo(1);
}