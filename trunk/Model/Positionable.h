#ifndef _POSITIONABLE_H
#define _POSITIONABLE_H

#include <utility>
#include <string>

class Positionable {
public:
	Positionable();
	~Positionable();
	std::pair<int, int> getPosition();
	void setPosition(std::pair<int, int>);
	std::string positionToString();
	void positionFromString(std::string);
protected:
	std::pair<int, int> position;

};

#endif //_POSITIONABLE_H

