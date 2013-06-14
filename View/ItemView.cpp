#include "ItemView.h"


ItemView::ItemView(int tileX,int tileY,Sprite* spriteCargado,Sprite * _hiddenSprite,unsigned _state,string _name):Entity(tileX,tileY,spriteCargado)
{
	//if(state=="D")
	//{
	//this->alive=false;
	//this->hidden=false;
	//}
	//else {
	//	this->alive=true;	
	//	if(state=="H")
	//		this->hidden=true;
	//	else
	//		this->hidden=false;
	//}
	//this->state=_state;
	this->setStatus(_state);
	this->setName(_name);
	this->hiddenSprite = _hiddenSprite;
	this->setHiddenRectangle(std::make_pair(tileX, tileY),this->hiddenSprite);
}

//string ItemView::getName()
//{
//	return this->name;
//}

bool ItemView::isAlive()
{
	return (this->isHidden() || this->getStatus()==UNCOVER_ITEM);
}

bool ItemView::isHidden()
{
	return (this->getStatus()==HIDDEN_ITEM);
}

ItemView::~ItemView(void)
{

}

void ItemView::update()
{

}

void ItemView::render(Camera& camera)
{
		if(this->getStatus()==UNCOVER_ITEM)
		{
			this->renderEntitySprite(this->spriteRect,this->sprite,camera);
		}
		else if(this->isHidden()){
			this->renderEntitySprite(this->hiddenSpriteRect,this->hiddenSprite,camera);
		}
}

void ItemView::setHiddenRectangle(std::pair<int, int> pos, Sprite* sprite ) {
	hiddenSpriteRect = posicionIsometricaPorTiles(pos.first, pos.second, sprite);
	hiddenSpriteRect.w = (Uint16)(sprite->getCurrentSurface()->getSurface()->w);
	hiddenSpriteRect.h = (Uint16)(sprite->getCurrentSurface()->getSurface()->h);
}

//void ItemView::changeState()
//{
//	if(this->hidden)
//		this->hidden=false;
//	else if(this->alive)
//		this->alive=false;
//}

void ItemView::uncover()
{
	this->setStatus(UNCOVER_ITEM);
}

void ItemView::revive(unsigned _state,pair <int,int> pos)
{
	this->setRectangle(pos,this->sprite);
	this->setHiddenRectangle(pos,this->hiddenSprite);
	if(_state==REVIVE_UNCOVER_ITEM)
		this->uncover();
	else
		this->setStatus(HIDDEN_ITEM);
}

void ItemView::kill()
{
	this->setStatus(DEATH_ITEM);
}