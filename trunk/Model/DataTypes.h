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


struct sItem {
		string type;
		string characteristics;
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

/*
int main(){
	std::pair<int, int> x(7,5);
	std::pair<int, int> y(2,9);
	int z = -2;
	std::pair<int, int> m = x + y;
	std::pair<int, int> n = x*z;
	std::cout<<"X"<<std::endl;
	std::cout<<"first: "<< x.first<<"second: "<< x.second  <<std::endl;
	std::cout<<"Y"<<std::endl;
	std::cout<<"first: "<< y.first<<"second: "<< y.second  <<std::endl;
	std::cout<<"M"<<std::endl;
	std::cout<<"first: "<< m.first<<"second: "<< m.second  <<std::endl;
	std::cout<<"N"<<std::endl;
	std::cout<<"first: "<< n.first<<"second: "<< n.second  <<std::endl;
	std::cin>>z;
	return 0;
}
*/


#endif