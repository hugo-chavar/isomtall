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
	this->tileModel = NULL;
}

TileView::TileView(TileModel* tModel){
	this->groundEntity = NULL;
	this->otherEntity = NULL;
	this->nextTile = NULL;
	this->relatedTile = NULL;
	this->isDrawable = true;
	this->tileModel = tModel;
}

TileView::~TileView(){
	//string x = StringUtilities::unsignedToString(position.first);
	//string y = StringUtilities::unsignedToString(position.second);
	//Logger::instance().log("Borrado tile "+ x+ ", "+y+" listo");
	if (otherEntity)
		delete otherEntity;
	if (groundEntity)
		delete groundEntity;
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

//void TileView::setPosition(KeyPair p){
//	this->position = p;
//}

KeyPair TileView::getPosition(){
	return this->tileModel->getPosition();
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

TileModel* TileView::getTileModel(){
	return this->tileModel;
}

bool TileView::drawable(){
	return this->tileModel->drawable();
}


bool TileView::EOL(){
	return this->tileModel->EOL();
}

string TileView::getGroundEntityName(){
	return this->tileModel->getGroundEntity()->name();
}

bool TileView::hasOtherEntity(){
	if (this->tileModel->getOtherEntity())
		return true;
	return false;
}

string TileView::getOtherEntityName(){
	//a este metodo usarlo con validaciones hasOtherEntity()
	return this->tileModel->getOtherEntity()->name();
}

void TileView::createGround(Sprite* sprite){
	groundEntity = new Entity(this->tileModel->getPosition().first, this->tileModel->getPosition().second, sprite);
}

void TileView::createOtherEntity(Sprite* sprite){
	otherEntity = new Entity(this->tileModel->getPosition().first, this->tileModel->getPosition().second, sprite);
}

void TileView::render(Camera& camera){
	this->getGroundEntity()->render(camera);

	if (this->drawable()){
		TileView* tileaux = this->getRelatedTile();
		if (tileaux)
			tileaux->getOtherEntity()->render(camera);
		else 
			if (this->hasOtherEntity())
				this->getOtherEntity()->render(camera);
	}
}