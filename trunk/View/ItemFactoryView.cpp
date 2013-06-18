#include "ItemFactoryView.h"
#include "GameView.h"
#include "Lamp.h"
#include "MapItem.h"
#include "RunningBoots.h"
#include "Heart.h"
#include "MagicBottle.h"
#include "Shield.h"
#include "ItemHProteccion.h"
#include "ItemTerremoto.h"
#include "ItemFlecha.h"

ItemFactoryView::ItemFactoryView(void)
{
}


ItemFactoryView::~ItemFactoryView(void)
{
}

ItemView* ItemFactoryView::createItem(Sprite* itemSprite,Sprite* hiddenSprite,unsigned state,std::pair<int,int> pos,string name)
{
	ItemView* item=new ItemView(pos.first,pos.second,itemSprite,hiddenSprite,state,name);
	return item;
}

ItemView* ItemFactoryView::generateRandomItem(float porcentajeAparicion,unsigned _state,std::pair <int,int> pos,bool _canReviveForHimself)
{
	if(porcentajeAparicion>0)
	{
	int indice=static_cast <int> ((100.0/porcentajeAparicion) * NUMBERITEMS);
	int random= rand() % indice;
	if(random<NUMBERITEMS)
		{
		return this->generateItem(random,_state,pos,_canReviveForHimself);
		}
	}
	return NULL;
}

ItemView* ItemFactoryView::generateItem(int itemPos,unsigned _state,std::pair <int,int> pos,bool _canReviveForHimself)
{
	Sprite* hiddenSprite=GameView::instance().getWorldView()->getSpriteWithName("Chest");
	Sprite* sprite=NULL;
	switch (itemPos){
		case 0:
			sprite=GameView::instance().getWorldView()->getSpriteWithName("Lamp");
			if (sprite)
				return new Lamp("Lamp",_state,pos,hiddenSprite,sprite,_canReviveForHimself);
		case 1:
			sprite=GameView::instance().getWorldView()->getSpriteWithName("RunningBoots");
			if (sprite)
				return new RunningBoots("RunningBoots",_state,pos,hiddenSprite,sprite,_canReviveForHimself);
		case 2:
			sprite=GameView::instance().getWorldView()->getSpriteWithName("MapItem");
			if (sprite)
				return new MapItem("MapItem",_state,pos,hiddenSprite,sprite,_canReviveForHimself);
		case 3:
			sprite=GameView::instance().getWorldView()->getSpriteWithName("Heart");
			if (sprite)
				return new Heart("Heart",_state,pos,hiddenSprite,sprite,_canReviveForHimself);
		case 4:
			sprite=GameView::instance().getWorldView()->getSpriteWithName("MagicBottle");
			if (sprite)
				return new MagicBottle("MagicBottle",_state,pos,hiddenSprite,sprite,_canReviveForHimself);
		case 5:
			sprite=GameView::instance().getWorldView()->getSpriteWithName("Shield");
			if (sprite)
				return new Shield("Shield",_state,pos,hiddenSprite,sprite,_canReviveForHimself);
		case 6:
			sprite=GameView::instance().getWorldView()->getSpriteWithName("ItemHProteccion");
			if (sprite)
				return new ItemHProteccion("ItemHProteccion",_state,pos,hiddenSprite,sprite,_canReviveForHimself);
		case 7:
			sprite=GameView::instance().getWorldView()->getSpriteWithName("ItemTerremoto");
			if (sprite)
				return new ItemTerremoto("ItemTerremoto",_state,pos,hiddenSprite,sprite,_canReviveForHimself);
		case 8:
			sprite=GameView::instance().getWorldView()->getSpriteWithName("ItemFlecha");
			if (sprite)
				return new ItemFlecha("ItemFlecha",_state,pos,hiddenSprite,sprite,_canReviveForHimself);
		}
	return NULL;
}