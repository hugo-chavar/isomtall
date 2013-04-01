#include "World.h"

#include "Surface.h"

using namespace view;

//desde aca todos los metodos fueron pasados al modelo en la clase Stage (Hugo)
model::World::World() {
	this->dimentionX = 0;
	this->dimentionY = 0;
	this->tileHeight = 0;
	this->tileWidth = 0;
}

unsigned int model::World::getDimentionX() { //reemplazado por unsigned int width();
	return this->dimentionX;
}

unsigned int model::World::getDimentionY() { //reemplazado por height()
	return this->dimentionY;
}

void model::World::setDimentionX(unsigned int dimentionX) {
	this->dimentionX = dimentionX;
}

void model::World::setDimentionY(unsigned int dimentionY) {
	this->dimentionY = dimentionY;
}

unsigned int model::World::getTileWidth() {
	return this->tileWidth;
}

void model::World::setTileWidth(unsigned int tileWidth) {
	this->tileWidth = tileWidth;
}

unsigned int model::World::getTileHeight() {
	return this->tileHeight;
}

void model::World::setTileHeight(unsigned int tileHeight) {
	this->tileHeight = tileHeight;
}

std::vector<model::Tile*>& model::World::getTileArray() {
	return this->tileArray;
}

void model::World::addTile(Tile* tile) {
	this->getTileArray().push_back(tile);
}

void model::World::initialize(unsigned int dimentionX, unsigned int dimentionY, unsigned int tileWidth, unsigned int tileHeight) {
	this->setDimentionX(dimentionX);
	this->setDimentionY(dimentionY);
	this->setTileWidth(tileWidth);
	this->setTileHeight(tileHeight);
}

void model::World::update() {
}

//el metodo que sigue va a la vista (Hugo), en el modelo no se debe mencionar la palabra pixel
//para dejar mas limpio el codigo reemplazar "std::pair<int,int>" por Key haciendo el siguiente include
//#include "..\Common\DataTypes.h", luego si no alcanza la funcionalidad se hace una clase Key
std::pair<int,int> model::World::tileToPixelCoordinates(std::pair<int,int> tileCoordinates) {
	int pixelX;
	int pixelY;

	pixelX = ((this->getDimentionX() + tileCoordinates.first - tileCoordinates.second) * this->getTileWidth()) / 2;

	pixelY = ((1 + tileCoordinates.first + tileCoordinates.second) * this->getTileHeight()) / 2;

	return std::make_pair<int,int>(pixelX,pixelY);
}

std::pair<int,int> model::World::pixelToTileCoordinates(std::pair<int,int> pixelCoordinates) {
	float a = 0;
	float b = 0;
	int c = 0;

	c = pixelCoordinates.first - ((this->getDimentionX() * this->getTileWidth()) / 2);
	a = (static_cast<float>(pixelCoordinates.second) / this->getTileHeight());
	b = (static_cast<float>(c) / this->getTileWidth());

	return std::make_pair<int,int>(a + b,a - b);
}

//me falta separar bien el tema de los tiles, con Andy nos reunimos a chequear esto
//porque asi como está, esta medio mezclado.. pero lo acomodaremos sin cambiar la funcionalidad
void model::World::cleanUp() {
	for (unsigned int i = 0; i < this->getTileArray().size(); i++) {
		this->getTileArray()[i]->cleanUp();
	}
}

model::World::~World() {
	for (unsigned int i = 0; i < this->getTileArray().size(); i++) {
		delete this->getTileArray()[i];
	}
}

//arranca el namespace view (lo de arriba a esta linea deberia ser eliminado completamente). Hugo
World::World() {
}

void World::render(model::Camera& camera) {
	//TODO: Fix this function.
	unsigned int horizontalTilesInCamera = ceil(static_cast<float>(camera.getWidth()) / worldModel.getTileWidth()) + 1;
	unsigned int verticalTilesInCamera = ceil(static_cast<float>(camera.getHeight()) / worldModel.getTileHeight()) + 1;
	std::pair<int,int> cameraReferenceTile = worldModel.pixelToTileCoordinates(std::make_pair(camera.getOffsetX(),camera.getOffsetY()));
	std::pair<int,int> cameraReferencePixel = worldModel.tileToPixelCoordinates(cameraReferenceTile);
	int Xt = 0;
	int Yt = 0;
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
				if ( (Xt >= 0) && (Xt < worldModel.getDimentionX()) && (Yt >= 0) && (Yt < worldModel.getDimentionY())) {
					index = Yt * worldModel.getDimentionX() + Xt;
					cameraReferencePixel = worldModel.tileToPixelCoordinates(std::make_pair<int,int>(Xt,Yt));
					cameraReferencePixel.first = cameraReferencePixel.first - camera.getOffsetX();
					cameraReferencePixel.second = cameraReferencePixel.second - camera.getOffsetY();
					Surface::draw(worldModel.getTileArray()[Yt * worldModel.getDimentionX() + Xt]->sdlSurface,0,0,worldModel.getTileHeight(),worldModel.getTileWidth(),camera.cameraSurface,cameraReferencePixel.first,cameraReferencePixel.second);
				}
				Xt++;
				Yt--;
			}
		}
	}
}

World::~World() {
}