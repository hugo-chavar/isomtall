#include "AmmunitionPool.h"
#include "GameView.h"

AmmunitionPool::AmmunitionPool() {
}

AmmunitionPool::~AmmunitionPool() {
}

//ItemView* ItemFactoryView::createItem(Sprite* itemSprite,Sprite* hiddenSprite,string isHidden,std::pair<int,int> pos)
//{
//	ItemView* item=new ItemView(pos.first,pos.second,itemSprite,hiddenSprite,isHidden);
//	return item;
//}

//ItemView* ItemFactoryView::generateRandomItem(float porcentajeAparicion,unsigned _state,std::pair <int,int> pos,bool _canReviveForHimself)
//{
//	if(porcentajeAparicion>0)
//	{
//	int indice=static_cast <int> ((100.0/porcentajeAparicion) * NUMBERITEMS);
//	int random= rand() % indice;
//	if(random<NUMBERITEMS)
//		{
//		return this->generateItem(random,_state,pos,_canReviveForHimself);
//		}
//	}
//	return NULL;
//}
//
//ItemView* ItemFactoryView::generateItem(int itemPos,unsigned _state,std::pair <int,int> pos,bool _canReviveForHimself)
//{
//	Sprite* hiddenSprite=GameView::instance().getWorldView()->getSprite("Chest");
//	Sprite* sprite=NULL;
//	switch (itemPos){
//		case 0:
//			sprite=GameView::instance().getWorldView()->getSprite("Lamp");
//			return new Lamp("Lamp",_state,pos,hiddenSprite,sprite,_canReviveForHimself);
//		case 1:
//			sprite=GameView::instance().getWorldView()->getSprite("RunningBoots");
//			return new RunningBoots("RunningBoots",_state,pos,hiddenSprite,sprite,_canReviveForHimself);
//		case 2:
//			sprite=GameView::instance().getWorldView()->getSprite("MapItem");
//			return new MapItem("MapItem",_state,pos,hiddenSprite,sprite,_canReviveForHimself);
//		case 3:
//			sprite=GameView::instance().getWorldView()->getSprite("Heart");
//			return new Heart("Heart",_state,pos,hiddenSprite,sprite,_canReviveForHimself);
//		case 4:
//			sprite=GameView::instance().getWorldView()->getSprite("MagicBottle");
//			return new MagicBottle("MagicBottle",_state,pos,hiddenSprite,sprite,_canReviveForHimself);
//		case 5:
//			sprite=GameView::instance().getWorldView()->getSprite("Shield");
//			return new Shield("Shield",_state,pos,hiddenSprite,sprite,_canReviveForHimself);
//		}
//	return NULL;
//}