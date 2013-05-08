#include "Stage.h"
#include "Surface.h"
#include "EntityObject.h"
#include "DataTypes.h"
#include "TileModel.h"

#define START_LEVEL 0
#define EXTRA_TILES_TO_RENDER 10

view::Stage::Stage() {
	_personaje = NULL;
}

view::Stage::~Stage() {
	for (unsigned int i = 0; i < spriteArray.size(); i++)
	{
		delete spriteArray[i];
	}
	//for(unsigned j=0;j<entityList.size();j++)
	//{
	//	for (unsigned i=0;i<entityList[j].size();i++)
	//	{
	//		delete(entityList[j][i]);
	//	}
	//	entityList[j].clear();
	//}
	spriteArray.clear();
	//entityList.clear();
	if (_personaje){
		delete _personaje;
		_personaje = NULL;
	}
	deleteStage();
	
}

void view::Stage::loadSprites(){
	//carga de sprites estaticos
	unsigned staticEntitiesModelCount = Game::instance().allEntities.vEntitiesObject.size();
	for (unsigned a = 0; a < staticEntitiesModelCount; a++){
		EntityObject *entity = Game::instance().allEntities.vEntitiesObject[a];
		mapEntityToSprite[entity->name()] = int(a);
		spriteArray.push_back(new Sprite(entity));
	}
	//carga de sprites animados
	unsigned animatedEntitiesModelCount = Game::instance().allEntities.vAnimatedEntities.size();
	for (unsigned a = 0; a < animatedEntitiesModelCount; a++){
		AnimatedEntity *entity = Game::instance().allEntities.vAnimatedEntities[a];
		mapEntityToSprite[entity->name()] = int(a + staticEntitiesModelCount);
		spriteArray.push_back(new SpriteAnimado(entity));
	}
}

TileView* view::Stage::createTile(TileModel* tileModel){
	TileView* tile = new TileView(tileModel);
	int posSpriteEntity = mapEntityToSprite.at(tile->getGroundEntityName());
	tile->createGround(spriteArray[posSpriteEntity]);
	if (tile->hasOtherEntity()){
		posSpriteEntity = mapEntityToSprite.at(tile->getOtherEntityName());
		tile->createOtherEntity(spriteArray[posSpriteEntity]);
	}
	tilesMap.insert(make_pair(tile->getPosition(), tile));
	return tile;
}

void view::Stage::generateStage(){
	TileModel* tileModel = worldModel->getFirstTile();
	this->firstTile = this->createTile(tileModel);
	tileLevels.push_back(this->firstTile);
	TileView* currentTile;
	TileView* prevTile = this->firstTile;
	KeyPair tilePos;
	tileModel = tileModel->getNextTile();
	while (tileModel){
		currentTile = this->createTile(tileModel);
		if (prevTile->EOL())
			tileLevels.push_back(currentTile);
		prevTile->setNextTile(currentTile);
		prevTile = currentTile;
		tileModel = tileModel->getNextTile();
	}
	currentTile = this->firstTile;
	tileModel = worldModel->getFirstTile();
	while ((currentTile) && (tileModel)){
		if (tileModel->getRelatedTile()){
			tilePos = tileModel->getRelatedTile()->getPosition();
			prevTile = tilesMap.at(tilePos);
			currentTile->setRelatedTile(prevTile);
		}
		currentTile = currentTile->getNextTile();
		tileModel = tileModel->getNextTile();
	}
}

void view::Stage::setTilesInCamera(int w, int h){
	unsigned horizontalTilesInCamera = static_cast<unsigned>(ceil(static_cast<float>(w) / DEFAULT_TILE_WIDTH));
	unsigned verticalTilesInCamera = static_cast<unsigned>(ceil(static_cast<float>(h) / DEFAULT_TILE_HEIGHT));
	minLevelsInCamera = horizontalTilesInCamera + verticalTilesInCamera;
}

bool view::Stage::initialize(){
	worldModel = Game::instance().world();
	
	this->loadSprites();
	this->generateStage();

	if (!Game::instance().personaje()){
		return false;
	}
	_personaje = new Personaje(Game::instance().personaje());
	_personaje->loadSprites();

	return true;
}

void view::Stage::update() {
	//for(unsigned i=0;i<spriteArray.size();i++){
	//	spriteArray[i]->actualizarFrame();
	//}


	this->updateSprites();
	this->updateTiles();

	_personaje->update();

}

Personaje* view::Stage::personaje(){
	return _personaje;
}

TileView* view::Stage::getTileAt(KeyPair k){
	return tilesMap.at(k);
}

TileView* view::Stage::getFirstMatch(std::pair<int,int> k){
	TileView* aux = tileLevels.at(this->fixLevel(k));
	KeyPair position = aux->getPosition();
	while ((static_cast<int>(position.second) > k.second) && (aux)){
		aux = aux->getNextTile();
		if (aux)
			position = aux->getPosition();
	}
	return aux;
}

TileView* view::Stage::getLastMatch(TileView* firstMatch, std::pair<int,int> k){
	TileView* aux = firstMatch;
	KeyPair position = aux->getPosition();
	while ((static_cast<int>(position.first) <= k.first) && (!aux->EOL())){
		aux = aux->getNextTile();
		position = aux->getPosition();
	}
	return aux;
}

void view::Stage::fixKeyLeftBottom(int level, std::pair<int,int> &k){
	while (level < (k.first + k.second)){
			k.first--;
	}
}

void view::Stage::fixKeyRightBottom(int level, std::pair<int,int> &k){
	while (level < (k.first + k.second)){
			k.second--;
	}
}

int view::Stage::fixLevel(std::pair<int,int> k){
	int level = k.first + k.second;
	if (level > this->worldModel->maxLevels() ){
		level = this->worldModel->maxLevels();
	}
	else if (level < START_LEVEL )
		level = START_LEVEL;
	return level;
}

int view::Stage::fixStartLevel(int endLevel, std::pair<int,int> &ref){
	int level = this->fixLevel(ref);
	if (((endLevel - level) < minLevelsInCamera) && (level > START_LEVEL)){
		if ((endLevel - minLevelsInCamera) > START_LEVEL){
			ref.first -= minLevelsInCamera - (endLevel - level);
			level = this->fixLevel(ref);
		}else {
			level = START_LEVEL;
		}
	}

	return level;
}

void view::Stage::alignLevel(std::pair<int,int> &k1, std::pair<int,int> &k2){
	int level1 = this->fixLevel(k1);
	int level2 = this->fixLevel(k2);
	while (level1 > level2 ){
		k2.first++;
		level2 = this->fixLevel(k2);
	}
	while (level1 < level2 ){
		k2.second--;
		level2 = this->fixLevel(k2);
	}
}

 void view::Stage::calculateTilesToRender(Camera& camera){ 

	renderHelper.clear();
	std::pair<int,int> cameraReferenceTile = this->worldModel->pixelToTileCoordinates(std::make_pair(camera.getOffsetX(),camera.getOffsetY()));
	cameraReferenceTile.second -= EXTRA_TILES_TO_RENDER;
	cameraReferenceTile.first -= EXTRA_TILES_TO_RENDER;
	std::pair<int,int> leftBottom = this->worldModel->pixelToTileCoordinatesInStage(make_pair(0,camera.getHeight()), camera.getOffsetX(), camera.getOffsetY());
	std::pair<int,int> rightBottom = this->worldModel->pixelToTileCoordinatesInStage(make_pair(camera.getWidth(),camera.getHeight()), camera.getOffsetX(), camera.getOffsetY());
	leftBottom.second += EXTRA_TILES_TO_RENDER;
	rightBottom.first += EXTRA_TILES_TO_RENDER;
	int endLevel = this->fixLevel(leftBottom);
	this->fixKeyLeftBottom(endLevel, leftBottom);
	this->alignLevel(leftBottom, rightBottom );
	int startLevel = this->fixStartLevel(endLevel, cameraReferenceTile);
	renderHelper.setStartLevel(startLevel);
	renderHelper.setEndLevel(endLevel);
	while (renderHelper.incomplete()){
		TileView* firstMatch = this->getFirstMatch(leftBottom);
		TileView* lastMatch;
		if (firstMatch){
			lastMatch = this->getLastMatch(firstMatch,rightBottom);
			renderHelper.addLevel(firstMatch,lastMatch);
		} else {
			renderHelper.setEmptyLevel();
		}

		if (renderHelper.flip()){
			leftBottom.first--;
			rightBottom.first--;
		} else {
			rightBottom.second--;
			leftBottom.second--;
		}
	}

}

void view::Stage::render(Camera& camera) {

	//list<std::pair<TileView*,TileView*>> l = calculateTilesToRender(camera);
	
	//std::list<std::pair<TileView*, TileView*>>::iterator it = l.begin();
	//TileView* tile;
	//for (; it != l.end(); it++){
	//	tile = (*it).first;
	//	while (tile != (*it).second ){
	//		tile->render(camera);
	//		tile = tile->getNextTile();
	//	}
	//	tile->render(camera);
	//}
	

	this->calculateTilesToRender(camera);
	renderHelper.renderGround(camera);
	renderHelper.startRenderingEntities();
	while (renderHelper.hasLevelsToRender()){
		renderHelper.renderNextLevel(camera);
		if (renderHelper.shouldRenderThis(_personaje->getPosicionEnTiles(),_personaje->getPosicionAnteriorEnTiles()))
			_personaje->render(camera);
	}
	
}

void Stage::deleteStage() {
	TileView* aux = this->firstTile;
	TileView* nextAux;
	while (aux) {
		nextAux = aux;
		aux = nextAux->getNextTile();
		delete nextAux;
	}
	tilesMap.clear();
}


void Stage::updateTiles() {
	TileView* aux = this->firstTile;
	TileView* nextAux;
	while (aux) {
		aux->update();
		aux = aux->getNextTile();
	}
}

void Stage::updateSprites() {
	for (unsigned i = 0 ; i < spriteArray.size(); i++) {
		spriteArray[i]->actualizarFrame();
	}
}