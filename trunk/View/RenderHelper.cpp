#include "RenderHelper.h"
#include "GameView.h"

using namespace view;

RenderHelper::RenderHelper() {
	this->clear();
}

RenderHelper::~RenderHelper() {
}

void RenderHelper::clear() {
	limits.clear();
	this->emptyStartLevel = -1;
	this->emptyEndLevel = -1;
	coin = false;
}

void RenderHelper::startRenderingEntities() {
	this->currentLevel = this->startLevel -1;
	levelIterator = limits.begin();
}

void RenderHelper::setStartLevel(int value) {
	this->startLevel = value;
}

void RenderHelper::setEndLevel(int value) {
	this->endLevel = value;
	this->currentLevel = value;
}

void RenderHelper::setEmptyLevel() {
	if (this->currentLevel > this->emptyEndLevel) {
		this->emptyEndLevel = this->currentLevel;
		if (this->emptyStartLevel == -1) {
			this->emptyStartLevel = this->currentLevel;
		}
	} else {
		this->emptyStartLevel = this->currentLevel;
	}
	this->currentLevel--;
}

bool RenderHelper::incomplete() {
	return (this->startLevel <= this->currentLevel);
}

bool RenderHelper::hasLevelsToRender() {
	return (this->currentLevel < this->endLevel);
}

bool RenderHelper::currentIsEmpty() {
	return ((this->currentLevel >= this->emptyStartLevel)&&(this->currentLevel <= this->emptyEndLevel));
}

bool RenderHelper::flip() {
	coin = !coin;
	return coin;
}

pair<int,int> RenderHelper::maxLevel(pair<int,int> pos1, pair<int,int> pos2) {
	if ((pos1.first + pos1.second) > (pos2.first + pos2.second) )
		return pos1;
	return pos2;
}

bool RenderHelper::belongsToLevel(pair<int,int> currentPos) { 
	return (this->currentLevel == (currentPos.first + currentPos.second) );
}

bool RenderHelper::shouldRenderThis(pair<int,int> currentPos, pair<int,int> previousPos) {
	pair<int,int> aux = this->maxLevel(currentPos, previousPos);
	if (this->belongsToLevel(aux))
		return (GameView::instance().insidePlayerVision(currentPos) || GameView::instance().insidePlayerVision(previousPos));
	return false;
}

void RenderHelper::addLevel(TileView* first ,TileView* last) {
	limits.push_front(std::make_pair(first,last->getNextTile()));
	this->currentLevel--;
}

void RenderHelper::renderNextLevel(Camera& camera) {
	this->currentLevel++;
	if (this->currentIsEmpty())
		return;
	TileView* tile;
	tile = (*levelIterator).first;
	bool isInsidePlayerVision = GameView::instance().insidePlayerVision(tile->getPosition());
	while ((tile) && (tile != (*levelIterator).second) ) {
		if ( isInsidePlayerVision  || (GameView::instance().isKnownByPlayer(tile->getPosition()))) {
			tile->renderEntity(camera,isInsidePlayerVision);
			//if (!isInsidePlayerVision)
			//	tile->renderFog(camera);
		} //else if (Game::instance().isKnownByPlayer(tile->getPosition())){
			//tile->renderEntity(camera);
		//}
		tile = tile->getNextTile();
		if (tile)
			isInsidePlayerVision = GameView::instance().insidePlayerVision(tile->getPosition());
	}
	levelIterator++;

}

void RenderHelper::renderGround(Camera& camera) {
	TileView* tile;
	levelIterator = limits.begin();
	for (; levelIterator != limits.end(); levelIterator++){
		tile = (*levelIterator).first;
		while (tile != (*levelIterator).second ){
			if (GameView::instance().insidePlayerVision(tile->getPosition())){
				tile->setFogged(false);
				tile->renderGround(camera);
			} else if (GameView::instance().isKnownByPlayer(tile->getPosition())){
				//aplico niebla
				tile->setFogged(true);
				tile->renderGround(camera);
			}
			tile = tile->getNextTile();
		}
	}
}