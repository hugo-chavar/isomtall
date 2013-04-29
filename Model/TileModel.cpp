#include "TileModel.h"


TileModel::TileModel(){
}

EntityObject * TileModel::getEntity(){
	return this->entity;
}

void TileModel::setEntity(EntityObject * e){
	this->entity = e;
}