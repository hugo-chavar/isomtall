#include "Stage.h"
#include "Game.h"

using namespace std;
using namespace model;

Stage::Stage(){
	_entityMap = NULL;
	_vMainCharacters.clear();
	_vEntitiesDef.clear();
}

Stage::Stage(const Stage &origStage){
	this->name(origStage.name());
	this->height(origStage.height());
	this->width(origStage.width());
	this->tileWidth(origStage.tileWidth());
	this->tileHeight(origStage.tileHeight());
	this->_entityMap = origStage._entityMap;
	this->_vMainCharacters.assign(origStage._vMainCharacters.begin(),origStage._vMainCharacters.end());
	this->_vEntitiesDef = origStage._vEntitiesDef;
	this->_entityMap = origStage._entityMap;
	this->_mainCharacter_speed = origStage._mainCharacter_speed;
}

Stage& Stage::operator=(const Stage &origStage){
	this->name(origStage.name());
	this->height(origStage.height());
	this->width(origStage.width());
	this->tileWidth(origStage.tileWidth());
	this->tileHeight(origStage.tileHeight());
	this->_entityMap = origStage._entityMap;
	this->_vMainCharacters.assign(origStage._vMainCharacters.begin(),origStage._vMainCharacters.end());
	this->_vEntitiesDef = origStage._vEntitiesDef;
	this->_entityMap = origStage._entityMap;
	this->_mainCharacter_speed = origStage._mainCharacter_speed;
	return *this;
}

string Stage::name() const {
	return _name;
}

unsigned int Stage::width() const{
	return _width;
}

unsigned int Stage::height() const{
	return _height;
}

void Stage::height(unsigned int value){
	_height = value;
}

void Stage::width(unsigned int value){
	_width = value;
}

vector <EntityDef> Stage::vEntitiesDef() {
	return _vEntitiesDef;
}

vector <PersonajeModelo*>* Stage::vMainCharacters() {
	return &_vMainCharacters;
}

map <KeyPair, EntityObject*>* Stage::entityMap() {
	return _entityMap;
}

//info de los tiles
unsigned int Stage::tileWidth() const{
	return _tileWidth;
}

unsigned int Stage::tileHeight() const{
	return _tileHeight;
}

void Stage::tileHeight(unsigned int value){
	_tileHeight = value;
}

void Stage::tileWidth(unsigned int value){
	_tileWidth = value;
}

void Stage::name(string value){
	_name = value;
}

float Stage::mainCharacter_speed()  const{
	return _mainCharacter_speed;
}

void Stage::mainCharacter_speed(float value) {
	if ((value >= MIN_MAIN_CHARACTER_SPEED) && (value <= MAX_MAIN_CHARACTER_SPEED)){
		_mainCharacter_speed = value;
	} else if (value > float(MAX_MAIN_CHARACTER_SPEED)) {
		Logger::instance().log("Game warning: Field 'vel_personaje' is too high, setted to maximun.");
		_mainCharacter_speed = float(MAX_MAIN_CHARACTER_SPEED);
	} else {
		Logger::instance().log("Game warning: Field 'vel_personaje' is too low, setted to minimun.");
		_mainCharacter_speed = float(MIN_MAIN_CHARACTER_SPEED);
	}
}


unsigned int Stage::cost(unsigned int x, unsigned int y){
	return 1;
}

void Stage::initialize(unsigned int dimentionX, unsigned int dimentionY, unsigned int tHeight, unsigned int tWidth){
	width(dimentionX);
	height(dimentionY);
	tileWidth(tWidth);
	tileHeight(tHeight);
}

std::pair<int,int> Stage::pixelToTileCoordinatesInStage(std::pair<int,int> pixelCoordinates, float cameraX, float cameraY) {
	float tileX = 0;
	float tileY = 0;
	float aux = static_cast<float>(pixelCoordinates.first + cameraX)/2;

	tileX = floor(static_cast<float>((pixelCoordinates.second + cameraY + aux) / this->tileHeight()));

	tileY = floor(static_cast<float>((pixelCoordinates.second + cameraY - aux) / this->tileHeight()));

	return std::make_pair<int,int>(static_cast<int>(tileX),static_cast<int>(tileY));
}

std::pair<int,int> Stage::pixelToTileCoordinates(std::pair<int,int> pixelCoordinates) {

	return pixelToTileCoordinatesInStage(pixelCoordinates,0,0);
}

bool Stage::isInsideWorld(std::pair<int,int> tileCoordinates) {
	return ( (tileCoordinates.first >= 0) && (tileCoordinates.first < static_cast<int>(this->width())) && (tileCoordinates.second >= 0) && (tileCoordinates.second < static_cast<int>(this->height())) );
}

void Stage::destino(int x,int y,float cameraX,float cameraY){
	std::pair<int,int> pixelCoordinates;
	pixelCoordinates.first = x;
	pixelCoordinates.second = y;
	std::pair<int,int> destino = pixelToTileCoordinatesInStage(pixelCoordinates,cameraX,cameraY);

	if(isInsideWorld(destino)) 
		Game::instance().personaje()->setDestino(destino.first,destino.second);
}


void Stage::insertMainCharacter(PersonajeModelo* pm){
	_vMainCharacters.push_back(pm);
}

PersonajeModelo* Stage::modelMainCharacters(unsigned pos){
	if (_vMainCharacters.size() > pos)
		return _vMainCharacters[pos];
	return NULL;
}

void Stage::clearStage(){
	for (unsigned j=0; j < (this->_vMainCharacters.size()); j++)
			delete _vMainCharacters[j];
	_vMainCharacters.clear();
	if (_entityMap){
		_entityMap->clear();
		delete _entityMap;
		_entityMap = NULL;
	}
	_vEntitiesDef.clear();
}