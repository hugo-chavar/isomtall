#include "ItemFactoryView.h"

ItemFactoryView::ItemFactoryView(void)
{
}


ItemFactoryView::~ItemFactoryView(void)
{
}

ItemView* ItemFactoryView::createItem(Sprite* itemSprite,Sprite* hiddenSprite,string state,std::pair<int,int> pos)
{
	ItemView* item=new ItemView(pos.first,pos.second,itemSprite,hiddenSprite,state);
	return item;
}