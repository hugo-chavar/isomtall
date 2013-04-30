#include "TileModel.h"
#include "Logger.h"
#include "stringUtilities.h"

using namespace common;


TileModel::TileModel(){
	this->groundEntity = NULL;
	this->otherEntity = NULL;
	this->nextTile = NULL;
}

TileModel::~TileModel(){
	//string x = StringUtilities::unsignedToString(position.first);
	//string y = StringUtilities::unsignedToString(position.second);
	//Logger::instance().log("Borrado tile "+ x+ ", "+y+" listo");
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

void TileModel::setNextTile(TileModel* t){
	this->nextTile = t;
}

TileModel* TileModel::getNextTile(){
	return this->nextTile;
}

void TileModel::addEntity(EntityObject * e){
	if ( e->isGround() ){
		if (!this->groundEntity){
			this->setGroundEntity(e);
		} else {
			string x = StringUtilities::unsignedToString(position.first);
			string y = StringUtilities::unsignedToString(position.second);
			Logger::instance().log("Game warning: pos "+ x+ ", "+y+" already has ground, ignoring '"+e->name()+"'");
		}
	} else { //no es piso
		if (!this->otherEntity){
			this->setOtherEntity(e);
		} else {
			string x = StringUtilities::unsignedToString(position.first);
			string y = StringUtilities::unsignedToString(position.second);
			Logger::instance().log("Game warning: pos "+ x+ ", "+y+" already has a entity, ignoring '"+e->name()+"'");
		}
	}
}