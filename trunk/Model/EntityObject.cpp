#include "EntityObject.h"


EntityObject::EntityObject() {
	_name = "DEFAULT";
	_image_path = DEFAULT_TILE_IMAGE;
	_base_width = DEFAULT_BASE_WIDTH;
	_base_height = DEFAULT_BASE_HEIGHT;
	_pixel_ref_x = DEFAULT_PIXEL_REF_X;
	_pixel_ref_y = DEFAULT_PIXEL_REF_Y;
	// DEFINIR _positionX, _positionY DEFAULT
}

EntityObject::~EntityObject() { }

string EntityObject::name() {
	return _name;
}

//int EntityObject::positionX() {
//	return _positionX;
//}
//
//int EntityObject::positionY() {
//	return _positionY;
//}

//void EntityObject::position(int valueX, int valueY) {
//	_positionX = valueX;
//	_positionY = valueY;
//}

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