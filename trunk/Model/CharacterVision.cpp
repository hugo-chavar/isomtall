#include "CharacterVision.h"
#include "Game.h"

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
	if (pos.first > this->position.first) {
		for (int j = this->rangeVision; j > 0; j--){
			aux.second = pos.second - j;
			aux.first = pos.first + (this->rangeVision - j);
			this->setKnown(aux);
			aux.second = pos.second + j;
			this->setKnown(aux);
		}
		aux.second = pos.second;
		aux.first = pos.first + this->rangeVision;
		this->setKnown(aux);
	} else if (pos.first < this->position.first) {
		for (int j = this->rangeVision; j > 0; j--){
			aux.second = pos.second - j;
			aux.first = pos.first - (this->rangeVision - j);
			this->setKnown(aux);
			aux.second = pos.second + j;
			this->setKnown(aux);
		}
		aux.second = pos.second;
		aux.first = pos.first - this->rangeVision;
		this->setKnown(aux);
	}
	if (pos.second > this->position.second) {
		for (int j = this->rangeVision; j > 0; j--){
			aux.first = pos.first - j;
			aux.second = pos.second + (this->rangeVision - j);
			this->setKnown(aux);
			aux.first = pos.first + j;
			this->setKnown(aux);
		}
		aux.second = pos.second;
		aux.first = pos.first + this->rangeVision;
		this->setKnown(aux);
	} else if (pos.second < this->position.second) {
		for (int j = this->rangeVision; j > 0; j--){
			aux.first = pos.first - j;
			aux.second = pos.second - (this->rangeVision - j);
			this->setKnown(aux);
			aux.first = pos.first + j;
			this->setKnown(aux);
		}
		aux.first = pos.first;
		aux.second = pos.second - this->rangeVision;
		this->setKnown(aux);
	}
	this->position = pos;
}

bool CharacterVision::testPosition(pair<int, int> pos){
	return this->mapKnowledge[pos.second].test(pos.first);
}

void CharacterVision::setKnown(pair<int, int> pos){
	if (Game::instance().world()->isInsideWorld(pos))
		this->mapKnowledge[pos.second].set(pos.first);
}

bool CharacterVision::isInsideVision(pair<int, int> pos){
	return ((pos.first <= (this->position.first + this->rangeVision)) && (pos.first >= (this->position.first - this->rangeVision)) && (pos.second <= (this->position.second + this->rangeVision)) && (pos.second  >= (this->position.second - this->rangeVision)));
}
