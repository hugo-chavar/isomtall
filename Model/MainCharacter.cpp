#include "MainCharacter.h"


MainCharacter::MainCharacter() { }

MainCharacter::~MainCharacter() { }

AnimatedEntity* MainCharacter::entityType() {
	return _entity_type;
}

int MainCharacter::x() {
	return _x;
}

int MainCharacter::y() {
	return _y;
}

int MainCharacter::speed() {
	return _speed;
}

void MainCharacter::speed(int value) {
	_speed = value;
}