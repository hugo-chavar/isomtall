#ifndef __DATATYPES_H__
#define __DATATYPES_H__

#include <vector>
#include "EntityObject.h"
#include "AnimatedEntity.h"


typedef std::pair<unsigned int,unsigned int> KeyPair;

struct EntityDef {
	std::string entity;
	int x;
	int y;
	};

struct EntLists {
	vector <EntityObject*> vEntitiesObject;
	vector <AnimatedEntity*> vAnimatedEntities;

	const EntLists& operator=(const EntLists& l){
		vEntitiesObject = l.vEntitiesObject;
		vAnimatedEntities = l.vAnimatedEntities;
		return *this;
	}

};


#endif