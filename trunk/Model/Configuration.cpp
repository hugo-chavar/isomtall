#include "Configuration.h"

using namespace common;

Configuration::Configuration(){
	this->_cameraScrollSpeed = DEFAULT_SCROLL_SPEED;
	this->_cameraWidth = DEFAULT_SCREEN_WIDTH;
	this->_cameraHeight = DEFAULT_SCREEN_HEIGHT;
	//_serverPort = DEFAULT_SERVER_PORT;
	//_serverPort = DEFAULT_SERVER_IP;
	this->_visionRange = DEFAULT_VISION_RANGE;
	this->_mainCharacterSpeed = DEFAULT_MAIN_CHARACTER_SPEED;
}

Configuration::Configuration(const Configuration &source){
	this->_cameraScrollSpeed = source._cameraScrollSpeed;
	this->_cameraWidth = source._cameraWidth;
	this->_cameraHeight = source._cameraHeight;
	//_serverPort = source._serverPort;
	this->_visionRange = source._visionRange;
	this->_mainCharacterSpeed = source._mainCharacterSpeed;
	//la ip se setea en otro punto.. no copiarla
}

Configuration& Configuration::operator=(const Configuration &source){
	this->_cameraScrollSpeed = source._cameraScrollSpeed;
	this->_cameraWidth = source._cameraWidth;
	this->_cameraHeight = source._cameraHeight;
	//_serverPort = source._serverPort;
	this->_visionRange = source._visionRange;
	this->_mainCharacterSpeed = source._mainCharacterSpeed;
	//la ip se setea en otro punto.. no copiarla
	return *this;
}


Configuration::~Configuration() {

}

unsigned int Configuration::cameraWidth() {
	return this->_cameraWidth;
}

unsigned int Configuration::cameraHeight() {
	return this->_cameraHeight;
}

void Configuration::cameraHeight(int value) {
	if (value >= MIN_SCREEN_HEIGHT) {
		this->_cameraHeight = static_cast<unsigned>(value);
	} else {
		Logger::instance().log("Game warning: Field 'alto pantalla' is too low, defaulted.");
	}
}

void Configuration::cameraWidth(int value) {
	if (value >= MIN_SCREEN_WIDTH) {
		this->_cameraWidth = static_cast<unsigned>(value);
	} else {
		Logger::instance().log("Game warning: Field 'ancho pantalla' is too low, defaulted.");
	}
}

unsigned int Configuration::cameraMarginScroll() {
	return this->_cameraMarginScroll;
}

void Configuration::cameraMarginScroll(int value) {
	if ((value >= MIN_SCROLL_MARGIN) && (value <= MAX_SCROLL_MARGIN)) {
		this->_cameraMarginScroll = static_cast<unsigned>(value);
	} else if (value < MIN_SCROLL_MARGIN) {
		Logger::instance().log("Game warning: Field 'margen_scroll' is too low, setted to minimun.");
		this->_cameraMarginScroll = MIN_SCROLL_MARGIN;
	} else if (value > MAX_SCROLL_MARGIN) {
		Logger::instance().log("Game warning: Field 'margen_scroll' is too high, setted to maximun.");
		this->_cameraMarginScroll = MAX_SCROLL_MARGIN;
	}
}

unsigned int Configuration::cameraSpeed() {
	return this->_cameraScrollSpeed;
}

void Configuration::initialize(int dimentionX, int dimentionY, int scr) {
	cameraMarginScroll(scr);
	cameraWidth(dimentionX);
	cameraHeight(dimentionY);
}

void Configuration::serverPort(int value) {
	// rango de puertos validos
	if ( (value >= 1024) && (value <= 65535) ){
		this->_serverPort = static_cast<unsigned>(value);
	} else {
		Logger::instance().log("Game warning: Field 'puerto servidor' is not valid, defaulted.");
		
	}
}

unsigned int Configuration::serverPort() {
	return _serverPort;
}

void Configuration::visionRange(int value) {
	// rango de puertos validos
	if ( (value >= 2) && (value <= 5000) ) {
		this->_visionRange = static_cast<unsigned>(value);
	} else {
		Logger::instance().log("Game warning: Field 'vision personaje' is not valid, defaulted.");
		
	}
}

float Configuration::mainCharacterSpeed() {
	return this->_mainCharacterSpeed;
}

void Configuration::mainCharacterSpeed(float value) {
	if ((value >= MIN_MAIN_CHARACTER_SPEED) && (value <= MAX_MAIN_CHARACTER_SPEED)) {
		this->_mainCharacterSpeed = value;
	} else if (value > float(MAX_MAIN_CHARACTER_SPEED)) {
		Logger::instance().log("Game warning: Field 'vel_personaje' is too high, setted to maximun.");
		this->_mainCharacterSpeed = float(MAX_MAIN_CHARACTER_SPEED);
	} else {
		Logger::instance().log("Game warning: Field 'vel_personaje' is too low, setted to minimun.");
		this->_mainCharacterSpeed = float(MIN_MAIN_CHARACTER_SPEED);
	}
}

unsigned int Configuration::visionRange() {
	return this->_visionRange;
}

std::string Configuration::serverIp() {
	return this->_serverIp;
}

void Configuration::serverIp(std::string ip) {
	this->_serverIp = ip;
}