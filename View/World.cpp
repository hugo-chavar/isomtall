#include "World.h"

#include "Surface.h"

using namespace view;

//desde aca todos los metodos fueron pasados al modelo en la clase Stage (Hugo)
//model::World::World() {
//	this->dimentionX = 0;
//	this->dimentionY = 0;
//	this->tileHeight = 0;
//	this->tileWidth = 0;
//}
//
//unsigned int model::World::getDimentionX() { //reemplazado por unsigned int width();
//	return this->dimentionX;
//}
//
//unsigned int model::World::getDimentionY() { //reemplazado por height()
//	return this->dimentionY;
//}
//
//void model::World::setDimentionX(unsigned int dimentionX) {
//	this->dimentionX = dimentionX;
//}
//
//void model::World::setDimentionY(unsigned int dimentionY) {
//	this->dimentionY = dimentionY;
//}
//
//unsigned int model::World::getTileWidth() {
//	return this->tileWidth;
//}
//
//void model::World::setTileWidth(unsigned int tileWidth) {
//	this->tileWidth = tileWidth;
//}
//
//unsigned int model::World::getTileHeight() {
//	return this->tileHeight;
//}
//
//void model::World::setTileHeight(unsigned int tileHeight) {
//	this->tileHeight = tileHeight;
//}

//void model::World::addTile(Tile* tile) {
//	this->getTileArray().push_back(tile);
//}
//
//void model::World::initialize(unsigned int dimentionX, unsigned int dimentionY, unsigned int tileWidth, unsigned int tileHeight) {
//	this->setDimentionX(dimentionX);
//	this->setDimentionY(dimentionY);
//	this->setTileWidth(tileWidth);
//	this->setTileHeight(tileHeight);
//}
//
//void model::World::update() {
//}


std::vector<TileView*>& view::World::getTileArray() {
	return this->tileArray;
}


//para dejar mas limpio el codigo reemplazar "std::pair<int,int>" por Key haciendo el siguiente include
//#include "..\Common\DataTypes.h", luego si no alcanza la funcionalidad se hace una clase Key
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

//me falta separar bien el tema de los tiles, con Andy nos reunimos a chequear esto
//porque asi como está, esta medio mezclado.. pero lo acomodaremos sin cambiar la funcionalidad
//Ultimo momento, dejo comentado porque da error durante la adaptacion del modelo
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

//arranca el namespace view (lo de arriba a esta linea deberia ser eliminado completamente). Hugo
view::World::World() {
}

void view::World::render(model::Camera& camera) {
	//TODO: Fix this function.
	unsigned int horizontalTilesInCamera = unsigned(ceil(static_cast<float>(camera.getWidth()) / worldModel.tileWidth())) + 1;
	unsigned int verticalTilesInCamera = unsigned(ceil(static_cast<float>(camera.getHeight()) / worldModel.tileHeight())) + 1;
	std::pair<int,int> cameraReferenceTile = this->pixelToTileCoordinates(std::make_pair(camera.getOffsetX(),camera.getOffsetY()));
	std::pair<int,int> cameraReferencePixel = this->tileToPixelCoordinates(cameraReferenceTile);
	unsigned Xt = 0; //Xt era int, estoy eliminando warnings
	unsigned Yt = 0; //Yt era int, estoy eliminando warnings
	unsigned int index = 0;

	cameraReferenceTile.first--;
	cameraReferenceTile.second--;
	horizontalTilesInCamera++;
	verticalTilesInCamera++;

	for (unsigned int i = 0; i < verticalTilesInCamera * 2; i++) {
		Xt = cameraReferenceTile.first + i;
		Yt = cameraReferenceTile.second + i;
		for (unsigned int j = 0; j < 2; j++) {
			Xt = cameraReferenceTile.first + j;
			Yt = cameraReferenceTile.second + i;
			for (unsigned int k = 0; k < horizontalTilesInCamera; k++) {
				if ( (Xt >= 0) && (Xt < worldModel.width()) && (Yt >= 0) && (Yt < worldModel.width())) {
					index = Yt * worldModel.width() + Xt;
					cameraReferencePixel = this->tileToPixelCoordinates(std::make_pair<int,int>(Xt,Yt));
					cameraReferencePixel.first = cameraReferencePixel.first - camera.getOffsetX();
					cameraReferencePixel.second = cameraReferencePixel.second - camera.getOffsetY();
					Surface::draw(this->getTileArray()[Yt * worldModel.width() + Xt]->sdlSurface,0,0,worldModel.tileHeight(),worldModel.tileWidth(),camera.cameraSurface,cameraReferencePixel.first,cameraReferencePixel.second);
				}
				Xt++;
				Yt--;
			}
		}
	}
}

view::World::~World() {
}

void World::addTile(TileView* tile) {
	this->getTileArray().push_back(tile);
}