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
	void increaseRangeVision(int value);
	void initialize();
	void setPosition(pair<int, int> pos);
	void updatePosition(pair<int, int> pos);
	bool testPosition(pair<int, int> pos);
	void setKnown(pair<int, int> pos);
	bool isInsideVision(pair<int, int> pos);
	string toString();
	void fromString(string data);
private:
	void updateVision();
	vector <bitset<MAX_STAGE_SIZE_X> > mapKnowledge;
	int rangeVision;
	int mapHeight;
	int mapWidth;
	pair <int, int > position;
	Circle vision;
};


#endif //_CHARACTERVISION_H_