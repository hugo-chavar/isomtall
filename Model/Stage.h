#ifndef _STAGE_H_
#define _STAGE_H_

#include <map>
#include <vector>
#include <iostream>
#include <utility>
#include "DataTypes.h"
#include "MainCharacter.h"

using namespace std;

namespace model{
class Stage {

public:
	Stage();
	Stage(string name, unsigned int width, unsigned int height, vector <EntityDef> vEntitiesDef, map <KeyPair, EntityObject*> *entityMap, vector <MainCharacter> vMainCharacters): 
		_name(name), _width(width), _height(height), _vEntitiesDef(vEntitiesDef), _entityMap(entityMap), _vMainCharacters(vMainCharacters) { _tileWidth = DEFAULT_TILE_WIDTH; _tileHeight = DEFAULT_TILE_HEIGHT; };
	unsigned int width(); 
	unsigned int height();
	string name(); 
	vector <EntityDef> vEntitiesDef();
	vector <MainCharacter> vMainCharacters(); 
	map <KeyPair, EntityObject*> *entityMap();
	void width(unsigned int); 
	void height(unsigned int);
	unsigned int tileWidth(); 
	unsigned int tileHeight();
	void tileWidth(unsigned int);
	//void setEntities(vector<> v);
	void tileHeight(unsigned int);
	//void addTile(unsigned int, unsigned int, Tile*);
	unsigned int cost(unsigned int, unsigned int);
	void initialize(unsigned int dimentionX, unsigned int dimentionY, unsigned int tileHeight, unsigned int tileWidth);
	//void update();
	std::pair<int,int> pixelToTileCoordinatesInStage(std::pair<int,int> pixelCoordinates,float cameraX,float cameraY);
	std::pair<int,int> pixelToTileCoordinates(std::pair<int,int> pixelCoordinates);
	bool isInsideWorld(std::pair<int,int> tileCoordinates);
	void destino(int x,int y,float cameraX,float cameraY);

	int mainCharacter_speed();
	void mainCharacter_speed(int value);
private:
	string _name;
	unsigned int _width;
	unsigned int _height;
	unsigned int _tileWidth;
	unsigned int _tileHeight;
	vector <EntityDef> _vEntitiesDef;
	map <KeyPair, EntityObject*> *_entityMap;
	vector <MainCharacter> _vMainCharacters;
	int _mainCharacter_speed;


	// map <KeyPair, *Tile> scene;

	//para insertar (no testeado) en scene un tile en la pos x=12, y=20:
	//Key clave(12,20);
	//scene.insert(std::make_pair(clave, &unTile));
};
}

#endif //_STAGE_H_