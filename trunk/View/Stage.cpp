#include "Stage.h"

#include "Surface.h"
#include "EntityObject.h"
#include "DataTypes.h"

std::vector<TileView*>& view::Stage::getTileArray() {
	return this->tileArray;
}


/*std::pair<int,int> view::Stage::tileToPixelCoordinates(std::pair<int,int> tileCoordinates) {
	int pixelX;
	int pixelY;

	pixelX = ((worldModel.width()  + tileCoordinates.first - tileCoordinates.second) * worldModel.tileWidth()) / 2;

	pixelY = ((1 + tileCoordinates.first + tileCoordinates.second) * worldModel.tileHeight()) / 2;

	return std::make_pair<int,int>(pixelX,pixelY);
}

std::pair<int,int> view::Stage::pixelToTileCoordinates(std::pair<int,int> pixelCoordinates) {
	float a = 0;
	float b = 0;
	int c = 0;

	c = pixelCoordinates.first - ((worldModel.width() * worldModel.tileWidth()) / 2);
	a = (static_cast<float>(pixelCoordinates.second) / worldModel.tileHeight());
	b = (static_cast<float>(c) / worldModel.tileWidth());

	return std::make_pair<int,int>(int(a + b),int(a - b));
}*/


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

	//inicia harcodeo
	//AnimatedEntity* entity = Game::instance().animatedEntityAt(0); // Las animadas no vienen en vEntitiesDef porque el archivo de configuración no las especifica.
	//if (entity){
	//	spriteArray.push_back(new Sprite(entity->imagePath(),entity->name(),23,entity->pixelRefX(),entity->pixelRefY(),entity->delay(),entity->fps()));
	//}

	//spriteArray.push_back(new Sprite("../Images/","piso",1,32,0,0,0));

	//spriteArray.push_back(new Sprite("../Images/","cubo",1,32,40,0,0));
	//spriteArray.push_back(new Sprite("../Images/","molino/molino",23,64,120,3000,15));

	

	
	//_personaje->setDestino(5,5);
	//_personaje->agregarSprite(new Sprite("../Images/personajeCaballo/", "stoppedN", 1, 74, 80));
	//_personaje->agregarSprite(new Sprite("../Images/personajeCaballo/", "stoppedNE", 1, 74, 80));
	//_personaje->agregarSprite(new Sprite("../Images/personajeCaballo/", "stoppedNO", 1, 74, 80));
	//_personaje->agregarSprite(new Sprite("../Images/personajeCaballo/", "stoppedS", 1, 74, 80));
	//_personaje->agregarSprite(new Sprite("../Images/personajeCaballo/", "stoppedSE", 1,74, 80));
	//_personaje->agregarSprite(new Sprite("../Images/personajeCaballo/", "stoppedSO", 1, 74, 80));
	//_personaje->agregarSprite(new Sprite("../Images/personajeCaballo/", "stoppedE", 1, 74, 80));
	//_personaje->agregarSprite(new Sprite("../Images/personajeCaballo/", "stoppedO", 1, 74, 80));
	//_personaje->agregarSprite(new Sprite("../Images/personajeCaballo/08walkingN/", "walkingN", 12, 74, 80, 0, 30.0));
	//_personaje->agregarSprite(new Sprite("../Images/personajeCaballo/09walkingNE/", "walkingNE", 12, 74, 80, 0, 30.0));
	//_personaje->agregarSprite(new Sprite("../Images/personajeCaballo/10walkingNO/", "walkingNO", 12, 74, 80, 0, 30.0));
	//_personaje->agregarSprite(new Sprite("../Images/personajeCaballo/11walkingS/", "walkingS", 12, 74, 80, 0, 30.0));
	//_personaje->agregarSprite(new Sprite("../Images/personajeCaballo/12walkingSE/", "walkingSE", 12, 74, 80, 0, 30.0));
	//_personaje->agregarSprite(new Sprite("../Images/personajeCaballo/13walkingSO/", "walkingSO", 12, 74, 80, 0, 30.0));
	//_personaje->agregarSprite(new Sprite("../Images/personajeCaballo/14walkingE/", "walkingE", 12, 74, 80, 0, 30.0));
	//_personaje->agregarSprite(new Sprite("../Images/personajeCaballo/15walkingO/", "walkingO",12, 74, 80, 0, 30.0));

	//Harcodeo la carga de entidades. debera venir del modelo

	/*entityList.resize(worldModel.width()*worldModel.height());
	for(int i=0;i<worldModel.width();i++)
		for(int j=0; j<worldModel.height();j++){
			entityList[i+j*worldModel.width()].push_back(new Entity(i,j,spriteArray[0]));
		}*/

	// entityList.push_back(new Entity(vEntitiesDef[0].x,vEntitiesDef[0].y,spriteArray[1])); Para entidades no animadas (vienen las posiciones en vEntitiesDev
	
		//entityList[3+2*worldModel.width()].push_back(new Entity(3,2,spriteArray[1]));
	//entityList.push_back(new Entity(15,2,spriteArray[2]));
	//entityList.push_back(new Entity(15,5,spriteArray[2]));
	//entityList.push_back(new Entity(15,10,spriteArray[2]));vpj->agregarSprite(new Sprite("../Images/personaje/", "stoppedN", 1, 32, 40));
	
	//Saco el personaje de la lista de entidades. Se dibuja aparte solo

	//std::pair<int,int> posicionPersonaje;
	//pj->personajeModelo()->getCurrent(posicionPersonaje);
	//entityList[posicionPersonaje.first+posicionPersonaje.second*worldModel.width()].push_back(pj);
	return true;
}

void view::Stage::update() {
	for(unsigned i=0;i<spriteArray.size();i++)
	{
		spriteArray[i]->actualizarFrame();
	}

	_personaje->update();
	/*std::pair<int,int> posicionAnterior;
	pj->personajeModelo()->getCurrent(posicionAnterior);*/
	
	//std::pair<int,int> posicionPersonaje;
	//pj->personajeModelo()->getCurrent(posicionPersonaje);
	//if(posicionPersonaje!=posicionAnterior)
	//{
	//	int indiceAnterior=posicionAnterior.first+posicionAnterior.second*worldModel.width();
	//	int indice=posicionPersonaje.first+posicionPersonaje.second*worldModel.width();
	//	entityList[indiceAnterior].erase(entityList[indiceAnterior].end()-1);
	//	entityList[indice].push_back(pj);
	//}

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


//void view::Stage::render(Camera& camera) {
//	
//	list<Entity*>::iterator iterador= entityList.begin();
//
//	for (unsigned i=0;i<entityList.size();i++)
//	{
//						//if (i==1254) {
//						//	i = 1254;
//						//}
//						(*iterador)->render(camera);
//                        iterador++;
//	}
//}