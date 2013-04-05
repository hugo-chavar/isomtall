#ifndef _TILE_H_
#define _TILE_H_

#include "EntityObject.h"

namespace model
{
	class Tile
	{
	public:
		Tile();
		EntityObject * getEntity();
		void setEntity(EntityObject * e);
	private:
		EntityObject* entity;
	};

}


#endif //_TILE_H_