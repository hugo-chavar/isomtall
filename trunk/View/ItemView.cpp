#include "ItemView.h"
#include "GameView.h"
#define VARIABLE_REGENERATION_TIME 60000
#define CONST_REGENERATION_TIME 30000

ItemView::ItemView(int tileX,int tileY,Sprite* spriteCargado,Sprite * _hiddenSprite,unsigned _state,string _name):Entity(tileX,tileY,spriteCargado)
{

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

void ItemView::updateSinglePlayer()
{
if(GameView::instance().isSinglePlayerGame())
	if (this->canReviveForHimself)
	{
		if(this->getStatus()==DEATH_ITEM)
			{
				int delta=static_cast <int>(Game::instance().getTimer()->getDeltaTime());
				if(regenerationTime-delta>0)
					this->regenerationTime-=delta;
				else
					{
						this->regenerationTime=0;
						if(GameView::instance().getMyPersonaje()->getPosicionActualEnTiles()!=this->getPosition())
						{
							GameView::instance().getWorldView()->getTileAt(this->getPosition())->setOtherEntity(this);
							this->revive(HIDDEN_ITEM,this->getPosition());//Aca tendria que meter logica para que cambie de lugar el item
						}
						else
							regenerationTime=CONST_REGENERATION_TIME+rand()%VARIABLE_REGENERATION_TIME;
					}
			}
	}
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

void ItemView::reviveSinglePlayer(unsigned _state,std::pair <int,int> _pos)
{
	this->setPosition(_pos);
	this->setStatus(_state);
	this->setRectangle(_pos,this->sprite);
	this->setHiddenRectangle(_pos,this->hiddenSprite);
	if(_state==REVIVE_UNCOVER_ITEM)
	{
		this->setStatus(UNCOVER_ITEM);
	}
	else{
		this->setStatus(HIDDEN_ITEM);
		Game::instance().world()->getTileAt(this->getPosition())->setHasHiddenItem(true);
	}
}


void ItemView::kill()
{
	this->setStatus(DEATH_ITEM);
}

void ItemView::killSinglePlayer()
{
	//this->state=DEATH_ITEM;
	this->setStatus(DEATH_ITEM);
	//EMPEZAR A CONTAR EL TIEMPO
	GameView::instance().getWorldView()->getTileAt(this->getPosition())->setOtherEntity(NULL);
	regenerationTime=CONST_REGENERATION_TIME+rand()%VARIABLE_REGENERATION_TIME;
}


void ItemView::modifyCharacter(Personaje* )
{
	//MetodoAbstracto
}

//Single Player
ItemView::ItemView(string _name,unsigned _state,std::pair <int,int> _pos,Sprite* _hiddenSprite, Sprite* sprite,bool _canReviveForHimself):Entity(_pos.first,_pos.second,sprite)
{
	this->name=_name;
	this->setPosition(_pos);
	this->setStatus(_state);
	this->canReviveForHimself=_canReviveForHimself;
	this->hiddenSprite = _hiddenSprite;
	this->setHiddenRectangle(_pos,this->hiddenSprite);
}
std::string ItemView::getName()
{
	return this->name;
}
void ItemView::recibirDano(float dano)
{
	if(dano>0 && this->isHidden())
	{
		this->uncover();
		GameView::instance().getWorldView()->getTileAt(this->getPosition())->setItemUncover();
	}
}

bool ItemView::isItem()
{
	return true;
}

bool ItemView::getCanReviveForHimself()
{
	return this->canReviveForHimself;
}
//Agrego Andy