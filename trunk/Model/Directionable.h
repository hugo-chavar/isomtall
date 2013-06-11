#ifndef _DIRECTIONABLE_H
#define _DIRECTIONABLE_H

#include <utility>
#include <string>

class Directionable
{
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

	std::pair<int, int> getDirection();
	void setDirection(std::pair<int, int>);
	std::string directionToString();
	void directionFromString(std::string);
protected:
	std::pair<int, int> direction;

};

#endif //_DIRECTIONABLE_H

