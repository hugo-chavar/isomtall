#include "Configuration.h"

using namespace common;

Configuration::Configuration(){
	_cameraScrollSpeed = DEFAULT_SCROLL_SPEED;
	_cameraWidth = DEFAULT_SCREEN_WIDTH;
	_cameraHeight = DEFAULT_SCREEN_HEIGHT;
	_serverPort = DEFAULT_SERVER_PORT;
	_visionRange = DEFAULT_VISION_RANGE;
	_mainCharacterSpeed = DEFAULT_MAIN_CHARACTER_SPEED;
}

Configuration::~Configuration(){

}

unsigned int Configuration::cameraWidth(){
	return _cameraWidth;
}

unsigned int Configuration::cameraHeight(){
	return _cameraHeight;
}

void Configuration::cameraHeight(int value){
	if (value >= MIN_SCREEN_HEIGHT){
		_cameraHeight = static_cast<unsigned>(value);
	} else {
		Logger::instance().log("Game warning: Field 'alto pantalla' is too low, defaulted.");
	}
}

void Configuration::cameraWidth(int value){
	if (value >= MIN_SCREEN_WIDTH){
		_cameraWidth = static_cast<unsigned>(value);
	} else {
		Logger::instance().log("Game warning: Field 'ancho pantalla' is too low, defaulted.");
	}
}

unsigned int Configuration::cameraMarginScroll(){
	return _cameraMarginScroll;
}

void Configuration::cameraMarginScroll(int value){
	if ((value >= MIN_SCROLL_MARGIN) && (value <= MAX_SCROLL_MARGIN)){
		_cameraMarginScroll = static_cast<unsigned>(value);
	} else if (value < MIN_SCROLL_MARGIN) {
		Logger::instance().log("Game warning: Field 'margen_scroll' is too low, setted to minimun.");
		_cameraMarginScroll = MIN_SCROLL_MARGIN;
	} else if (value > MAX_SCROLL_MARGIN) {
		Logger::instance().log("Game warning: Field 'margen_scroll' is too high, setted to maximun.");
		_cameraMarginScroll = MAX_SCROLL_MARGIN;
	}
}

unsigned int Configuration::cameraSpeed(){
	return _cameraScrollSpeed;
}

void Configuration::initialize(int dimentionX, int dimentionY, int scr){
	cameraMarginScroll(scr);
	cameraWidth(dimentionX);
	cameraHeight(dimentionY);
}

void Configuration::serverPort(int value){
	// rango de puertos validos
	if ( (value >= 1024) && (value <= 65535) ){
		_serverPort = static_cast<unsigned>(value);
	} else {
		Logger::instance().log("Game warning: Field 'puerto servidor' is not valid, defaulted.");
		
	}
}

unsigned int Configuration::serverPort(){
	return _serverPort;
}

void Configuration::visionRange(int value){
	// rango de puertos validos
	if ( (value >= 2) && (value <= 5000) ){
		_visionRange = static_cast<unsigned>(value);
	} else {
		Logger::instance().log("Game warning: Field 'vision personaje' is not valid, defaulted.");
		
	}
}

float Configuration::mainCharacterSpeed(){
	return _mainCharacterSpeed;
}

void Configuration::mainCharacterSpeed(float value){
	if ((value >= MIN_MAIN_CHARACTER_SPEED) && (value <= MAX_MAIN_CHARACTER_SPEED)){
		_mainCharacterSpeed = value;
	} else if (value > float(MAX_MAIN_CHARACTER_SPEED)) {
		Logger::instance().log("Game warning: Field 'vel_personaje' is too high, setted to maximun.");
		_mainCharacterSpeed = float(MAX_MAIN_CHARACTER_SPEED);
	} else {
		Logger::instance().log("Game warning: Field 'vel_personaje' is too low, setted to minimun.");
		_mainCharacterSpeed = float(MIN_MAIN_CHARACTER_SPEED);
	}
}

unsigned int Configuration::visionRange(){
	return _visionRange;
}