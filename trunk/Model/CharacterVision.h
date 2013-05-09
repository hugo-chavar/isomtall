#ifndef _CHARACTERVISION_H_
#define _CHARACTERVISION_H_

#include <string>
#include <vector>
#include <bitset>
#include "Constants.h"
#include "Circle.h"

using namespace std;


class CharacterVision {

public:
	CharacterVision();
	~CharacterVision();
	void setRangeVision(int value);
	void initialize();
	void setPosition(pair<int, int>);
	void updatePosition(pair<int, int>);
	bool testPosition(pair<int, int>);
	void setKnown(pair<int, int> );
	bool isInsideVision(pair<int, int> pos);
private:
	vector <bitset<MAX_STAGE_SIZE_X> > mapKnowledge;
	int rangeVision;
	int mapHeight;
	int mapWidth;
	pair<int, int > position;
	Circle vision;
};


#endif //_CHARACTERVISION_H_