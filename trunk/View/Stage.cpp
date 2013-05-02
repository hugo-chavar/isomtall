#include "Stage.h"
#include "Surface.h"
#include "EntityObject.h"
#include "DataTypes.h"
#include "TileModel.h"

//std::vector<TileView*>& view::Stage::getTileArray() {
//	return this->tileArray;
//}

bool comparador (Entity* entity1, Entity* entity2) {
	if ((entity1->order()) < (entity2->order())) {
		return true;
	}
	return false;
}


//void model::World::cleanUp() {
//	for (unsigned int i = 0; i < this->getTileArray().size(); i++) {
//		this->getTileArray()[i]->cleanUp();
//	}
//}
//
//model::World::~World() {
//	for (unsigned int i = 0; i < this->getTileArray().size(); i++) {
//		delete this->getTileArray()[i];
//	}
//}


view::Stage::Stage() {
	_personaje = NULL;
}


view::Stage::~Stage() {
	for (unsigned int i = 0; i < spriteArray.size(); i++)
	{
		delete spriteArray[i];
	}

	for(unsigned j=0;j<entityList.size();j++)
	{
		for (unsigned i=0;i<entityList[j].size();i++)
		{
			delete(entityList[j][i]);
		}
		entityList[j].clear();
	}
	spriteArray.clear();
	entityList.clear();
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
	TileView* currentTile;
	TileView* prevTile = this->firstTile;
	KeyPair tilePos;
	while (tileModel){
		currentTile = this->createTile(tileModel);
		prevTile->setNextTile(currentTile);
		prevTile = currentTile;
		tileModel = tileModel->getNextTile();
	}
}

bool view::Stage::initialize(){
	worldModel = Game::instance().world();
	this->loadSprites();
	this->generateStage();

	entityList.resize((worldModel->width())*(worldModel->height()));
	
	//Carga del piso x default
	unsigned posEntityDefault = mapEntityToSprite.at("DEFAULT ENTITY OBJECT");
	unsigned w = (Game::instance().world())->width();
	unsigned h = (Game::instance().world())->height();

	for(unsigned i=0; i < w; i++){ 
		for(unsigned j=0; j < h; j++){
			entityList[i+j*(worldModel->width())].push_back(new Entity(int(i),int(j),spriteArray[posEntityDefault],-1));
		}
	}

	//genero entidades de la vista estaticas
	vector <EntityDef> vEntitiesDef = worldModel->vEntitiesDef();
	unsigned defCount = vEntitiesDef.size();
	int posSpriteEntity;
	for (unsigned a = 0; a < defCount; a++){
		posSpriteEntity = mapEntityToSprite[vEntitiesDef[a].entity];
		int baseh=spriteArray[posSpriteEntity]->baseHeight();
		int basew=spriteArray[posSpriteEntity]->baseWidth();
		int posArray= vEntitiesDef[a].x+(basew-1)+(vEntitiesDef[a].y+(baseh-1))*(worldModel->width());
		entityList[posArray].push_back(new Entity(vEntitiesDef[a].x,vEntitiesDef[a].y,spriteArray[posSpriteEntity],int(a)));

	}

	if (!Game::instance().personaje()){
		return false;
	}
	_personaje = new Personaje(Game::instance().personaje());
	_personaje->loadSprites();

	return true;
}

void view::Stage::update() {
	for(unsigned i=0;i<spriteArray.size();i++)
	{
		spriteArray[i]->actualizarFrame();
	}

	_personaje->update();

}

Personaje* view::Stage::personaje()
{
	return _personaje;
}

void view::Stage::render(Camera& camera) {

	unsigned int horizontalTilesInCamera = static_cast<unsigned>(ceil(static_cast<float>(camera.getWidth()) / DEFAULT_TILE_WIDTH));
	unsigned int verticalTilesInCamera = static_cast<unsigned>(ceil(static_cast<float>(camera.getHeight()) / DEFAULT_TILE_HEIGHT));
	std::pair<int,int> cameraReferenceTile = this->worldModel->pixelToTileCoordinates(std::make_pair(camera.getOffsetX(),camera.getOffsetY()));
	int Xt = 0;
	int Yt = 0;

	//Crappy way to avoid not drawing partial tiles
	cameraReferenceTile.first -= 10;
	horizontalTilesInCamera += 10;
	verticalTilesInCamera += 10;

	list<Entity*> ordenada;
	//Dibujo primero el piso por defecto
	for (unsigned int i = 0; i < verticalTilesInCamera; i++) {
			Xt = cameraReferenceTile.first + i;
			Yt = cameraReferenceTile.second + i;
			for (unsigned int j = 0; j < horizontalTilesInCamera; j++) {
	
				int indice=Xt+Yt*(worldModel->width());
				if (this->worldModel->isInsideWorld(std::make_pair<int,int>(Xt,Yt)))
				{
						entityList[indice][0]->render(camera);	
				}
				indice++;
				if (this->worldModel->isInsideWorld(std::make_pair<int,int>(Xt + 1,Yt)))
				{
						entityList[indice][0]->render(camera);
				}
				Xt++;
				Yt--;
			}
			}
	//Dibujo el resto de las entidades

	
		for (unsigned int i = 0; i < verticalTilesInCamera; i++) {
			Xt = cameraReferenceTile.first + i;
			Yt = cameraReferenceTile.second + i;
			for (unsigned int j = 0; j < horizontalTilesInCamera; j++) {
	
				int indice=Xt+Yt*(worldModel->width());
				if (this->worldModel->isInsideWorld(std::make_pair<int,int>(Xt,Yt)))
				{
				for(unsigned l=1;l<entityList[indice].size();l++)
				{
				//if((Xt>=0)&&(Yt>=0)&&(Xt<worldModel.width())&&(Yt<worldModel.height()))
						ordenada.push_back(entityList[indice][l]);	
				}
				}
				indice++;
				if (this->worldModel->isInsideWorld(std::make_pair<int,int>(Xt + 1,Yt)))
				{
				for(unsigned l=1;l<entityList[indice].size();l++)
				{
					//if((Xt+1>=0)&&(Yt>=0)&&(Xt+1<worldModel.width())&&(Yt<worldModel.height()))
						ordenada.push_back(entityList[indice][l]);
				}
				}
				Xt++;
				Yt--;
			}
		}
		list<Entity*>::iterator it;
		ordenada.sort(comparador);
		for(it=ordenada.begin();it!=ordenada.end();it++)
		{
			(*it)->render(camera);
		
		}
	_personaje->render(camera);
}

void Stage::deleteStage(){
	TileView* aux = this->firstTile;
	TileView* nextAux;
	while (aux){
		nextAux = aux;
		aux = nextAux->getNextTile();
		delete nextAux;
	}
	tilesMap.clear();
}