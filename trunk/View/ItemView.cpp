#include "ItemView.h"


ItemView::ItemView(int tileX,int tileY,Sprite* spriteCargado,Sprite * _hiddenSprite,std::string state,string _name):Entity(tileX,tileY,spriteCargado)
{
	if(state=="D")
	{
	this->alive=false;
	this->hidden=false;
	}
	else {
		this->alive=true;	
		if(state=="H")
			this->hidden=true;
		else
			this->hidden=false;
	}
	this->name=_name;
	this->hiddenSprite = _hiddenSprite;
	this->setHiddenRectangle(std::make_pair(tileX, tileY),this->hiddenSprite);
}

string ItemView::getName()
{
	return this->name;
}

bool ItemView::isAlive()
{
	return this->alive;
}

ItemView::~ItemView(void)
{

}

void ItemView::update()
{

}

void ItemView::render(Camera& camera)
{
	if(this->alive)
	{
		if(!this->hidden)
		{
			this->renderEntitySprite(this->spriteRect,this->sprite,camera);
		}
		else{
			this->renderEntitySprite(this->hiddenSpriteRect,this->hiddenSprite,camera);
		}
	}
}

void ItemView::setHiddenRectangle(std::pair<int, int> pos, Sprite* sprite ) {
	hiddenSpriteRect = posicionIsometricaPorTiles(pos.first, pos.second, sprite);
	hiddenSpriteRect.w = (Uint16)(sprite->getCurrentSurface()->getSurface()->w);
	hiddenSpriteRect.h = (Uint16)(sprite->getCurrentSurface()->getSurface()->h);
}

void ItemView::changeState()
{
	if(this->hidden)
		this->hidden=false;
	else if(this->alive)
		this->alive=false;
}

void ItemView::uncover()
{
	this->hidden=false;
}

void ItemView::revive(char _hidden)
{
	this->alive=true;
	if(_hidden=='H')
			this->hidden=true;
		else
			this->hidden=false;
}

void ItemView::kill()
{
	this->alive=false;
}