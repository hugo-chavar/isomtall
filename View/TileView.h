#ifndef _TILEVIEW_H_
#define _TILEVIEW_H_

#include <string>
//#include "SDL.h"
#include "TileModel.h"
#include "Entity.h"
#include "DataTypes.h"


class TileView {

public:
	TileView();
	~TileView();
	//void cleanUp();
	//int getSpeedPenalty()
	Entity* getGroundEntity();
	Entity* getOtherEntity();
	void setGroundEntity(Entity * e);
	void setOtherEntity(Entity * e);
	void addEntity(Entity * e);
	void setPosition(KeyPair);
	KeyPair getPosition();
	void setNextTile(TileView* );
	TileView* getNextTile();
	void setRelatedTile(TileView* );
	TileView* getRelatedTile();
	void setUndrawable();
	bool drawable();
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


#endif //_TILE_H_