#include "TileModel.h"
#include "Logger.h"
#include "StringUtilities.h"

using namespace common;


TileModel::TileModel(){
	this->groundEntity = NULL;
	this->otherEntity = NULL;
	this->nextTile = NULL;
	this->relatedTile = NULL;
	this->isDrawable = true;
	this->endOfLevel = false;
}

TileModel::~TileModel(){
}

EntityObject * TileModel::getGroundEntity(){
	return this->groundEntity;
}

EntityObject * TileModel::getOtherEntity(){
	return this->otherEntity;
}

void TileModel::setGroundEntity(EntityObject * e){
	this->groundEntity = e;
}

void TileModel::setOtherEntity(EntityObject * e){
	this->otherEntity = e;
}

void TileModel::setPosition(KeyPair p){
	this->position = p;
}

KeyPair TileModel::getPosition(){
	return this->position;
}

void TileModel::setNextTile(TileModel* t){
	this->nextTile = t;
}

TileModel* TileModel::getNextTile(){
	return this->nextTile;
}

void TileModel::setRelatedTile(TileModel* t){
	this->relatedTile = t;
}

TileModel* TileModel::getRelatedTile(){
	return this->relatedTile;
}

void TileModel::setUndrawable(){
	this->isDrawable = false;
}

void TileModel::setDrawable(){
	this->isDrawable = true;
}

bool TileModel::drawable(){
	return this->isDrawable;
}

bool TileModel::EOL(){
	return this->endOfLevel;
}

void TileModel::setEOL(){
	this->endOfLevel = true;
}
void TileModel::addEntity(EntityObject * e){
	if ( e->isGround() ){
		if (!this->groundEntity){
			this->setGroundEntity(e);
		} else {
			string x = stringUtilities::unsignedToString(position.first);
			string y = stringUtilities::unsignedToString(position.second);
			Logger::instance().log("Game warning: pos "+ x+ ", "+y+" already has ground, ignoring '"+e->name()+"'");
		}
	} else { //no es piso
		if (!this->otherEntity){
			this->setOtherEntity(e);
		} else {
			string x = stringUtilities::unsignedToString(position.first);
			string y = stringUtilities::unsignedToString(position.second);
			Logger::instance().log("Game warning: pos "+ x+ ", "+y+" already has a entity, ignoring '"+e->name()+"'");
		}
	}
}
