#ifndef _DIRECTIONABLE_H
#define _DIRECTIONABLE_H

#ifndef orientation_t
#define orientation_t
enum orientation_t {
	NORTH,
	NORTHEAST,
	EAST,
	SOUTHEAST,
	SOUTH,
	SOUTHWEST,
	WEST,
	NORTHWEST
};
#endif

#include <utility>
#include <string>
#include <map>

class Directionable {
public:
	Directionable();
	~Directionable();

	static std::map<std::pair<int, int>, std::pair<int, int> > create_map()
	{
		std::map<std::pair<int, int>, std::pair<int, int> > m;

		m[DIRECTION_N] = DIRECTION_NE;
		m[DIRECTION_S] = DIRECTION_SO;
		m[DIRECTION_NE] = DIRECTION_E;
		m[DIRECTION_E] = DIRECTION_SE;
		m[DIRECTION_SE] = DIRECTION_S;
		m[DIRECTION_O] = DIRECTION_NO;
		m[DIRECTION_NO] = DIRECTION_N;
		m[DIRECTION_SO] = DIRECTION_O;
		m[DIRECTION_Q] = DIRECTION_Q;
		return m;
	}

	static const std::pair<int, int> DIRECTION_N;
	static const std::pair<int, int> DIRECTION_NO;
	static const std::pair<int, int> DIRECTION_NE;
	static const std::pair<int, int> DIRECTION_S;
	static const std::pair<int, int> DIRECTION_SO;
	static const std::pair<int, int> DIRECTION_SE;
	static const std::pair<int, int> DIRECTION_O;
	static const std::pair<int, int> DIRECTION_E;
	static const std::pair<int, int> DIRECTION_Q;
	static const std::map<std::pair<int, int>, std::pair<int, int> > TRANSFORM_TILE_TO_PIXEL_DIRECTION;

	std::pair<int, int> getDirection();
	void setDirection(std::pair<int, int> dir);
	void setDirection(std::pair<int, int> from, std::pair<int, int> to);
	std::pair<int, int> calculateDirection(std::pair<int, int> from, std::pair<int, int> to);
	std::pair<int, int> calculateDistance(std::pair<int, int> from, std::pair<int, int> to);
	std::string directionToString();
	void directionFromString(std::string);
	int getOrientation();
	std::pair<int, int> getPixelDirection();
	void changeToOppositeDirection();
private:
	std::pair<int, int> direction;
	

};

#endif //_DIRECTIONABLE_H

