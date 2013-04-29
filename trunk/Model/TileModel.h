#ifndef _TILEMODEL_H_
#define _TILEMODEL_H_

#include "EntityObject.h"

class TileModel
{
public:
	TileModel();
	EntityObject * getGroundEntity();
	EntityObject * getOtherEntity();
	void setGroundEntity(EntityObject * e);
	void setOtherEntity(EntityObject * e);
	void addEntity(EntityObject * e);
	void setPosition(unsigned, unsigned);
private:
	EntityObject* groundEntity;
	EntityObject* otherEntity;
	unsigned posx;
	unsigned posy;
};



#endif //_TILEMODEL_H_