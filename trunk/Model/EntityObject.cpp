#include "EntityObject.h"

using namespace model;



EntityObject::EntityObject() {
	_name = "default";
	// DEFINIR _image_path, _base_width, _base_height, _positionX, _positionY DEFAULT
	// pixel_ref_x, pixel_ref_y ?
}

EntityObject::~EntityObject() { }

string EntityObject::name() {
	return _name;
}

int EntityObject::positionX() {
	return _positionX;
}

int EntityObject::positionY() {
	return _positionY;
}

void EntityObject::position(int valueX, int valueY) {
	_positionX = valueX;
	_positionY = valueY;
}

void EntityObject::imagePath(string value) {
	_image_path = value;
}

string EntityObject::imagePath() {
	return _image_path;
}

int EntityObject::baseWidth() {
	return _base_width;
}

int EntityObject::baseHeight() {
	return _base_height;
}

int EntityObject::pixelRefX() {
	return _pixel_ref_x;
}

int EntityObject::pixelRefY() {
	return _pixel_ref_y;
}