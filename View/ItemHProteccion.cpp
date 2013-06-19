#include "ItemHProteccion.h"
#include "HechizoProteccion.h"

#define COSTE 1.5

ItemHProteccion::ItemHProteccion(string _name,unsigned _state,std::pair <int,int> _pos,Sprite* _hiddenSprite, Sprite* sprite,bool _canReviveForHimself) : ItemView(_name,_state,_pos,_hiddenSprite,sprite,_canReviveForHimself)
{
}

ItemHProteccion::~ItemHProteccion()
{
}

void ItemHProteccion::modifyCharacter(Personaje* personaje)
{

	HechizoProteccion* hechizo;
	hechizo = new HechizoProteccion(COSTE, "Proteccion");
	personaje->setHechizo(hechizo);
}