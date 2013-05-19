#include "StageModel.h"
#include "Game.h"
#include "stringUtilities.h"
#include "Constants.h"

using namespace std;

StageModel::StageModel(){
	this->_tilesMap = NULL;
	this->firstTile = NULL;
	_vMainCharacters.clear();
	_vEntitiesDef.clear();
	tileLevels.clear();
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
	this->tileLevels.assign(origStage.tileLevels.begin(),origStage.tileLevels.end());
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
	this->tileLevels.assign(origStage.tileLevels.begin(),origStage.tileLevels.end());
	return *this;
}

string StageModel::name() const {
	return _name;
}

unsigned int StageModel::width() const {
	return _width;
}

unsigned int StageModel::height() const {
	return _height;
}

void StageModel::height(unsigned int value) {
	_height = value;
}

void StageModel::width(unsigned int value) {
	_width = value;
}

vector <EntityDef> StageModel::vEntitiesDef() {
	return _vEntitiesDef;
}

vector <PersonajeModelo*>* StageModel::vMainCharacters() {
	return &_vMainCharacters;
}

unsigned int StageModel::tileWidth() const {
	return _tileWidth;
}

unsigned int StageModel::tileHeight() const {
	return _tileHeight;
}

void StageModel::tileHeight(unsigned int value) {
	_tileHeight = value;
}

void StageModel::tileWidth(unsigned int value) {
	_tileWidth = value;
}

void StageModel::name(string value) {
	_name = value;
}

unsigned int StageModel::cost(unsigned int x, unsigned int y) {
	TileModel* tile = _tilesMap->at(make_pair(x,y));
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

pair<int,int> StageModel::pixelToTileCoordinates(pair<int,int> pixelCoordinates) {

	return pixelToTileCoordinatesInStage(pixelCoordinates,0,0);
}

bool StageModel::isInsideWorld(pair<int,int> tileCoordinates) {
	return ( (tileCoordinates.first >= 0) && (tileCoordinates.first < static_cast<int>(this->width())) && (tileCoordinates.second >= 0) && (tileCoordinates.second < static_cast<int>(this->height())) );
}

//Unir mas tarde

//void StageModel::destino(int x,int y,float cameraX,float cameraY){
//	pair<int,int> destino = pixelToTileCoordinatesInStage(make_pair(x,y), cameraX, cameraY);
//	if(isInsideWorld(destino)) 
//		Game::instance().personaje()->setDestino(destino.first,destino.second);
//}

pair<int, int> StageModel::destination(int x,int y,float cameraX,float cameraY) {
	pair<int,int> destino = pixelToTileCoordinatesInStage(make_pair(x,y), cameraX, cameraY);
	return destino;
}
//Unir mas tarde

//void StageModel::insertMainCharacter(PersonajeModelo* pm){
//	_vMainCharacters.push_back(pm);
//}

//PersonajeModelo* StageModel::modelMainCharacters(unsigned pos){
//	if (_vMainCharacters.size() > pos)
//		return _vMainCharacters[pos];
//	return NULL;
//}

void StageModel::clearStage(){
	for (unsigned j=0; j < (this->_vMainCharacters.size()); j++)
			delete _vMainCharacters[j];
	_vMainCharacters.clear();
	_vEntitiesDef.clear();
	this->deleteMap();
}

int StageModel::maxLevels(){
	return tileLevels.size() -1;
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
	if ( (entity) && ((entity->baseWidth() > 1) || (entity->baseHeight() > 1)) ){
		this->markRelatedTiles(tile);
		//if  ((entity->baseWidth() > 2) || (entity->baseHeight() > 2))
		//	this->resolveBolckedEntities(tile);
	}
}

void StageModel::generateMap() {
	KeyPair tilePos;
	tilePos.first = 0;
	tilePos.second = 0;
	_tilesMap = new map <KeyPair, TileModel*>();
	TileModel* currentTile  = new TileModel();
	TileModel* prevTile;
	firstTile = currentTile;
	tileLevels.push_back(firstTile);
	firstTile->setEOL();
	firstTile->setPosition(tilePos);
	_tilesMap->insert(make_pair(tilePos, firstTile));
	unsigned currentLevel = 1;
	unsigned levels = this->_width + this->_height - 2;
	while ( currentLevel <= levels ){
		if (currentLevel < this->_height){
			tilePos.first = 0;
			tilePos.second = currentLevel;
		} else {
			tilePos.second = (this->_height -1);
			tilePos.first = (currentLevel - tilePos.second);
		}
		while ( (tilePos.first <= currentLevel) && (tilePos.first <= (this->_width -1)) ){
			prevTile = currentTile;
			currentTile  = new TileModel();
			currentTile->setPosition(tilePos);
			prevTile->setNextTile(currentTile);
			if (prevTile->EOL()){
				tileLevels.push_back(currentTile);
			}
			_tilesMap->insert(make_pair(tilePos, currentTile));
			tilePos.second--;
			tilePos.first++;
		} //when exit level complete
		currentTile->setEOL();
		currentLevel++;
	}
}

void StageModel::markRelatedTiles(TileModel* tile) {
	bool hasCenter = false;
	EntityObject* entity = tile->getOtherEntity();
	KeyPair tilePos, centerTilePos, refTilePos;
	refTilePos = tile->getPosition();
	tilePos.first = refTilePos.first + (entity->baseWidth() - 1);
	tilePos.second = refTilePos.second + (entity->baseHeight() - 1);
	centerTilePos.first = refTilePos.first  + (static_cast<unsigned>(ceil(static_cast<float>(entity->baseWidth() - 1) / 2)));
	centerTilePos.second = refTilePos.second  + (static_cast<unsigned>(ceil(static_cast<float>(entity->baseHeight() - 1) / 2)));
	TileModel* centerTile = _tilesMap->at(centerTilePos);
	TileModel* prevTile  = tile;
	TileModel* currentTile = _tilesMap->at(tilePos);
	if ( centerTile != currentTile){
		currentTile->setRelatedTile(centerTile);
		//centerTile->setRelatedTile(tile);
		hasCenter = true;
	} 
	centerTile->setRelatedTile(tile);
	//TileModel* referenceTile = currentTile;
	tile->setUndrawable();

	//TileModel* referenceTile = tile; //currentTile;
	//currentTile->setUndrawable(); //tile
	//tile->setRelatedTile(currentTile); //testing
	unsigned levels = entity->baseWidth() + entity->baseHeight() - 2;
	currentTile  = tile;
	unsigned currentLevel = 1;
	while ( currentLevel <= levels ){
		if (currentLevel < static_cast<unsigned>(entity->baseHeight())) {
			tilePos.first = refTilePos.first;
			tilePos.second = refTilePos.second + currentLevel;
		} else {
			tilePos.second = refTilePos.second + (entity->baseHeight() - 1 );
			tilePos.first = refTilePos.first + currentLevel - (entity->baseHeight() - 1 );
		}
		while ( (tilePos.first <= (refTilePos.first + currentLevel)) && (tilePos.first <= (refTilePos.first + entity->baseWidth() -1)) ){
			prevTile = currentTile;
			currentTile  = _tilesMap->at(tilePos);
			if ( (!hasCenter) || (currentTile != centerTile)) {
				currentTile->setUndrawable();
				prevTile->setRelatedTile(currentTile);
			} else {
				currentTile = prevTile;
			}
			tilePos.second--;
			tilePos.first++;
		} //when exit level complete
		currentLevel++;
	}
	//referenceTile->setDrawable();
	centerTile->setDrawable();
}

void StageModel::insertEntity(KeyPair k, EntityObject* e) {
	TileModel* tile = _tilesMap->at(k);
	tile->addEntity(e);
	resolveRelatedTiles(tile);
}

TileModel* StageModel::getTileAt(KeyPair k) {
	return _tilesMap->at(k);
}

TileModel* StageModel::getFirstTile() {
	return this->firstTile;
}

bool StageModel::isThereAChar(string & name,int x,int y,float cameraX,float cameraY) {
	pair<int,int> pixelCoordinates;
	pixelCoordinates.first = x;
	pixelCoordinates.second = y;
	pair<int,int> tilePos = pixelToTileCoordinatesInStage(pixelCoordinates,cameraX,cameraY);
	if(isInsideWorld(tilePos))
	{
		for(unsigned i = 0; i < _vMainCharacters.size(); i++)
		{
			pair<int,int> posChar = _vMainCharacters[i]->getPosition();
			//_vMainCharacters[i]->getCurrent(posChar);
			if(posChar == tilePos)
			{
				name = _vMainCharacters[i]->getName();
				return true;
			}
		}
	}
	return false;
}

void StageModel::setSize(unsigned w, unsigned h) {
	this->height(h);
	if (w > MAX_STAGE_SIZE_X)
		this->width(MAX_STAGE_SIZE_X);
	else
		this->width(w);

}

void StageModel::loadNamedChars() {
	vector <PersonajeModelo*>::iterator it = _vMainCharacters.begin();
	for (; it != _vMainCharacters.end(); it++ ) {
		mapMainCharacters.insert(make_pair((*it)->getName(), (*it)));
	}
}

PersonajeModelo* StageModel::getCharacter(string name) {
	PersonajeModelo* character = NULL;
	map <string,PersonajeModelo*>::iterator it;
	it = mapMainCharacters.find(name);
	if(it != mapMainCharacters.end()) {
		character = it->second;
	} else {
		it = mapMainCharacters.find("DEFAULT");
		if(it != mapMainCharacters.end()) {
			character = it->second;
		}
	}
	return character;
}
