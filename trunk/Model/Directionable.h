#ifndef _DIRECTIONABLE_H
#define _DIRECTIONABLE_H

#ifndef orientation_t
#define orientation_t
enum orientation_t {
	NORTH,
	NORTHEAST,
	NORTHWEST,
	SOUTH,
	SOUTHEAST,
	SOUTHWEST,
	EAST,
	WEST
};
#endif

#include <utility>
#include <string>

class Directionable {
public:
	Directionable();
	~Directionable();

	static const std::pair<int, int> DIRECTION_N;
	static const std::pair<int, int> DIRECTION_NO;
	static const std::pair<int, int> DIRECTION_NE;
	static const std::pair<int, int> DIRECTION_S;
	static const std::pair<int, int> DIRECTION_SO;
	static const std::pair<int, int> DIRECTION_SE;
	static const std::pair<int, int> DIRECTION_O;
	static const std::pair<int, int> DIRECTION_E;
	static const std::pair<int, int> DIRECTION_Q;

	std::pair<int, int> getDirection();
	void setDirection(std::pair<int, int> dir);
	void setDirection(std::pair<int, int> from, std::pair<int, int> to);
	std::string directionToString();
	void directionFromString(std::string);
	int getOrientation();
	//std::pair<int, int> getTraslation();
private:
	std::pair<int, int> direction;
	//std::pair<float, float> remaining;

};

#endif //_DIRECTIONABLE_H

