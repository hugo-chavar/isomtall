#include "Stage.h"

#include "Surface.h"
#include "EntityObject.h"
#include "DataTypes.h"

std::vector<TileView*>& view::Stage::getTileArray() {
	return this->tileArray;
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
	}
	_personaje->clearSprites();
	delete _personaje;
}

void view::Stage::addTile(TileView* tile) {
	this->getTileArray().push_back(tile);
}

bool view::Stage::initialize()
{
	worldModel = Game::instance().world();
	//carga de sprites estaticos
	unsigned staticEntitiesModelCount = Game::instance().allEntities.vEntitiesObject.size();
	
	for (unsigned a = 0; a < staticEntitiesModelCount; a++){
		EntityObject *entity = Game::instance().allEntities.vEntitiesObject[a];
		//enlazo Sprites con los nombres de las entidades estaticas en el modelo
		mapEntityToSprite[entity->name()] = int(a);
		//genero los Sprites
		spriteArray.push_back(new Sprite(entity));
	}
	
	//carga de sprites animados
	unsigned animatedEntitiesModelCount = Game::instance().allEntities.vAnimatedEntities.size();

	for (unsigned a = 0; a < animatedEntitiesModelCount; a++){
		AnimatedEntity *entity = Game::instance().allEntities.vAnimatedEntities[a];
		//enlazo Sprites con los nombres de las entidades animadas en el modelo
		mapEntityToSprite[entity->name()] = int(a + staticEntitiesModelCount);
		//genero los Sprites
		spriteArray.push_back(new Sprite(entity));
	}

	entityList.resize(worldModel.width()*worldModel.height());
	
	//Carga del piso x default
	unsigned posEntityDefault = mapEntityToSprite["DEFAULT"];
	unsigned w = Game::instance().world().width();
	unsigned h = Game::instance().world().height();

	for(unsigned i=0; i < w; i++){ 
		for(unsigned j=0; j < h; j++){
			entityList[i+j*worldModel.width()].push_back(new Entity(int(i),int(j),spriteArray[posEntityDefault]));
		}
	}

	//genero entidades de la vista estaticas
	vector <EntityDef> vEntitiesDef = worldModel.vEntitiesDef();
	unsigned defCount = vEntitiesDef.size();
	int posSpriteEntity;
	for (unsigned a = 0; a < defCount; a++){
		posSpriteEntity = mapEntityToSprite[vEntitiesDef[a].entity];// find.. it.end()
		entityList[vEntitiesDef[a].x+vEntitiesDef[a].y*worldModel.width()].push_back(new Entity(vEntitiesDef[a].x,vEntitiesDef[a].y,spriteArray[posSpriteEntity]));

	}

	if (!Game::instance().personaje()){
		//ver una maneta elegante de salir en todos los lugares que pincharia
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
	std::pair<int,int> cameraReferenceTile = this->worldModel.pixelToTileCoordinates(std::make_pair(camera.getOffsetX(),camera.getOffsetY()));
	int Xt = 0;
	int Yt = 0;

	//Crappy way to avoid not drawing partial tiles
	cameraReferenceTile.first -= 10;
	horizontalTilesInCamera += 10;
	verticalTilesInCamera += 10;
	for(unsigned int l = 0; l < 5; l++)//Harcodeo un maximo de 5 entidades por Tile
	{
		for (unsigned int i = 0; i < verticalTilesInCamera; i++) {
			Xt = cameraReferenceTile.first + i;
			Yt = cameraReferenceTile.second + i;

			for (unsigned int j = 0; j < horizontalTilesInCamera; j++) {
				int indice=Xt+Yt*worldModel.width();

				if (this->worldModel.isInsideWorld(std::make_pair<int,int>(Xt,Yt)))
				//if((Xt>=0)&&(Yt>=0)&&(Xt<worldModel.width())&&(Yt<worldModel.height()))
				{	
					if(l<entityList[indice].size())
						entityList[indice][l]->render(camera);	
				}
				indice++;
				if (this->worldModel.isInsideWorld(std::make_pair<int,int>(Xt + 1,Yt)))
				//if((Xt+1>=0)&&(Yt>=0)&&(Xt+1<worldModel.width())&&(Yt<worldModel.height()))
				{
					if(l<entityList[indice].size())
						entityList[indice][l]->render(camera);
				}
				Xt++;
				Yt--;
			}
		}
	}
	_personaje->render(camera);
}