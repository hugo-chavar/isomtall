#include "Stage.h"


using namespace std;
using namespace model;


//info del escenario
unsigned int Stage::width(){
	return _width;
}

unsigned int Stage::height(){
	Logger::instance().setFile("hola.log");
	return _height;
}

void Stage::height(unsigned int value){
	_height = value;
}

void Stage::width(unsigned int value){
	_width = value;
}

//info de los tiles
unsigned int Stage::tileWidth(){
	return _tileWidth;
}

unsigned int Stage::tileHeight(){
	return _tileHeight;
}

void Stage::tileHeight(unsigned int value){
	_tileHeight = value;
}

void Stage::tileWidth(unsigned int value){
	_tileWidth = value;
}

void Stage::addTile(unsigned int x, unsigned int y, Tile* tile) {
	Key position(x,y);
	scene.insert(make_pair(position, tile)); //se podria chequear errores aca.. que no vengan repetidas las posiciones
}

void Stage::initialize(unsigned int dimentionX, unsigned int dimentionY, unsigned int tHeight, unsigned int tWidth){
	width(dimentionX);
	height(dimentionY);
	tileWidth(tWidth);
	tileHeight(tHeight);
}

void Stage::update(){

}
