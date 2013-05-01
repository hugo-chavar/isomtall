#include "TileView.h"
#include "Logger.h"
#include "stringUtilities.h"

using namespace common;


TileView::TileView(){
	this->groundEntity = NULL;
	this->otherEntity = NULL;
	this->nextTile = NULL;
	this->relatedTile = NULL;
	this->isDrawable = true;
}

TileView::~TileView(){
	//string x = StringUtilities::unsignedToString(position.first);
	//string y = StringUtilities::unsignedToString(position.second);
	//Logger::instance().log("Borrado tile "+ x+ ", "+y+" listo");
}

Entity * TileView::getGroundEntity(){
	return this->groundEntity;
}

Entity * TileView::getOtherEntity(){
	return this->otherEntity;
}

void TileView::setGroundEntity(Entity * e){
	this->groundEntity = e;
}

void TileView::setOtherEntity(Entity * e){
	this->otherEntity = e;
}

void TileView::setPosition(KeyPair p){
	this->position = p;
}

KeyPair TileView::getPosition(){
	return this->position;
}

void TileView::setNextTile(TileView* t){
	this->nextTile = t;
}

TileView* TileView::getNextTile(){
	return this->nextTile;
}

void TileView::setRelatedTile(TileView* t){
	this->relatedTile = t;
}

TileView* TileView::getRelatedTile(){
	return this->relatedTile;
}

void TileView::setUndrawable(){
	this->isDrawable = false;
}


bool TileView::drawable(){
	return this->isDrawable;
}

//void TileView::cleanUp() {
//	SDL_FreeSurface(this->sdlSurface);
//}

//unsigned int TileView::getSpeedPenalty() {
//	return this->speedPenalty;
//}