#include "StageModel.h"
#include "Game.h"
#include "stringUtilities.h"

using namespace std;

StageModel::StageModel(){
	this->_tilesMap = NULL;
	this->firstTile = NULL;
	_vMainCharacters.clear();
	_vEntitiesDef.clear();
}

StageModel::StageModel(const StageModel &origStage){
	this->name(origStage.name());
	this->height(origStage.height());
	this->width(origStage.width());
	this->tileWidth(origStage.tileWidth());
	this->tileHeight(origStage.tileHeight());
	this->_tilesMap = origStage._tilesMap;
	this->firstTile = origStage.firstTile;
	this->_vMainCharacters.assign(origStage._vMainCharacters.begin(),origStage._vMainCharacters.end());
	this->_vEntitiesDef = origStage._vEntitiesDef;
}

StageModel& StageModel::operator=(const StageModel &origStage){
	this->name(origStage.name());
	this->height(origStage.height());
	this->width(origStage.width());
	this->tileWidth(origStage.tileWidth());
	this->tileHeight(origStage.tileHeight());
	this->_tilesMap = origStage._tilesMap;
	this->firstTile = origStage.firstTile;
	this->_vMainCharacters.assign(origStage._vMainCharacters.begin(),origStage._vMainCharacters.end());
	this->_vEntitiesDef = origStage._vEntitiesDef;
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

//map <KeyPair, EntityObject*>* StageModel::entityMap() {
//	return _entityMap;
//}

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
	KeyPair k;
	k.first = x;
	k.second = y;
	TileModel* tile = _tilesMap->at(k);
	if ( (tile->getOtherEntity()) || (tile->getRelatedTile()))
		return 0;
	return 1;
}

void StageModel::initialize(unsigned int dimentionX, unsigned int dimentionY, unsigned int tHeight, unsigned int tWidth){
	width(dimentionX);
	height(dimentionY);
	tileWidth(tWidth);
	tileHeight(tHeight);
}

pair<int,int> StageModel::pixelToTileCoordinatesInStage(pair<int,int> pixelCoordinates, float cameraX, float cameraY) {
	float tileX = 0;
	float tileY = 0;
	float aux = static_cast<float>(pixelCoordinates.first + cameraX)/2;

	tileX = floor(static_cast<float>((pixelCoordinates.second + cameraY + aux) / this->tileHeight()));

	tileY = floor(static_cast<float>((pixelCoordinates.second + cameraY - aux) / this->tileHeight()));

	return std::make_pair<int,int>(static_cast<int>(tileX),static_cast<int>(tileY));
}

pair<int,int> StageModel::pixelToTileCoordinates(std::pair<int,int> pixelCoordinates) {

	return pixelToTileCoordinatesInStage(pixelCoordinates,0,0);
}

bool StageModel::isInsideWorld(pair<int,int> tileCoordinates) {
	return ( (tileCoordinates.first >= 0) && (tileCoordinates.first < static_cast<int>(this->width())) && (tileCoordinates.second >= 0) && (tileCoordinates.second < static_cast<int>(this->height())) );
}

void StageModel::destino(int x,int y,float cameraX,float cameraY){
	std::pair<int,int> pixelCoordinates;
	pixelCoordinates.first = x;
	pixelCoordinates.second = y;
	std::pair<int,int> destino = pixelToTileCoordinatesInStage(pixelCoordinates,cameraX,cameraY);

	if((isInsideWorld(destino))) 
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
	_vEntitiesDef.clear();
	this->deleteMap();

}

void StageModel::generateMap(){
	unsigned currentLevel = 0;
	KeyPair tilePos;
	tilePos.first = 0;
	tilePos.second = 0;
	unsigned levels = max(this->_width, this->_height) - 1;
	_tilesMap = new map <KeyPair, TileModel*>();
	TileModel* currentTile  = new TileModel();
	TileModel* prevTile;
	firstTile = currentTile;
	firstTile->setPosition(tilePos);
	_tilesMap->insert(make_pair(tilePos, firstTile));
	currentLevel++;
	if (levels == (this->_width - 1) ){
		while ( currentLevel <= levels ) {
			tilePos.first = currentLevel;
			tilePos.second = 0;
			while (( tilePos.second <= currentLevel )&& (tilePos.second <= (this->_height -1)) ){
				prevTile = currentTile;
				currentTile  = new TileModel();
				currentTile->setPosition(tilePos);
				prevTile->setNextTile(currentTile);
				_tilesMap->insert(make_pair(tilePos, currentTile));
				tilePos.first--;
				tilePos.second++;
			} //when exit level complete
			currentLevel++;
		}
		levels = (this->_height -1);
		currentLevel = 1;
		while ( currentLevel <= levels ){
			tilePos.first = (this->_width - 1); //currentLevel
			tilePos.second = currentLevel;
			while ( tilePos.second <= levels ){
				prevTile = currentTile;
				currentTile  = new TileModel();
				currentTile->setPosition(tilePos);
				prevTile->setNextTile(currentTile);
				_tilesMap->insert(make_pair(tilePos, currentTile));
				tilePos.first--;
				tilePos.second++;
			} //when exit level complete
			currentLevel++;
		}
	} else { //height > width
		while ( currentLevel <= levels ){
			tilePos.first = 0;
			tilePos.second = currentLevel;
			while ( (tilePos.first <= currentLevel) && (tilePos.first <= (this->_width -1)) ){
				prevTile = currentTile;
				currentTile  = new TileModel();
				currentTile->setPosition(tilePos);
				prevTile->setNextTile(currentTile);
				_tilesMap->insert(make_pair(tilePos, currentTile));
				tilePos.second--;
				tilePos.first++;
			} //when exit level complete
			currentLevel++;
		}
		levels = (this->_width -1);
		currentLevel = 1;
		while ( currentLevel <= levels ){
			tilePos.first = currentLevel;
			tilePos.second = (this->_height -1);
			while ( tilePos.first <= levels ){
				prevTile = currentTile;
				currentTile  = new TileModel();
				currentTile->setPosition(tilePos);
				prevTile->setNextTile(currentTile);
				_tilesMap->insert(make_pair(tilePos, currentTile));
				tilePos.first++;
				tilePos.second--;
			} //when exit level complete
			currentLevel++;
		}
	}
}

void StageModel::deleteMap(){
	TileModel* aux = this->firstTile;
	TileModel* nextAux;
	while (aux){
		nextAux = aux;
		aux = nextAux->getNextTile();
		delete nextAux;
	}
	if (_tilesMap){
		_tilesMap->clear();
		delete _tilesMap;
	}
}

void StageModel::loadByDefault(EntityObject* e){
	TileModel* aux = this->firstTile;
	while (aux){
		if (aux->getGroundEntity() == NULL)
			aux->setGroundEntity(e);
		aux = aux->getNextTile();
	}
}

void StageModel::resolveRelatedTiles(TileModel* tile){
	EntityObject* entity = tile->getOtherEntity();
	if ( (entity) && ( (entity->baseWidth() > 1) || (entity->baseHeight() > 1) ) ){
		markRelatedTiles(tile);

	}
}

void StageModel::markRelatedTiles(TileModel* tile){ //TODO:falta testear con baseHeight > baseWidth
	EntityObject* entity = tile->getOtherEntity();
	unsigned currentLevel = 0;
	KeyPair tilePos, refTilePos;
	refTilePos = tile->getPosition();
	tilePos.first = refTilePos.first + (entity->baseWidth() - 1);
	tilePos.second = refTilePos.second + (entity->baseHeight() - 1);
	TileModel* prevTile  = tile;
	TileModel* currentTile = _tilesMap->at(tilePos);
	currentTile->setRelatedTile(tile);
	currentTile->setUndrawable();
	unsigned levels = max(entity->baseWidth(), entity->baseHeight()) - 1;
	currentTile  = tile;
	currentLevel++;
	if (levels == (entity->baseWidth() - 1) ){
		while ( currentLevel <= levels ) {
			tilePos.first = refTilePos.first + currentLevel;
			tilePos.second = refTilePos.second;
			while ( tilePos.second <= (refTilePos.second + currentLevel) ) {
				prevTile = currentTile;
				currentTile  = _tilesMap->at(tilePos);
				currentTile->setUndrawable();
				prevTile->setRelatedTile(currentTile);
				tilePos.first--;
				tilePos.second++;
			} 
			currentLevel++;
		}
		levels = (entity->baseHeight() -1);
		currentLevel = 1;
		while ( currentLevel <= levels ){
			tilePos.first = refTilePos.first + (entity->baseWidth() -1);
			tilePos.second = refTilePos.second + currentLevel;
			while ( tilePos.second <= (refTilePos.second +levels) ){
				prevTile = currentTile;
				currentTile  = _tilesMap->at(tilePos);
				currentTile->setUndrawable();
				prevTile->setRelatedTile(currentTile);
				tilePos.first--;
				tilePos.second++;
			} 
			currentLevel++;
		}
	} else { //height > width TODO: falta testear
		while ( currentLevel <= levels ){
			tilePos.first = refTilePos.first;
			tilePos.second = refTilePos.second + currentLevel;
			while (tilePos.first <= (refTilePos.first + currentLevel)){
				prevTile = currentTile;
				currentTile  = _tilesMap->at(tilePos);
				currentTile->setUndrawable();
				prevTile->setRelatedTile(currentTile);
				tilePos.second--;
				tilePos.first++;
			} 
			currentLevel++;
		}
		levels = (entity->baseWidth() -1);
		currentLevel = 1;
		while ( currentLevel <= levels ){
			tilePos.first = refTilePos.first + currentLevel;
			tilePos.second = refTilePos.second + (entity->baseHeight() - 1 );
			while ( tilePos.first <= (refTilePos.first + currentLevel) ){
				prevTile = currentTile;
				currentTile  = _tilesMap->at(tilePos);
				currentTile->setUndrawable();
				prevTile->setRelatedTile(currentTile);
				tilePos.first++;
				tilePos.second--;
			}
			currentLevel++;
		}
	}
}

void StageModel::insertEntity(KeyPair k, EntityObject* e){
	TileModel* tile = _tilesMap->at(k);
	tile->addEntity(e);
	resolveRelatedTiles(tile);
}

TileModel* StageModel::getFirstTile(){
	return this->firstTile;
}

unsigned max (unsigned a, unsigned b ) {
	unsigned result = a;
	if ( b > a )
		result = b;
	return result;
}

bool StageModel::isThereAChar(string & name,int x,int y,float cameraX,float cameraY)
{
	std::pair<int,int> pixelCoordinates;
	pixelCoordinates.first =x;
	pixelCoordinates.second =y;
	std::pair<int,int> tilePos=pixelToTileCoordinatesInStage(pixelCoordinates,cameraX,cameraY);
	if(isInsideWorld(tilePos))
	{
		for(int i=0;i<_vMainCharacters.size();i++)
		{
			std::pair<int,int> posChar;
			_vMainCharacters[i]->getCurrent(posChar);
			if(posChar==tilePos)
			{
				name=_vMainCharacters[i]->getName();
				return true;
			}
		}
	}
	return false;
}