#ifndef _GAMEDEPENDENT_H
#define _GAMEDEPENDENT_H

#include <utility>

class GameDependent {
public:
	GameDependent();
	~GameDependent();
	float getDeltaTime();
	std::pair<int, int> pixelToTileCoordinates(std::pair<int, int> pixelPosition);
	bool isInsideWorld(std::pair<int, int> tilePosition);
	bool canCross(std::pair<int, int> tilePosition);
protected:

};

#endif //_GAMEDEPENDENT_H

