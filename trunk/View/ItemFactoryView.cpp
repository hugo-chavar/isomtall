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
#include "ItemCrystallBall.h"
#include "ItemIceSpell.h"
#include "ItemMagicWand.h"

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
	//int random= rand() % indice;
	int random=(rand() * ( 1.0 / ( RAND_MAX + 1.0 ) ))*indice;
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
	hiddenSprite->initWhiteShadows();
	Sprite* sprite=NULL;
	switch (itemPos){
		case 0:
			sprite=GameView::instance().getWorldView()->getSpriteWithName("Lamp");
			if (sprite) {
				sprite->initWhiteShadows();
				return new Lamp("Lamp",_state,pos,hiddenSprite,sprite,_canReviveForHimself);
			}
		case 1:
			sprite=GameView::instance().getWorldView()->getSpriteWithName("RunningBoots");
			if (sprite) {
				sprite->initWhiteShadows();
				return new RunningBoots("RunningBoots",_state,pos,hiddenSprite,sprite,_canReviveForHimself);
			}
		case 2:
			sprite=GameView::instance().getWorldView()->getSpriteWithName("MapItem");
			if (sprite) {
				sprite->initWhiteShadows();
				return new MapItem("MapItem",_state,pos,hiddenSprite,sprite,_canReviveForHimself);
			}
		case 3:
			sprite=GameView::instance().getWorldView()->getSpriteWithName("Heart");
			if (sprite) {
				sprite->initWhiteShadows();
				return new Heart("Heart",_state,pos,hiddenSprite,sprite,_canReviveForHimself);
			}
		case 4:
			sprite=GameView::instance().getWorldView()->getSpriteWithName("MagicBottle");
			if (sprite) {
				sprite->initWhiteShadows();
				return new MagicBottle("MagicBottle",_state,pos,hiddenSprite,sprite,_canReviveForHimself);
			}
		case 5:
			sprite=GameView::instance().getWorldView()->getSpriteWithName("Shield");
			if (sprite) {
				sprite->initWhiteShadows();
				return new Shield("Shield",_state,pos,hiddenSprite,sprite,_canReviveForHimself);
			}
		case 6:
			sprite=GameView::instance().getWorldView()->getSpriteWithName("ItemHProteccion");
			if (sprite) {
				sprite->initWhiteShadows();
				return new ItemHProteccion("ItemHProteccion",_state,pos,hiddenSprite,sprite,_canReviveForHimself);
			}
		case 7:
			sprite=GameView::instance().getWorldView()->getSpriteWithName("ItemTerremoto");
			if (sprite) {
				sprite->initWhiteShadows();
				return new ItemTerremoto("ItemTerremoto",_state,pos,hiddenSprite,sprite,_canReviveForHimself);
			}
		case 8:
			sprite=GameView::instance().getWorldView()->getSpriteWithName("ItemFlecha");
			if (sprite) {
				sprite->initWhiteShadows();
				return new ItemFlecha("ItemFlecha",_state,pos,hiddenSprite,sprite,_canReviveForHimself);
			}
		case 9:
			sprite=GameView::instance().getWorldView()->getSpriteWithName("crystalBall");
			if (sprite) {
				sprite->initWhiteShadows();
				return new ItemCrystallBall("crystalBall",_state,pos,hiddenSprite,sprite,_canReviveForHimself);
			}
		case 10:
			sprite=GameView::instance().getWorldView()->getSpriteWithName("ItemIceSpell");
			if (sprite) {
				sprite->initWhiteShadows();
				return new ItemIceSpell("ItemIceSpell",_state,pos,hiddenSprite,sprite,_canReviveForHimself);
			}
		case 11:
			sprite=GameView::instance().getWorldView()->getSpriteWithName("ItemMagicWand");
			if (sprite) {
				sprite->initWhiteShadows();
				return new ItemMagicWand("ItemMagicWand",_state,pos,hiddenSprite,sprite,_canReviveForHimself);
			}
		}
	return NULL;
}