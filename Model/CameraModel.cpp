#include "CameraModel.h"


using namespace common;
using namespace model;

CameraModel::CameraModel(){
	_speed = DEFAULT_SCROLL_SPEED;
}

CameraModel::~CameraModel(){

}

unsigned int CameraModel::width(){
	return _width;
}

unsigned int CameraModel::height(){
	return _height;
}

void CameraModel::height(int value){
	if (value >= MIN_SCREEN_HEIGHT){
		_height = static_cast<unsigned>(value); //value;
	} else {
		Logger::instance().log("Game warning: Field 'alto pantalla' is too low, defaulted.");
		_height = DEFAULT_SCREEN_HEIGHT;
	}
}

void CameraModel::width(int value){
	if (value >= MIN_SCREEN_WIDTH){
		_width = static_cast<unsigned>(value); //value;
	} else {
		Logger::instance().log("Game warning: Field 'ancho pantalla' is too low, defaulted.");
		_width = DEFAULT_SCREEN_WIDTH;
	}
}

unsigned int CameraModel::scroll(){
	return _scroll;
}

void CameraModel::scroll(int value){
	if (value >= MIN_SCROLL_MARGIN){
		_scroll = static_cast<unsigned>(value); //value;
	} else {
		Logger::instance().log("Game warning: Field 'margen_scroll' is too low, defaulted.");
		_scroll = DEFAULT_SCROLL_MARGIN;
	}
}

unsigned int CameraModel::speed(){
	return _speed;
}

void CameraModel::initialize(int dimentionX, int dimentionY, int scr){
	scroll(scr);
	width(dimentionX);
	height(dimentionY);
}

