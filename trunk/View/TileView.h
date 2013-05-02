#ifndef _TILEVIEW_H_
#define _TILEVIEW_H_

#include <string>
//#include "SDL.h"
#include "TileModel.h"
#include "Entity.h"
#include "DataTypes.h"

using namespace std;

class TileView {

public:
	TileView();
	TileView(TileModel* );
	~TileView();
	//void cleanUp();
	//int getSpeedPenalty()
	Entity* getGroundEntity();
	Entity* getOtherEntity();
	void setGroundEntity(Entity* e);
	void setOtherEntity(Entity* e);
	void addEntity(Entity* e);
	//void setPosition(KeyPair );
	KeyPair getPosition();
	void setNextTile(TileView* );
	TileView* getNextTile();
	void setRelatedTile(TileView* );
	TileView* getRelatedTile();
	//void setUndrawable();
	bool drawable();

	string getGroundEntityName();
	bool hasOtherEntity();
	string getOtherEntityName();
	void createGround(Sprite*);
	void createOtherEntity(Sprite*);
private:
	//SDL_Surface* sdlSurface;
	TileModel* tileModel;
	Entity* groundEntity;
	Entity* otherEntity;
	TileView* nextTile;
	TileView* relatedTile;
	KeyPair position;
	bool isDrawable;
};


#endif //_TILEVIEW_H_