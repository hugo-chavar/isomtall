#ifndef _TILEVIEW_H_
#define _TILEVIEW_H_

#include <string>
#include "TileModel.h"
#include "Entity.h"
#include "DataTypes.h"
#include "Camera.h"

using namespace std;

class TileView {

public:
	TileView();
	TileView(TileModel* );
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
	void render(Camera& camera);
private:
	TileModel* tileModel;
	Entity* groundEntity;
	Entity* otherEntity;
	TileView* nextTile;
	TileView* relatedTile;
	bool isDrawable;
};


#endif //_TILEVIEW_H_