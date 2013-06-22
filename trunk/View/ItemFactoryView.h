#pragma once
#include "ItemView.h"

#define NUMBERITEMS 11 // Cantidad de items implementados

class ItemFactoryView
{
public:
	ItemFactoryView(void);
	~ItemFactoryView(void);
	ItemView* createItem(Sprite* itemSprite,Sprite* chestSprite,unsigned state,std::pair<int,int> pos,string name);
	ItemView* generateRandomItem(float porcentajeAparicion,unsigned _state,std::pair <int,int> pos,bool _canReviveForHimself);
	ItemView* generateItem(int itemPos,unsigned _state,std::pair <int,int> pos,bool _canReviveForHimself);
};

