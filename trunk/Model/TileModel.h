#ifndef _TILEMODEL_H_
#define _TILEMODEL_H_

#include "EntityObject.h"
#include "DataTypes.h"

class TileModel
{
public:
	TileModel();
	~TileModel();
	EntityObject * getGroundEntity();
	EntityObject * getOtherEntity();
	void setGroundEntity(EntityObject * e);
	void setOtherEntity(EntityObject * e);
	void addEntity(EntityObject * e);
	void setPosition(KeyPair);
	void setNextTile(TileModel*);
	TileModel* getNextTile();
private:
	EntityObject* groundEntity;
	EntityObject* otherEntity;
	TileModel* nextTile;
	KeyPair position;
};



#endif //_TILEMODEL_H_