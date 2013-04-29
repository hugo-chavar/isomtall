#include "StageModel.h"
#include "Game.h"

using namespace std;

StageModel::StageModel(){
	_entityMap = NULL;
	_vMainCharacters.clear();
	_vEntitiesDef.clear();
}

StageModel::StageModel(const StageModel &origStage){
	this->name(origStage.name());
	this->height(origStage.height());
	this->width(origStage.width());
	this->tileWidth(origStage.tileWidth());
	this->tileHeight(origStage.tileHeight());
	this->_entityMap = origStage._entityMap;
	this->_vMainCharacters.assign(origStage._vMainCharacters.begin(),origStage._vMainCharacters.end());
	this->_vEntitiesDef = origStage._vEntitiesDef;
	this->_entityMap = origStage._entityMap;
}

StageModel& StageModel::operator=(const StageModel &origStage){
	this->name(origStage.name());
	this->height(origStage.height());
	this->width(origStage.width());
	this->tileWidth(origStage.tileWidth());
	this->tileHeight(origStage.tileHeight());
	this->_entityMap = origStage._entityMap;
	this->_vMainCharacters.assign(origStage._vMainCharacters.begin(),origStage._vMainCharacters.end());
	this->_vEntitiesDef = origStage._vEntitiesDef;
	this->_entityMap = origStage._entityMap;
	return *this;
}

string StageModel::name() const {
	return _name;
}

unsigned int StageModel::width() const{
	return _width;
}

unsigned int StageModel::height() const{
	return _height;
}

void StageModel::height(unsigned int value){
	_height = value;
}

void StageModel::width(unsigned int value){
	_width = value;
}

vector <EntityDef> StageModel::vEntitiesDef() {
	return _vEntitiesDef;
}

vector <PersonajeModelo*>* StageModel::vMainCharacters() {
	return &_vMainCharacters;
}

map <KeyPair, EntityObject*>* StageModel::entityMap() {
	return _entityMap;
}

//info de los tiles
unsigned int StageModel::tileWidth() const{
	return _tileWidth;
}

unsigned int StageModel::tileHeight() const{
	return _tileHeight;
}

void StageModel::tileHeight(unsigned int value){
	_tileHeight = value;
}

void StageModel::tileWidth(unsigned int value){
	_tileWidth = value;
}

void StageModel::name(string value){
	_name = value;
}

unsigned int StageModel::cost(unsigned int x, unsigned int y){
	return 1;
}

void StageModel::initialize(unsigned int dimentionX, unsigned int dimentionY, unsigned int tHeight, unsigned int tWidth){
	width(dimentionX);
	height(dimentionY);
	tileWidth(tWidth);
	tileHeight(tHeight);
}

std::pair<int,int> StageModel::pixelToTileCoordinatesInStage(std::pair<int,int> pixelCoordinates, float cameraX, float cameraY) {
	float tileX = 0;
	float tileY = 0;
	float aux = static_cast<float>(pixelCoordinates.first + cameraX)/2;

	tileX = floor(static_cast<float>((pixelCoordinates.second + cameraY + aux) / this->tileHeight()));

	tileY = floor(static_cast<float>((pixelCoordinates.second + cameraY - aux) / this->tileHeight()));

	return std::make_pair<int,int>(static_cast<int>(tileX),static_cast<int>(tileY));
}

std::pair<int,int> StageModel::pixelToTileCoordinates(std::pair<int,int> pixelCoordinates) {

	return pixelToTileCoordinatesInStage(pixelCoordinates,0,0);
}

bool StageModel::isInsideWorld(std::pair<int,int> tileCoordinates) {
	return ( (tileCoordinates.first >= 0) && (tileCoordinates.first < static_cast<int>(this->width())) && (tileCoordinates.second >= 0) && (tileCoordinates.second < static_cast<int>(this->height())) );
}

void StageModel::destino(int x,int y,float cameraX,float cameraY){
	std::pair<int,int> pixelCoordinates;
	pixelCoordinates.first = x;
	pixelCoordinates.second = y;
	std::pair<int,int> destino = pixelToTileCoordinatesInStage(pixelCoordinates,cameraX,cameraY);

	if(isInsideWorld(destino)) 
		Game::instance().personaje()->setDestino(destino.first,destino.second);
}


void StageModel::insertMainCharacter(PersonajeModelo* pm){
	_vMainCharacters.push_back(pm);
}

PersonajeModelo* StageModel::modelMainCharacters(unsigned pos){
	if (_vMainCharacters.size() > pos)
		return _vMainCharacters[pos];
	return NULL;
}

void StageModel::clearStage(){
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