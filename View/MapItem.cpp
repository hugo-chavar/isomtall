#include "MapItem.h"


MapItem::MapItem(string _name,unsigned _state,std::pair <int,int> _pos,Sprite* _hiddenSprite, Sprite* sprite,bool _canReviveForHimself) : ItemView(_name,_state,_pos,_hiddenSprite,sprite,_canReviveForHimself)
{
}


MapItem::~MapItem(void)
{
}

void MapItem::modifyCharacter(Personaje* personaje)
{
	personaje->personajeModelo()->getVision()->setAllKnown(true);
}
