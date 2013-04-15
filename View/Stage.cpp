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

void view::Stage::render(Camera& camera) {
	
	list<Entity*>::iterator iterador= entityList.begin();
	for (unsigned i=0;i<entityList.size();i++)
	{
						//if (i==1254) {
						//	i = 1254;
						//}
						(*iterador)->render(camera);
                        iterador++;
	}
}

view::Stage::~Stage() {
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

void view::Stage::addTile(TileView* tile) {
	this->getTileArray().push_back(tile);
}

bool view::Stage::initialize()
{
	
	//worldModel = Game::instance().world();
	//worldModel.initialize(100,100,62,31);//metodo harcodeado
	//Game::instance().world().initialize(100,100,32,64);//metodo harcodeado
	//EntityObject entity = Game::instance().vEntitiesObject()[1];
	//vector <EntityDef> vEntitiesDef = worldModel.vEntitiesDef();

	//carga de sprites estaticos
	unsigned staticEntitiesModelCount = Game::instance().allEntities.vEntitiesObject.size();
	
	for (unsigned a = 0; a < staticEntitiesModelCount; a++){
		EntityObject *entity = Game::instance().allEntities.vEntitiesObject[a];
		//enlazo Sprites con los nombres de las entidades estaticas en el modelo
		mapEntityToSprite[entity->name()] = int(a);
		//genero los Sprites (TODO: diferenciar animados de estaticos usando el constructor de Sprite adecuado)
		spriteArray.push_back(new Sprite(entity));
	}
	
	//carga de sprites animados
	unsigned animatedEntitiesModelCount = Game::instance().allEntities.vAnimatedEntities.size();

	for (unsigned a = 0; a < animatedEntitiesModelCount; a++){
		AnimatedEntity *entity = Game::instance().allEntities.vAnimatedEntities[a];
		//enlazo Sprites con los nombres de las entidades animadas en el modelo
		mapEntityToSprite[entity->name()] = int(a + staticEntitiesModelCount);
		//genero los Sprites (TODO: diferenciar animados de estaticos usando el constructor de Sprite adecuado)
		spriteArray.push_back(new Sprite(entity));
	}

	//Carga del piso x default
	unsigned posEntityDefault = mapEntityToSprite["DEFAULT"];
	unsigned w = Game::instance().world().width();
	unsigned h = Game::instance().world().height();
	for(unsigned i=0; i < w; i++){ //TODO: esta bien width() aca y height() en el for interno?
		for(unsigned j=0; j < h; j++){
			entityList.push_back(new Entity(int(i),int(j),spriteArray[posEntityDefault]));
		}
	}

	//genero entitades de la vista estaticas
	vector <EntityDef> vEntitiesDef = worldModel.vEntitiesDef();
	unsigned defCount = vEntitiesDef.size();
	int posSpriteEntity;
	staticEntitiesModelCount = 1; //solo para evitar errores
	for (unsigned a = 0; a < defCount; a++){

		posSpriteEntity = mapEntityToSprite[vEntitiesDef[a].entity];// find.. it.end()
		entityList.push_back(new Entity(vEntitiesDef[a].x,vEntitiesDef[a].y,spriteArray[posSpriteEntity]));

	}

	//inicia harcodeo
	AnimatedEntity* entity = Game::instance().animatedEntityAt(0); // Las animadas no vienen en vEntitiesDef porque el archivo de configuración no las especifica.
	if (entity){
		spriteArray.push_back(new Sprite(entity->imagePath(),entity->name(),23,entity->pixelRefX(),entity->pixelRefY(),entity->delay(),entity->fps()));
	}

	spriteArray.push_back(new Sprite("../Images/","piso",1,32,0,0,0));

	spriteArray.push_back(new Sprite("../Images/","cubo",1,32,40,0,0));
	spriteArray.push_back(new Sprite("../Images/","molino/molino",23,64,120,3000,15));

	
	if (!Game::instance().personaje()){
		//ver una maneta elegante de salir en todos los lugares que pincharia
		return false;
	}
	pj = new Personaje(Game::instance().personaje());
	
	//pj->setDestino(5,5);
	pj->agregarSprite(new Sprite("../Images/personajeCaballo/", "stoppedN", 1, 74, 80));
	pj->agregarSprite(new Sprite("../Images/personajeCaballo/", "stoppedNE", 1, 74, 80));
	pj->agregarSprite(new Sprite("../Images/personajeCaballo/", "stoppedNO", 1, 74, 80));
	pj->agregarSprite(new Sprite("../Images/personajeCaballo/", "stoppedS", 1, 74, 80));
	pj->agregarSprite(new Sprite("../Images/personajeCaballo/", "stoppedSE", 1,74, 80));
	pj->agregarSprite(new Sprite("../Images/personajeCaballo/", "stoppedSO", 1, 74, 80));
	pj->agregarSprite(new Sprite("../Images/personajeCaballo/", "stoppedE", 1, 74, 80));
	pj->agregarSprite(new Sprite("../Images/personajeCaballo/", "stoppedO", 1, 74, 80));
	pj->agregarSprite(new Sprite("../Images/personajeCaballo/8walkingN/", "walkingN", 12, 74, 80, 0, 30.0));
	pj->agregarSprite(new Sprite("../Images/personajeCaballo/9walkingNE/", "walkingNE", 12, 74, 80, 0, 30.0));
	pj->agregarSprite(new Sprite("../Images/personajeCaballo/10walkingNO/", "walkingNO", 12, 74, 80, 0, 30.0));
	pj->agregarSprite(new Sprite("../Images/personajeCaballo/11walkingS/", "walkingS", 12, 74, 80, 0, 30.0));
	pj->agregarSprite(new Sprite("../Images/personajeCaballo/12walkingSE/", "walkingSE", 12, 74, 80, 0, 30.0));
	pj->agregarSprite(new Sprite("../Images/personajeCaballo/13walkingSO/", "walkingSO", 12, 74, 80, 0, 30.0));
	pj->agregarSprite(new Sprite("../Images/personajeCaballo/14walkingE/", "walkingE", 12, 74, 80, 0, 30.0));
	pj->agregarSprite(new Sprite("../Images/personajeCaballo/15walkingO/", "walkingO",12, 74, 80, 0, 30.0));

	//Harcodeo la carga de entidades. debera venir del modelo
	for(int i=0;i<50;i++)
		for(int j=0; j<25;j++){
			entityList.push_back(new Entity(i,j,spriteArray[0]));
		}

	// entityList.push_back(new Entity(vEntitiesDef[0].x,vEntitiesDef[0].y,spriteArray[1])); Para entidades no animadas (vienen las posiciones en vEntitiesDev
	entityList.push_back(new Entity(3,2,spriteArray[1]));
	//entityList.push_back(new Entity(15,2,spriteArray[2]));
	//entityList.push_back(new Entity(15,5,spriteArray[2]));
	//entityList.push_back(new Entity(15,10,spriteArray[2]));vpj->agregarSprite(new Sprite("../Images/personaje/", "stoppedN", 1, 32, 40));
	entityList.push_back(pj);
	return true;
}

void view::Stage::update() {
	for(unsigned i=0;i<spriteArray.size();i++)
	{
		spriteArray[i]->actualizarFrame();
	}
	pj->update();
}

Personaje* view::Stage::personaje()
{
	return pj;
}