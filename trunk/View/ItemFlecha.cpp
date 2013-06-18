#include "ItemFlecha.h"
#include "../Model/PersonajeConstantes.h"
#include "Bow.h"

ItemFlecha::ItemFlecha(string _name,unsigned _state,std::pair <int,int> _pos,Sprite* _hiddenSprite, Sprite* sprite,bool _canReviveForHimself) : ItemView(_name,_state,_pos,_hiddenSprite,sprite,_canReviveForHimself)
{
}


ItemFlecha::~ItemFlecha(void)
{
}

void ItemFlecha::modifyCharacter(Personaje* personaje)
{
	((Bow*)personaje->getWeapons()[WEAPON_BOW])->setAmmo(10);
}
