#pragma once
#include "ItemView.h"

class ItemFactoryView
{
public:
	ItemFactoryView(void);
	~ItemFactoryView(void);
	ItemView* createItem(Sprite* itemSprite,Sprite* chestSprite,string isHidden,std::pair<int,int> pos);
};

