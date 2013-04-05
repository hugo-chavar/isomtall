#include "Tile.h"

using namespace model;

Tile::Tile(){
}

EntityObject * Tile::getEntity(){
	return this->entity;
}

void Tile::setEntity(EntityObject * e){
	this->entity = e;
}