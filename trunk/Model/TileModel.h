#ifndef _TILEMODEL_H_
#define _TILEMODEL_H_

#include "EntityObject.h"
#include "DataTypes.h"

class TileModel{

public:
	TileModel();
	~TileModel();
	EntityObject * getGroundEntity();
	EntityObject * getOtherEntity();
	void setGroundEntity(EntityObject * e);
	void setOtherEntity(EntityObject * e);
	void addEntity(EntityObject * e);
	void setPosition(KeyPair);
	KeyPair getPosition();
	void setNextTile(TileModel*);
	TileModel* getNextTile();
	void setRelatedTile(TileModel*);
	TileModel* getRelatedTile();
	void setUndrawable();
	bool drawable();
private:
	EntityObject* groundEntity;
	EntityObject* otherEntity;
	TileModel* nextTile;
	TileModel* relatedTile;
	KeyPair position;
	bool isDrawable;
};



#endif //_TILEMODEL_H_