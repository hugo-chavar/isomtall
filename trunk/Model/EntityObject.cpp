#include "EntityObject.h"


EntityObject::EntityObject() {
	_name = "DEFAULT";
	_image_path = DEFAULT_TILE_IMAGE;
	_base_width = DEFAULT_BASE_WIDTH;
	_base_height = DEFAULT_BASE_HEIGHT;
	_pixel_ref_x = DEFAULT_PIXEL_REF_X;
	_pixel_ref_y = DEFAULT_PIXEL_REF_Y;
}

EntityObject::~EntityObject() { }

string EntityObject::name() {
	return _name;
}

void EntityObject::name(string value) {
	_name = value;
}
//
//bool EntityObject::isAnimated() {
//	return false;
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

void EntityObject::baseWidth(int value) {
	_base_width = value;
}

int EntityObject::baseHeight() {
	return _base_height;
}

void EntityObject::baseHeight(int value) {
	_base_height = value;
}

int EntityObject::pixelRefX() {
	return _pixel_ref_x;
}

void EntityObject::pixelRefX(int value) {
	_pixel_ref_x = value;
}

int EntityObject::pixelRefY() {
	return _pixel_ref_y;
}

void EntityObject::pixelRefY(int value) {
	_pixel_ref_y = value;
}