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
		vEntitiesObject.assign(l.vEntitiesObject.begin(),l.vEntitiesObject.end());
		vAnimatedEntities.assign(l.vAnimatedEntities.begin(),l.vAnimatedEntities.end());
		return *this;
	}

};


template <typename T1, typename T2> 
std::pair<T1,T2> operator+(const std::pair<T1,T2> &p1, const std::pair<T1,T2> &p2) { 
	return std::pair<T1,T2>(p1.first + p2.first, p1.second + p2.second); 
}


template <typename T1, typename T2> 
std::pair<T1,T2> operator*(const std::pair<T1,T2> &p1, const T2 &escalar) { 
	return std::pair<T1,T2>(p1.first*escalar, p1.second*escalar); 
} 

/* Example: How to use this 2 last methods*/



#endif