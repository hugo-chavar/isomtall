#include "World.h"

#include "Surface.h"
#include "EntityObject.h"
#include "DataTypes.h"

using namespace view;
using namespace model;

std::vector<TileView*>& World::getTileArray() {
	return this->tileArray;
}


std::pair<int,int> World::tileToPixelCoordinates(std::pair<int,int> tileCoordinates) {
	int pixelX;
	int pixelY;

	pixelX = ((worldModel.width()  + tileCoordinates.first - tileCoordinates.second) * worldModel.tileWidth()) / 2;

	pixelY = ((1 + tileCoordinates.first + tileCoordinates.second) * worldModel.tileHeight()) / 2;

	return std::make_pair<int,int>(pixelX,pixelY);
}

std::pair<int,int> World::pixelToTileCoordinates(std::pair<int,int> pixelCoordinates) {
	float a = 0;
	float b = 0;
	int c = 0;

	c = pixelCoordinates.first - ((worldModel.width() * worldModel.tileWidth()) / 2);
	a = (static_cast<float>(pixelCoordinates.second) / worldModel.tileHeight());
	b = (static_cast<float>(c) / worldModel.tileWidth());

	return std::make_pair<int,int>(int(a + b),int(a - b));
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


World::World() {
}

void World::render(Camera& camera) {
	
	list<Entity*>::iterator iterador= entityList.begin();
	for (unsigned i=0;i<entityList.size();i++)
	{
						(*iterador)->render(camera);
                        iterador++;
	}
}

World::~World() {
		for (unsigned int i = 0; i < spriteArray.size(); i++)
	{
		delete spriteArray[i];
	}

	list<Entity*>::iterator iterador= entityList.begin();
	for (unsigned i=0;i<entityList.size();i++)
	{
						delete(*iterador);
                        iterador++;
	}
}

void World::addTile(TileView* tile) {
	this->getTileArray().push_back(tile);
}

void World::initialize()
{
	
	worldModel = Game::instance().world();
	worldModel.initialize(100,100,62,31);//metodo harcodeado

	//EntityObject entity = Game::instance().vEntitiesObject()[1];
	//vector <EntityDef> vEntitiesDef = worldModel.vEntitiesDef();

	AnimatedEntity entity = Game::instance().vAnimatedEntities()[0]; // Las animadas no vienen en vEntitiesDef porque el archivo de configuración no las especifica.
	

	spriteArray.push_back(new Sprite("../Images/","piso",1,32,0,0,0));
	spriteArray.push_back(new Sprite(entity.imagesPaths(),entity.pixelRefX(),entity.pixelRefY(),entity.delay(),entity.fps()));
	spriteArray.push_back(new Sprite("../Images/","cubo",1,32,40,0,0));
	spriteArray.push_back(new Sprite("../Images/","molino/molino",23,64,120,3000,15));

	//Harcodeo la carga de entidades. debera venir del modelo
	for(int i=0;i<50;i++)
		for(int j=0; j<25;j++){
			entityList.push_back(new Entity(i,j,spriteArray[0]));
		}

	// entityList.push_back(new Entity(vEntitiesDef[0].x,vEntitiesDef[0].y,spriteArray[1])); Para entidades no animadas (vienen las posiciones en vEntitiesDev
	entityList.push_back(new Entity(3,2,spriteArray[1]));
	entityList.push_back(new Entity(15,2,spriteArray[3]));
	entityList.push_back(new Entity(15,5,spriteArray[3]));
	entityList.push_back(new Entity(15,10,spriteArray[3]));

}

void view::World::update() {
	for(unsigned i=0;i<spriteArray.size();i++)
	{
		spriteArray[i]->actualizarFrame();
	}
}