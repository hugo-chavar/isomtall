#include "CharacterVision.h"
#include "Game.h"
#include "TileModel.h"

CharacterVision::CharacterVision(){
	mapKnowledge.clear();
}

CharacterVision::~CharacterVision(){

}

void CharacterVision::setRangeVision(int value){
	this->rangeVision = value;
}

void CharacterVision::initialize(){
	this->mapWidth = Game::instance().world()->width();
	this->mapHeight = Game::instance().world()->height();
	//this->prevPosition = this->position;
	for (int i = 0; i < this->mapHeight; i++){
		bitset <MAX_STAGE_SIZE_X> line;
		line.reset();
		mapKnowledge.push_back(line);
	}
	this->setKnown(this->position);
	pair<int, int > aux;
	for (int i = 1; i <= this->rangeVision; i++){
		aux = this->position;
		for (int j = i; j > 0; j--){
			aux.second = this->position.second - j;
			aux.first = this->position.first - (i - j);
			this->setKnown(aux);
			if (this->position.first != aux.first){
				aux.first = this->position.first + (i - j);
				this->setKnown(aux);
			}
			aux.second = this->position.second + j;
			aux.first = this->position.first - (i - j);
			this->setKnown(aux);
			if (this->position.first != aux.first){
				aux.first = this->position.first + (i - j);
				this->setKnown(aux);
			}
		}
		aux.second = this->position.second;
		aux.first = this->position.first - i;
		this->setKnown(aux);
		aux.first = this->position.first + i;
		this->setKnown(aux);
	}
}

void CharacterVision::setPosition(pair<int, int> pos){
	this->position = pos;
}

void CharacterVision::updatePosition(pair<int, int> pos){
	if (pos == this->position)
		return;
	pair<int, int > aux = pos;
	if (pos.first > this->position.first) { //TODO: eliminar codigo repetido
		if (pos.second == this->position.second){
			for (int j = this->rangeVision; j > 0; j--){
				aux.second = this->position.second - j;
				aux.first = pos.first + (this->rangeVision - j);
				this->setKnown(aux);
				aux.second = this->position.second + j;
				this->setKnown(aux);
			}
			aux.second = this->position.second;
			aux.first = pos.first + this->rangeVision;
			this->setKnown(aux);
		} else if (pos.second > this->position.second) {
			for (int j = this->rangeVision; j > 0; j--){
				aux.second = pos.second + j;
				aux.first = pos.first + (this->rangeVision - j);
				this->setKnown(aux);
				aux.second -= 1;
				this->setKnown(aux);
			}
			aux.second = pos.second;
			aux.first = pos.first + this->rangeVision;
			this->setKnown(aux);
		} else  { //if (pos.second < this->position.second)
			for (int j = this->rangeVision; j > 0; j--){
				aux.second = pos.second - j;
				aux.first = pos.first + (this->rangeVision - j);
				this->setKnown(aux);
				aux.second += 1;
				this->setKnown(aux);
			}
			aux.second = pos.second;
			aux.first = pos.first + this->rangeVision;
			this->setKnown(aux);
		}
	} else if (pos.first < this->position.first) {
		if (pos.second == this->position.second){
			for (int j = this->rangeVision; j > 0; j--){
				aux.second = this->position.second - j; 
				aux.first = pos.first - (this->rangeVision - j);
				this->setKnown(aux);
				aux.second = this->position.second + j;
				this->setKnown(aux);
			}
			aux.second = this->position.second;
			aux.first = pos.first - this->rangeVision;
			this->setKnown(aux);
		} else if (pos.second > this->position.second) { 
			for (int j = this->rangeVision; j > 0; j--){
				aux.second = pos.second + j;
				aux.first = pos.first - (this->rangeVision - j);
				this->setKnown(aux);
				aux.second -= 1;
				this->setKnown(aux);
			}
			aux.second = pos.second;
			aux.first = pos.first - this->rangeVision;
			this->setKnown(aux);
		} else  { //if (pos.second < this->position.second)
			for (int j = this->rangeVision; j > 0; j--){
				aux.second = pos.second - j;
				aux.first = pos.first - (this->rangeVision - j);
				this->setKnown(aux);
				aux.second += 1;
				this->setKnown(aux);
			}
			aux.second = pos.second;
			aux.first = pos.first - this->rangeVision;
			this->setKnown(aux);
		}
	} else {
		if (pos.second > this->position.second) {
			for (int j = this->rangeVision; j > 0; j--){
				aux.first = this->position.first - j; 
				aux.second = pos.second + (this->rangeVision - j);
				this->setKnown(aux);
				aux.first = this->position.first + j;
				this->setKnown(aux);
			}
			aux.first = this->position.first; 
			aux.second = pos.second + this->rangeVision;
			this->setKnown(aux);
		} else  {
			for (int j = this->rangeVision; j > 0; j--){
				aux.first = this->position.first - j;
				aux.second = pos.second - (this->rangeVision - j);
				this->setKnown(aux);
				aux.first = this->position.first + j;
				this->setKnown(aux);
			}
			aux.first = this->position.first;
			aux.second = pos.second - this->rangeVision;
			this->setKnown(aux);
		}
	}
	this->position = pos;
}

bool CharacterVision::testPosition(pair<int, int> pos){
	return this->mapKnowledge[pos.second].test(pos.first);
}

void CharacterVision::setKnown(pair<int, int> pos){
	if (Game::instance().world()->isInsideWorld(pos)){
		this->mapKnowledge[pos.second].set(pos.first);
		TileModel* relatedTile = Game::instance().world()->getTileAt(pos)->getRelatedTile();
		if (relatedTile){
			while (relatedTile != Game::instance().world()->getTileAt(pos) ){
				pair<int, int> posRelated = relatedTile->getPosition();
				this->mapKnowledge[posRelated.second].set(posRelated.first);
				relatedTile = relatedTile->getRelatedTile();
			}
		}
	}
}

bool CharacterVision::isInsideVision(pair<int, int> pos){

	int bottom =  (this->position.second - this->rangeVision + abs(this->position.first - pos.first));
	int top = this->position.second + this->rangeVision- abs(this->position.first - pos.first);
	return ((pos.second  >= bottom)	&& (pos.second <= top));
}
