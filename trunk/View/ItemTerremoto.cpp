#include "ItemTerremoto.h"
#include "HechizoTerremoto.h"

#define COSTE 30

ItemTerremoto::ItemTerremoto(string _name,unsigned _state,std::pair <int,int> _pos,Sprite* _hiddenSprite, Sprite* sprite,bool _canReviveForHimself) : ItemView(_name,_state,_pos,_hiddenSprite,sprite,_canReviveForHimself)
{
}


ItemTerremoto::~ItemTerremoto(void)
{
}

void ItemTerremoto::modifyCharacter(Personaje* personaje)
{
	HechizoTerremoto* hechizo = new HechizoTerremoto(COSTE, "Terremoto");
	personaje->setHechizo(hechizo);
}