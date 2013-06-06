#include "ItemView.h"


ItemView::ItemView(int tileX,int tileY,Sprite* spriteCargado,Sprite * _hiddenSprite,std::string _hidden):Entity(tileX,tileY,spriteCargado)
{
	this->alive=true;
	if(_hidden=="H")
		this->hidden=true;
	else
		this->hidden=false;
	this->hiddenSprite = _hiddenSprite;
	this->setHiddenRectangle(std::make_pair(tileX, tileY),this->hiddenSprite);
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