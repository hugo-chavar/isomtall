#include "Stage.h"
#include "Surface.h"
#include "EntityObject.h"
#include "DataTypes.h"
#include "TileModel.h"
#include "GameView.h"
#include "ItemFactoryView.h"
#include "Arrow.h"
#include "Grenade.h"
#include "Bomb.h"
#include "Logger.h"

#define START_LEVEL 0
#define EXTRA_TILES_TO_RENDER 9

view::Stage::Stage() {
	spriteArray.clear();
	this->worldModel = NULL;
	this->firstTile = NULL;
}

view::Stage::~Stage() {
	Logger::instance().log("view::Stage::~Stage()");
	this->cleanUp();
}

void view::Stage::cleanUp() {
	for (unsigned int i = 0; i < this->spriteArray.size(); i++) {
		delete this->spriteArray[i];
	}
	//for (unsigned int i = 0; i < this->ammunitions.size(); i++) {
	//	delete this->ammunitions[i];
	//}
	this->spriteArray.clear();
	this->ammunitions.clear();
	this->deleteStage();
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
	} else if(GameView::instance().isSinglePlayerGame()){
		ItemFactoryView factory;
		ItemView* item=factory.generateRandomItem(Game::instance().world()->itemsPercentage(),HIDDEN_ITEM,tile->getPosition(),true);//Harcodeo porcentaje de items
		if(item)
			{
				//Logger::instance().log("Item " + item->getName()+" "+ stringUtilities::pairIntToString(tile->getPosition()) );
				itemsArray.push_back(item);
				tile->setOtherEntity(item);
			}	
			
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
	//Arrow* arrow = new Arrow();
	//Grenade* grenade = new Grenade();
	//Bomb* bomb = new Bomb();
	//arrow->setInitialTile(make_pair(15,6));
	//arrow->initialize();
	//arrow->setDirection(Directionable::DIRECTION_S);
	//arrow->setVelocity(20);
	//this->ammunitions.push_back(arrow);
	//arrow = new Arrow();
	//arrow->setInitialTile(make_pair(15,6));
	//arrow->initialize();
	//arrow->setDirection(Directionable::DIRECTION_N);
	//arrow->setVelocity(20);
	//this->ammunitions.push_back(arrow);
	//arrow = new Arrow();
	//arrow->setInitialTile(make_pair(15,6));
	//arrow->initialize();
	//arrow->setDirection(Directionable::DIRECTION_NO);
	//arrow->setVelocity(20);
	//grenade->setInitialTile(make_pair(15,7));
	//grenade->initialize();
	//grenade->setDirection(Directionable::DIRECTION_NO);
	//grenade->setVelocity(20);
	//this->ammunitions.push_back(arrow);
	//this->ammunitions.push_back(grenade);
	//arrow = new Arrow();
	//arrow->setInitialTile(make_pair(15,6));
	//arrow->initialize();
	//arrow->setDirection(Directionable::DIRECTION_NE);
	//arrow->setVelocity(20);
	//this->ammunitions.push_back(arrow);
	//arrow = new Arrow();
	//arrow->setInitialTile(make_pair(15,6));
	//arrow->initialize();
	//arrow->setDirection(Directionable::DIRECTION_E);
	//arrow->setVelocity(20);
	//this->ammunitions.push_back(arrow);
	//arrow = new Arrow();
	//arrow->setInitialTile(make_pair(15,6));
	//arrow->initialize();
	//arrow->setDirection(Directionable::DIRECTION_O);
	//arrow->setVelocity(20);
	//this->ammunitions.push_back(arrow);
	//arrow = new Arrow();
	//arrow->setInitialTile(make_pair(15,6));
	//arrow->initialize();
	//arrow->setDirection(Directionable::DIRECTION_SO);
	//arrow->setVelocity(20);
	//this->ammunitions.push_back(arrow);
	//arrow = new Arrow();
	//arrow->setInitialTile(make_pair(15,6));
	//arrow->initialize();
	//arrow->setDirection(Directionable::DIRECTION_SE);
	//arrow->setVelocity(20);
	//this->ammunitions.push_back(arrow);
}

void view::Stage::setTilesInCamera(int w, int h) {
	unsigned horizontalTilesInCamera = static_cast<unsigned>(ceil(static_cast<float>(w) / DEFAULT_TILE_WIDTH));
	unsigned verticalTilesInCamera = static_cast<unsigned>(ceil(static_cast<float>(h) / DEFAULT_TILE_HEIGHT));
	minLevelsInCamera = horizontalTilesInCamera + verticalTilesInCamera;
}

bool view::Stage::initialize() {
	this->cleanUp();
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
	this->updateAmmunitions();

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
	pair<int,int> position = make_pair(static_cast<int>(camera.getOffsetX()),static_cast<int>(camera.getOffsetY()));
	pair<int,int> cameraReferenceTile = this->worldModel->pixelToTileCoordinates(position);
	cameraReferenceTile.second -= EXTRA_TILES_TO_RENDER;
	cameraReferenceTile.first -= EXTRA_TILES_TO_RENDER;
	pair<int,int> leftBottom = this->worldModel->pixelToTileCoordinatesInStage(make_pair(0,camera.getHeight()), camera.getOffsetX(), camera.getOffsetY());
	pair<int,int> rightBottom = this->worldModel->pixelToTileCoordinatesInStage(make_pair(camera.getWidth(),camera.getHeight()), camera.getOffsetX(), camera.getOffsetY());
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
			if (p->isActive() && renderHelper.shouldRenderThis(p->personajeModelo()->getPosition(),p->getPosition()))
				p->render(camera);
			p = GameView::instance().nextCharacter();
		}

		for (unsigned i = 0 ; i < this->ammunitions.size(); i++) {
			if (this->ammunitions[i]->getName() == "Bomb") {

				if (renderHelper.shouldRenderThis(((Bomb*)this->ammunitions[i])->getPosition(),((Bomb*)this->ammunitions[i])->getPosition()))
					this->ammunitions[i]->render(camera);
			} else {
				if (renderHelper.shouldRenderThis(((Movable*)this->ammunitions[i])->getCurrentTile(),((Movable*)this->ammunitions[i])->getLastTile()))
					this->ammunitions[i]->render(camera);

			}
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
	tileLevels.clear();
	itemsArray.clear();
}

bool Stage::addOtherEntity(pair <int,int> position, string entityName) {
	if (mapEntityToSprite.find(entityName) == mapEntityToSprite.end())
		return false;
	Sprite* entitySprite = spriteArray[mapEntityToSprite.at(entityName)];
	Entity* entity = new Entity(position.first, position.second, entitySprite);
	this->getTileAt(position)->setOtherEntity(entity);
	return true;
}

void Stage::removeOtherEntity(pair <int,int> tile) {
	delete(this->getTileAt(tile)->getOtherEntity());
	this->getTileAt(tile)->setOtherEntity(NULL);
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
		spriteArray[i]->updateFrame();
	}
}

StageModel* Stage::getWorldModel() {
	return this->worldModel;
}

void Stage::initItemsFromString(std::string ItemsData)
{
	if(ItemsData.size()==0)
		return;
	std::vector <std::string> v_items;
	stringUtilities::splitString(ItemsData,v_items,';');
	unsigned i=0;
	itemsArray.clear();
	ItemFactoryView factory;
	//TODO: andy: puse este if porque pinchaba acá..
	//if (v_items.size() < 3)
	//	return;
	while(i<v_items.size())
	{
		string itemName=v_items[i];
		i++;
		unsigned state=stringUtilities::stringToUnsigned(v_items[i]);
		i++;
		string tile=v_items[i];
		i++;
		pair<int,int> pos=stringUtilities::stringToPairInt(tile);
		//Sprite* itemSprite= spriteArray[ mapEntityToSprite.at(itemName)];//Deberia chequear que exista el item
		//Sprite* chestSprite= spriteArray[ mapEntityToSprite.at("Chest")];
		Sprite* itemSprite= this->getSpriteWithName(itemName);//Deberia chequear que exista el item
		Sprite* chestSprite= this->getSpriteWithName("Chest");
		if ((itemSprite != NULL) && (chestSprite != NULL) ) {

			ItemView* item=factory.createItem(itemSprite,chestSprite,state,pos,itemName);
			if(pos.first!=-1)
				this->getTileAt(pos)->setOtherEntity(item);
			itemsArray.push_back(item);
		}
	}
}

void Stage::updateItems(string serializedItemUpdates)
{
	if(serializedItemUpdates.size()<1)
		return;
	std::vector <string> updateVector;
	stringUtilities::splitString(serializedItemUpdates,updateVector,':');
	for(unsigned i=0;i<updateVector.size();i++)
	{
		this->updateItem(updateVector[i]);
	}
}

void Stage::updateItem(string serializedItemUpdate)
{
	std::vector <string> updateVector;
	stringUtilities::splitString(serializedItemUpdate,updateVector,';');
	unsigned state=stringUtilities::stringToUnsigned(updateVector[0]);
	pair<int,int> pos=stringUtilities::stringToPairInt(updateVector[2]);
	switch (state){
	case UNCOVER_ITEM:
		{
			ItemView* item=(ItemView*)this->getTileAt(pos)->getOtherEntity();
			if (item == NULL)
				break;
			item->uncover();
		}
	break;
	case DEATH_ITEM:
		{
			ItemView* item=(ItemView*)this->getTileAt(pos)->getOtherEntity();
			if (item == NULL)
				break;
			item->kill();
			this->getTileAt(pos)->setOtherEntity(NULL);
		}
	break;
	default://Si hay que revivir
	{
		ItemView* item=this->findDeathItem(updateVector[1]);//paso nombre
		if(item)
		{
			item->revive(state,pos);
			this->getTileAt(pos)->setOtherEntity(item);
		}
	}
	break;
	};
}

ItemView* Stage::findDeathItem(string name)
{
	for(unsigned i=0;i<this->itemsArray.size();i++)
	{
		if(itemsArray[i]->getName()==name)
		{	
			if(!itemsArray[i]->isAlive())
				return itemsArray[i];
		}
	}
	return NULL;
}

ItemView* Stage::findDeathItemSinglePlayer()
{
	for(unsigned i=this->itemsArray.size();i>0;i--)
	{
		if(!itemsArray[i-1]->isAlive() && !(itemsArray[i-1]->getCanReviveForHimself()))
			{
				int random=rand()%itemsArray.size();
				std::swap(itemsArray[i-1],itemsArray[random]);
				return itemsArray[random];
			}
	}
	return NULL;
}

Sprite* Stage::getSpriteWithName(string value) {
    bool found = false;
    map<string, int>::iterator it = mapEntityToSprite.begin();
    while(it != mapEntityToSprite.end())
    {
        found = (it->first == value);
        if(found)
            break;
        ++it;
    }
	if (found) {
		int posSprite = mapEntityToSprite.at(value);
		Sprite* auxSprite = spriteArray[posSprite];
		return auxSprite;
	} 
	return NULL;
}

void Stage::updateSinglePlayer()
{
	this->updateItemsSinglePlayer();
	this->updateSprites();
	this->updateTiles();
	this->updateAmmunitions();
}

void Stage::updateItemsSinglePlayer()
{
	for(unsigned i=0;i<this->itemsArray.size();i++)
	{
		itemsArray[i]->updateSinglePlayer();
	}
}

void Stage::updateItems()
{
	for(unsigned i=0;i<this->itemsArray.size();i++)
	{
		itemsArray[i]->update();
	}
}

ItemView* Stage::getItemInTile(int posX,int posY)
{
	for(unsigned i=0;i<this->itemsArray.size();i++)
	{
		if(itemsArray[i]->getPosition() == std::make_pair(posX, posY))
			if(itemsArray[i]->isHidden()&&itemsArray[i]->isAlive())
				return this->itemsArray[i];
	}
	return NULL;
}

void Stage::relocateItem(pair<int,int>pos)
{
	ItemView* item=this->findDeathItemSinglePlayer();
	if(item)
	{
		item->revive(REVIVE_UNCOVER_ITEM,pos);
		this->getTileAt(pos)->setOtherEntity(item);
	}
}

void Stage::updateAmmunitions() {
	vector<Entity*>::iterator it;
	it = ammunitions.begin();
	while ( it != ammunitions.end()) {
		if ((*it)->isAlive()) {
			(*it)->update();
			it++;
		} else {
			ammunitions.erase(it); //TODO: testear esto
		}
	}
	//for (unsigned i = 0 ; i < this->ammunitions.size(); i++) {

	//	this->ammunitions[i]->update();
	//}
}

void Stage::addAmmunition(Entity * ammo) {
	this->ammunitions.push_back(ammo);
}