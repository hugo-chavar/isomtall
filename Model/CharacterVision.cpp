#include "CharacterVision.h"
#include "Game.h"
#include "../View/GameView.h"
#include "TileModel.h"
#include "StringUtilities.h"
#include "Logger.h"

CharacterVision::CharacterVision() {
	mapKnowledge.clear();
	this->setAllKnown(false);
	this->setRangeVision(0);
}

CharacterVision::~CharacterVision() {

}

void CharacterVision::setRangeVision(int value) {
	this->rangeVision = value;
}

int CharacterVision::getRangeVision() {
	return this->rangeVision;
}


void CharacterVision::increaseRangeVision(int value) {
	this->rangeVision += value;
	this->updateVision();
}

void CharacterVision::initialize() {
	this->mapWidth = Game::instance().world()->width();
	this->mapHeight = Game::instance().world()->height();
	for (int i = 0; i < this->mapHeight; i++) {
		bitset <MAX_STAGE_SIZE_X> line;
		line.reset();
		mapKnowledge.push_back(line);
	}
	this->updateVision();
}

void CharacterVision::updatePosition(pair<int, int> pos) {
	if (pos == this->getPosition())
		return;
	this->setPosition(pos);
	this->updateVision();
}

void CharacterVision::updateVision() {
	vision.initialize(this->getPosition(), this->rangeVision);
	if (!this->isAllKnown()) {
		
		vision.fill();
		pair<int, int > aux;
		while (vision.hasNext()) {
			aux = vision.next();
			this->setKnown(aux);
		}
	}
}

bool CharacterVision::testPosition(pair<int, int> pos) {
	return this->mapKnowledge[pos.second].test(pos.first);
}

void CharacterVision::setKnown(pair<int, int> pos){
	if (Game::instance().world()->isInsideWorld(pos)) {
		if (testPosition(pos))
			return;
		this->mapKnowledge[pos.second].set(pos.first);
		TileModel* relatedTile = Game::instance().world()->getTileAt(pos)->getRelatedTile();
		if (relatedTile) {
			while (relatedTile != Game::instance().world()->getTileAt(pos) ) {
				pair<int, int> posRelated = relatedTile->getPosition();
				this->mapKnowledge[posRelated.second].set(posRelated.first);
				relatedTile = relatedTile->getRelatedTile();
			}
		}
	}
}

bool CharacterVision::isInsideVision(pair<int, int> pos) {
	return this->vision.inside(pos);
}

string CharacterVision::initToString() {
	string out = "";
	if (!this->isAllKnown()) {
		pair<int, int> pos;
		for (pos.first = 0; pos.first < this->mapHeight; pos.first++) {
			for (pos.second = 0; pos.second < this->mapWidth; pos.second++) {
				if ((this->testPosition(pos)) && (!vision.inside(pos)) ) {
					out.append("?");
					out.append(stringUtilities::pairIntToString(pos));
				}
			}
		}
	}
	return out;
}

void CharacterVision::initFromString(string data) {
	if (!this->isAllKnown() && (data.size() > 2)) {
		pair<int, int> pos;
		vector <string> auxVector;
		auxVector.clear();
		stringUtilities::splitString(data, auxVector, '?');
		vector <string>::iterator it;
		it = auxVector.begin();
		for (; it != auxVector.end(); it++) {
			if (((*it).size() > 1) && ((*it).find(",") != std::string::npos)) {
				pos = stringUtilities::stringToPairInt(*it);
				this->setKnown(pos);
			}
		}
	}
}

string CharacterVision::updateToString() {
	string out = stringUtilities::intToString(this->rangeVision);
	out.append("z");
	if (this->isAllKnown()) {
		out.append("A");
	} 
	return out;
}

void CharacterVision::updateFromString(string data) {
	vector <string> auxVector;
	auxVector.clear();
	stringUtilities::splitString(data, auxVector, 'z');
	this->setRangeVision(stringUtilities::stringToInt(auxVector[0]));
	if (auxVector[1] == "A") {
		this->setAllKnown(true);
	}
}

void CharacterVision::setAllKnown(bool value) {
	this->allKnown = value;
}

bool CharacterVision::isAllKnown() {
	return this->allKnown;
}

void CharacterVision::setMagicVision(bool value) {
	this->magicVision = value;
}

bool CharacterVision::setMagicVision() {
	return this->magicVision;
}