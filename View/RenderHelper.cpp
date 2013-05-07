#include "RenderHelper.h"

using namespace view;

RenderHelper::RenderHelper(){
	this->clear();
}

RenderHelper::~RenderHelper(){
}

void RenderHelper::clear(){
	limits.clear();
	this->emptyStartLevel = -1;
	this->emptyEndLevel = -1;
	coin = false;
}

void RenderHelper::startRendering(){
	this->currentLevel = this->startLevel -1;
	levelIterator = limits.begin();
}

void RenderHelper::setStartLevel(int value){
	this->startLevel = value;
}

void RenderHelper::setEndLevel(int value){
	this->endLevel = value;
	this->currentLevel = value;
}

void RenderHelper::setEmptyLevel(){
	if (this->currentLevel > this->emptyEndLevel)
		this->emptyEndLevel = this->currentLevel;
	else
		this->emptyStartLevel = this->currentLevel;
	this->currentLevel--;
}

bool RenderHelper::incomplete(){
	return (this->startLevel <= this->currentLevel);
}

bool RenderHelper::hasLevelsToRender(){
	return (this->currentLevel < this->endLevel);
}

bool RenderHelper::currentIsEmpty(){
	return ((this->currentLevel >= this->emptyStartLevel)&&(this->currentLevel <= this->emptyEndLevel));
}

bool RenderHelper::flip(){
	coin = !coin;
	return coin;
}

int RenderHelper::maxLevel(pair<int,int> pos1, pair<int,int> pos2){
	if ((pos1.first + pos1.second) > (pos2.first + pos2.second) )
		return (pos1.first + pos1.second);
	return (pos2.first + pos2.second);
}

bool RenderHelper::belongsToLevel(pair<int,int> currentPos, pair<int,int> previousPos){
	return (this->currentLevel == this->maxLevel(currentPos, previousPos) );
}

void RenderHelper::addLevel(TileView* first ,TileView* last){
	limits.push_front(std::make_pair(first,last->getNextTile()));
	this->currentLevel--;
}

void RenderHelper::renderNextLevel(Camera& camera){
	this->currentLevel++;
	if (this->currentIsEmpty())
		return;
	TileView* tile;
	tile = (*levelIterator).first;
	while (tile != (*levelIterator).second ){
		tile->render(camera);
		tile = tile->getNextTile();
	}
	levelIterator++;

}