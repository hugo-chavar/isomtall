#ifndef _CHARACTERVISION_H_
#define _CHARACTERVISION_H_

#include <string>
#include <vector>
#include <bitset>
#include "Constants.h"
#include "Circle.h"
#include "Positionable.h"

using namespace std;


class CharacterVision: public Positionable {

public:
	CharacterVision();
	~CharacterVision();
	void setRangeVision(int value);
	int getRangeVision();
	void increaseRangeVision(int value);
	void initialize();
	void updatePosition(pair<int, int> pos);
	bool testPosition(pair<int, int> pos);
	void setKnown(pair<int, int> pos);
	bool isInsideVision(pair<int, int> pos);
	string initToString();
	void initFromString(string data);
	string updateToString();
	void updateFromString(string data);
	void setAllKnown(bool value);
	bool isAllKnown();
	void setMagicVision(bool value);
	bool setMagicVision();
private:
	void updateVision();
	vector <bitset<MAX_STAGE_SIZE_X> > mapKnowledge;
	int rangeVision;
	int mapHeight;
	int mapWidth;
	Circle vision;
	bool allKnown;
	bool magicVision;
};

#endif //_CHARACTERVISION_H_