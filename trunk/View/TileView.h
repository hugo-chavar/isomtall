#ifndef _TILEVIEW_H_
#define _TILEVIEW_H_

#include <string>
#include "TileModel.h"
#include "Entity.h"
#include "DataTypes.h"
#include "Camera.h"
#include "Surface.h"

using namespace std;

class TileView {

public:
	TileView();
	TileView(TileModel*);
	~TileView();
	TileModel* getTileModel();
	Entity* getGroundEntity();
	Entity* getOtherEntity();
	void setGroundEntity(Entity* e);
	void setOtherEntity(Entity* e);
	void addEntity(Entity* e);
	KeyPair getPosition();
	void setNextTile(TileView* );
	TileView* getNextTile();
	void setRelatedTile(TileView* );
	TileView* getRelatedTile();
	bool drawable();
	bool EOL();
	string getGroundEntityName();
	bool hasOtherEntity();
	string getOtherEntityName();
	void createGround(Sprite*);
	void createOtherEntity(Sprite*);
	void renderEntity(Camera& camera);
	void renderGround(Camera& camera);
	void setFogged(bool value);
	void update();
	void initialize();
private:
	TileModel* tileModel;
	Entity* groundEntity;
	Entity* otherEntity;
	TileView* nextTile;
	TileView* relatedTile;
	bool isDrawable;
	bool isFogged;
};


#endif //_TILEVIEW_H_