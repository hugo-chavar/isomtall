#ifndef _TILEMODEL_H_
#define _TILEMODEL_H_

#include "EntityObject.h"

class TileModel
{
public:
	TileModel();
	EntityObject * getEntity();
	void setEntity(EntityObject * e);
private:
	EntityObject* entity;
};



#endif //_TILEMODEL_H_