#include "Explosive.h"
#include "GameView.h"
#include "Logger.h"
#include "../Common/StringUtilities.h"

Explosive::Explosive():Ammunition() {
	//this->exploded = false;
}

Explosive::~Explosive() {
}

void Explosive::setRange(int value) {
	this->range.setRadius(value);
}

void Explosive::setCenter(std::pair<int, int> value) {
	this->range.setCenter(value);
}

void Explosive::activate() {
	this->range.initialize();
}