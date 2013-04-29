#include "TileModel.h"
#include "Logger.h"
#include "stringUtilities.h"

using namespace common;


TileModel::TileModel(){
	this->groundEntity = NULL;
	this->otherEntity = NULL;
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

void TileModel::setPosition(unsigned x, unsigned y){
	this->posx = x;
	this->posy = y;
}

void TileModel::addEntity(EntityObject * e){
	if ( e->isGround() ){
		if (!this->groundEntity){
			this->setGroundEntity(e);
		} else {
			string x = StringUtilities::unsignedToString(posx);
			string y = StringUtilities::unsignedToString(posy);
			Logger::instance().log("Game warning: pos "+ x+ ", "+y+" already has ground, ignoring '"+e->name()+"'");
		}
	} else { //no es piso
		if (!this->otherEntity){
			this->setOtherEntity(e);
		} else {
			string x = StringUtilities::unsignedToString(posx);
			string y = StringUtilities::unsignedToString(posy);
			Logger::instance().log("Game warning: pos "+ x+ ", "+y+" already has a entity, ignoring '"+e->name()+"'");
		}
	}
}