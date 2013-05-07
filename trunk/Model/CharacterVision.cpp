#include "CharacterVision.h"
#include "Game.h"

CharacterVision::CharacterVision(){
	mapKnowledge.clear();
}

CharacterVision::~CharacterVision(){

}
//
//void CharacterVision::setMapWidth(int value){
//	this->mapWidth = value;
//}
//
//void CharacterVision::setMapHeight(int value){
//	this->mapHeight = value;
//}

void CharacterVision::initialize(){
	this->mapWidth = Game::instance().world()->width();
	this->mapHeight = Game::instance().world()->height();
	this->prevPosition = this->position;
	for (int i = 0; i < this->mapHeight; i++){
		bitset <MAX_STAGE_SIZE_X> line;
		line.reset();
		mapKnowledge.push_back(line);
	}
	pair<int, int > aux;
	for (int i = 1; i <= this->rangeVision; i++){
		aux = this->position;
		for (int j = i; j >= 0; j--){
			aux.second = this->position.second - j;
			aux.first = this->position.first - (i - j);
			this->setKnown(aux);
			aux.first = this->position.first + (i - j);
			this->setKnown(aux);
			aux.second = this->position.second + j;
			aux.first = this->position.first - (i - j);
			this->setKnown(aux);
			aux.first = this->position.first + (i - j);
			this->setKnown(aux);

		}
	}
}

void CharacterVision::setPosition(pair<int, int> pos){
	this->position = pos;
}

void CharacterVision::updatePosition(pair<int, int> pos){
	this->position = pos;
}

bool CharacterVision::testPosition(pair<int, int> pos){
	return this->mapKnowledge[pos.first].test(pos.second);
}

void CharacterVision::setKnown(pair<int, int> pos){
	this->mapKnowledge[pos.first].set(pos.second);
}
