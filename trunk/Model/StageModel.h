#ifndef _STAGEMODEL_H_
#define _STAGEMODEL_H_

#include <map>
#include <list>
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
	StageModel(string name, vector <EntityDef> vEntitiesDef, vector <PersonajeModelo*> vMainCharacters): // unsigned int width, unsigned int height,
	_name(name), _vEntitiesDef(vEntitiesDef),  _vMainCharacters(vMainCharacters) { _tileWidth = DEFAULT_TILE_WIDTH; _tileHeight = DEFAULT_TILE_HEIGHT; firstTile = NULL; this->_tilesMap = NULL; }; //_width(width), _height(height), 
	StageModel(const StageModel&);
	StageModel& operator=(const StageModel&);
	unsigned int width() const; 
	unsigned int height() const;
	string name() const; 
	vector <EntityDef> vEntitiesDef();
	vector <PersonajeModelo*>* vMainCharacters(); 
	void width(unsigned); 
	void height(unsigned);
	void setSize(unsigned, unsigned);
	void name(string);
	unsigned int tileWidth() const; 
	unsigned int tileHeight() const;
	void tileWidth(unsigned int);
	void tileHeight(unsigned int);
	unsigned int cost(unsigned int, unsigned int);
	void initialize(unsigned int dimentionX, unsigned int dimentionY, unsigned int tileHeight, unsigned int tileWidth);
	pair<int,int> pixelToTileCoordinatesInStage(pair<int,int> pixelCoordinates,float cameraX,float cameraY);
	pair<int,int> pixelToTileCoordinates(pair<int,int> pixelCoordinates);
	bool isInsideWorld(pair<int,int> tileCoordinates);
	//Reemplazar luego una por otra
	void destino(int x,int y,float cameraX,float cameraY);
	std::pair<int, int> destination(int x,int y,float cameraX,float cameraY);
	//
	PersonajeModelo* modelMainCharacters(unsigned );
	TileModel* getFirstTile();
	void insertMainCharacter(PersonajeModelo* );
	void clearStage();
	void generateMap();
	int maxLevels();
	void deleteMap();
	void loadByDefault(EntityObject* );
	void insertEntity(KeyPair k, EntityObject* e);
	TileModel* getTileAt(KeyPair k);
	void markRelatedTiles(TileModel* );
	void resolveRelatedTiles(TileModel* );
	//void StageModel::resolveBolckedEntities(TileModel* tile);
	bool isThereAChar(string & name,int x,int y,float cameraX,float cameraY);
private:
	string _name;
	unsigned int _width;
	unsigned int _height;
	unsigned int _tileWidth;
	unsigned int _tileHeight;
	vector <EntityDef> _vEntitiesDef;
	map <KeyPair, TileModel*> *_tilesMap;
	TileModel* firstTile;
	vector <TileModel*> tileLevels;
	vector <PersonajeModelo*> _vMainCharacters;
};

#endif //_STAGEMODEL_H_