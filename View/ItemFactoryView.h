#pragma once
#include "ItemView.h"

class ItemFactoryView
{
public:
	ItemFactoryView(void);
	~ItemFactoryView(void);
	ItemView* createItem(Sprite* itemSprite,Sprite* chestSprite,unsigned state,std::pair<int,int> pos,string name);
};

