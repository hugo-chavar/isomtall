#ifndef _STAGEMODEL_H_
#define _STAGEMODEL_H_

#include <map>
#include <vector>
#include <iostream>
#include <utility>
#include "DataTypes.h"
#include "PersonajeModelo.h"
#include "TileModel.h"

using namespace std;


class StageModel {

public:
	StageModel();
	StageModel(string name, unsigned int width, unsigned int height, vector <EntityDef> vEntitiesDef, vector <PersonajeModelo*> vMainCharacters): //, map <KeyPair, EntityObject*> *entityMap
	_name(name), _width(width), _height(height), _vEntitiesDef(vEntitiesDef),  _vMainCharacters(vMainCharacters) { _tileWidth = DEFAULT_TILE_WIDTH; _tileHeight = DEFAULT_TILE_HEIGHT; firstTile = NULL; this->_tilesMap = NULL; }; //_entityMap(entityMap),
	StageModel(const StageModel&);
	StageModel& operator=(const StageModel&);
	unsigned int width() const; 
	unsigned int height() const;
	string name() const; 
	vector <EntityDef> vEntitiesDef();
	vector <PersonajeModelo*>* vMainCharacters(); 
	//map <KeyPair, EntityObject*> *entityMap();
	void width(unsigned int); 
	void height(unsigned int);
	void name(string);
	unsigned int tileWidth() const; 
	unsigned int tileHeight() const;
	void tileWidth(unsigned int);
	void tileHeight(unsigned int);
	//void addTile(unsigned int, unsigned int, Tile*);
	unsigned int cost(unsigned int, unsigned int);
	void initialize(unsigned int dimentionX, unsigned int dimentionY, unsigned int tileHeight, unsigned int tileWidth);
	std::pair<int,int> pixelToTileCoordinatesInStage(std::pair<int,int> pixelCoordinates,float cameraX,float cameraY);
	std::pair<int,int> pixelToTileCoordinates(std::pair<int,int> pixelCoordinates);
	bool isInsideWorld(std::pair<int,int> tileCoordinates);
	void destino(int x,int y,float cameraX,float cameraY);

	float mainCharacter_speed() const;
	void mainCharacter_speed(float value);
	PersonajeModelo* modelMainCharacters(unsigned);
	void insertMainCharacter(PersonajeModelo*);
	void clearStage();
	void generateMap();
	void deleteMap();
	void loadByDefault(EntityObject*);
	void insertEntity(KeyPair k, EntityObject* e);
private:
	string _name;
	unsigned int _width;
	unsigned int _height;
	unsigned int _tileWidth;
	unsigned int _tileHeight;
	vector <EntityDef> _vEntitiesDef;
	//map <KeyPair, EntityObject*> *_entityMap;

	map <KeyPair, TileModel*> *_tilesMap;
	TileModel* firstTile;
	//float _mainCharacter_speed;

	vector <PersonajeModelo*> _vMainCharacters;
};

#endif //_STAGEMODEL_H_