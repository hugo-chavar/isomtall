#include "Stage.h"
#include "Surface.h"
#include "EntityObject.h"
#include "DataTypes.h"
#include "TileModel.h"
#include "GameView.h"
#include "ItemFactoryView.h"

#define START_LEVEL 0
#define EXTRA_TILES_TO_RENDER 9

view::Stage::Stage() {
//	_personaje = NULL;
}

view::Stage::~Stage() {
	for (unsigned int i = 0; i < spriteArray.size(); i++) {
		delete spriteArray[i];
	}

	spriteArray.clear();
	//if (_personaje){
	//	delete _personaje;
	//	_personaje = NULL;
	//}
	deleteStage();
}

void view::Stage::loadSprites() {
	//carga de sprites estaticos
	Sprite* auxSprite;
	unsigned staticEntitiesModelCount = Game::instance().allEntities.vEntitiesObject.size();
	for (unsigned a = 0; a < staticEntitiesModelCount; a++){
		EntityObject *entity = Game::instance().allEntities.vEntitiesObject[a];
		mapEntityToSprite[entity->name()] = int(a);
		auxSprite = new Sprite(entity);
		//auxSprite->initialize();
		spriteArray.push_back(auxSprite);
		auxSprite = NULL;
	}
	//carga de sprites animados
	SpriteAnimado* auxAnimatedSprite;
	unsigned animatedEntitiesModelCount = Game::instance().allEntities.vAnimatedEntities.size();
	for (unsigned a = 0; a < animatedEntitiesModelCount; a++){
		AnimatedEntity *entity = Game::instance().allEntities.vAnimatedEntities[a];
		mapEntityToSprite[entity->name()] = int(a + staticEntitiesModelCount);
		auxAnimatedSprite = new SpriteAnimado(entity);
		//auxAnimatedSprite->initialize();
		spriteArray.push_back(auxAnimatedSprite);
		auxAnimatedSprite = NULL;
	}
}

TileView* view::Stage::createTile(TileModel* tileModel) {
	TileView* tile = new TileView(tileModel);
	int posSpriteEntity = mapEntityToSprite.at(tile->getGroundEntityName());
	tile->createGround(spriteArray[posSpriteEntity]);
	if (tile->hasOtherEntity()) {
		posSpriteEntity = mapEntityToSprite.at(tile->getOtherEntityName());
		tile->createOtherEntity(spriteArray[posSpriteEntity]);
	}
	tilesMap.insert(make_pair(tile->getPosition(), tile));
	return tile;
}

void view::Stage::generateStage() {
	TileModel* tileModel = worldModel->getFirstTile();
	this->firstTile = this->createTile(tileModel);
	tileLevels.push_back(this->firstTile);
	TileView* currentTile;
	TileView* prevTile = this->firstTile;
	KeyPair tilePos;
	tileModel = tileModel->getNextTile();
	while (tileModel) {
		currentTile = this->createTile(tileModel);
		if (prevTile->EOL())
			tileLevels.push_back(currentTile);
		prevTile->setNextTile(currentTile);
		prevTile = currentTile;
		tileModel = tileModel->getNextTile();
	}
	currentTile = this->firstTile;
	tileModel = worldModel->getFirstTile();
	while ((currentTile) && (tileModel)) {
		if (tileModel->getRelatedTile()) {
			tilePos = tileModel->getRelatedTile()->getPosition();
			prevTile = tilesMap.at(tilePos);
			currentTile->setRelatedTile(prevTile);
		}
		currentTile = currentTile->getNextTile();
		tileModel = tileModel->getNextTile();
	}
}

void view::Stage::setTilesInCamera(int w, int h) {
	unsigned horizontalTilesInCamera = static_cast<unsigned>(ceil(static_cast<float>(w) / DEFAULT_TILE_WIDTH));
	unsigned verticalTilesInCamera = static_cast<unsigned>(ceil(static_cast<float>(h) / DEFAULT_TILE_HEIGHT));
	minLevelsInCamera = horizontalTilesInCamera + verticalTilesInCamera;
}

bool view::Stage::initialize() {
	worldModel = Game::instance().world();
	
	this->loadSprites();
	this->generateStage();

	//if (!Game::instance().personaje()){
	//	return false;
	//}
	//_personaje = new Personaje(Game::instance().personaje());
	//GameView::instance().addPersonaje(Game::instance().personaje()->getName(),_personaje);
	//_personaje->loadSprites();

	return true;
}

void view::Stage::update() {
	this->updateSprites();
	this->updateTiles();
	//this->regenerateItem();
	//_personaje->update(); //llamar en algun lado.. despues
}
//
//Personaje* view::Stage::personaje() {
//	return _personaje;
//}

TileView* view::Stage::getTileAt(KeyPair k) {
	return tilesMap.at(k);
}

TileView* view::Stage::getFirstMatch(std::pair<int,int> k) {
	TileView* aux = tileLevels.at(this->fixLevel(k));
	KeyPair position = aux->getPosition();
	while ((static_cast<int>(position.second) > k.second) && (aux)) {
		aux = aux->getNextTile();
		if (aux)
			position = aux->getPosition();
	}
	return aux;
}

TileView* view::Stage::getLastMatch(TileView* firstMatch, std::pair<int,int> k) {
	TileView* aux = firstMatch;
	KeyPair position = aux->getPosition();
	while ((static_cast<int>(position.first) <= k.first) && (!aux->EOL())) {
		aux = aux->getNextTile();
		position = aux->getPosition();
	}
	return aux;
}

void view::Stage::fixKeyLeftBottom(int level, std::pair<int,int> &k) {
	while (level < (k.first + k.second)) {
			k.first--;
	}
}

void view::Stage::fixKeyRightBottom(int level, std::pair<int,int> &k) {
	while (level < (k.first + k.second)) {
			k.second--;
	}
}

int view::Stage::fixLevel(std::pair<int,int> k) {
	int level = k.first + k.second;
	if (level > this->worldModel->maxLevels() ) {
		level = this->worldModel->maxLevels();
	}
	else if (level < START_LEVEL )
		level = START_LEVEL;
	return level;
}

int view::Stage::fixStartLevel(int endLevel, std::pair<int,int> &ref) {
	int level = this->fixLevel(ref);
	if (((endLevel - level) < minLevelsInCamera) && (level > START_LEVEL)) {
		if ((endLevel - minLevelsInCamera) > START_LEVEL) {
			ref.first -= minLevelsInCamera - (endLevel - level);
			level = this->fixLevel(ref);
		} else {
			level = START_LEVEL;
		}
	}
	return level;
}

void view::Stage::alignLevel(std::pair<int,int> &k1, std::pair<int,int> &k2) {
	int level1 = this->fixLevel(k1);
	int level2 = this->fixLevel(k2);
	while (level1 > level2 )  {
		k2.first++;
		level2 = this->fixLevel(k2);
	}
	while (level1 < level2 ) {
		k2.second--;
		level2 = this->fixLevel(k2);
	}
}

 void view::Stage::calculateTilesToRender(Camera& camera) { 
	renderHelper.clear();
	std::pair<int,int> position = std::make_pair(static_cast<int>(camera.getOffsetX()),static_cast<int>(camera.getOffsetY()));
	std::pair<int,int> cameraReferenceTile = this->worldModel->pixelToTileCoordinates(position);
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
	while (renderHelper.incomplete()) {
		TileView* firstMatch = this->getFirstMatch(leftBottom);
		TileView* lastMatch;
		if (firstMatch) {
			lastMatch = this->getLastMatch(firstMatch,rightBottom);
			renderHelper.addLevel(firstMatch,lastMatch);
		} else {
			renderHelper.setEmptyLevel();
		}

		if (renderHelper.flip()) {
			leftBottom.first--;
			rightBottom.first--;
		} else {
			rightBottom.second--;
			leftBottom.second--;
		}
	}
}

void view::Stage::render(Camera& camera) {
	this->calculateTilesToRender(camera);
	renderHelper.renderGround(camera);
	renderHelper.startRenderingEntities();
	while (renderHelper.hasLevelsToRender()) {
		renderHelper.renderNextLevel(camera);
		GameView::instance().startRenderingCharacters();
		Personaje* p = GameView::instance().nextCharacter();
		while (p) {
			if (p->isActive() && renderHelper.shouldRenderThis(p->getPosicionEnTiles(),p->getPosicionAnteriorEnTiles()))
				p->render(camera);
			p = GameView::instance().nextCharacter();
		}

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

StageModel* Stage::getWorldModel() {
	return this->worldModel;
}

void Stage::initItemsFromString(std::string ItemsData)
{
	std::vector <std::string> v_items;
	stringUtilities::splitString(ItemsData,v_items,';');
	int i=0;
	itemArray.clear();
	ItemFactoryView factory;
	while(i<v_items.size())
	{
		string itemName=v_items[i];
		i++;
		string isHidden=v_items[i];
		i++;
		string tile=v_items[i];
		i++;
		pair<int,int> pos=stringUtilities::stringToPairInt(tile);
		Sprite* itemSprite= spriteArray[ mapEntityToSprite.at(itemName)];//Deberia chequear que exista el item
		Sprite* chestSprite= spriteArray[ mapEntityToSprite.at("Chest")];
		ItemView* item=factory.createItem(itemSprite,chestSprite,isHidden,pos);
		this->getTileAt(pos)->setOtherEntity(item);
		itemArray.push_back(item);
	}
}
