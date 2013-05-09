#include "Circle.h"
#include <iterator>


bool comparator(std::pair<int, int> p1, std::pair<int, int> p2 ) {
	if ( (p1.second > p2.second) || ((p1.second == p2.second) && (p1.first < p2.first)))
		return true;
	return false;
}

Circle::Circle() {
}

Circle::Circle(std::pair<int, int> center, int range) {
	this->initialize(center, range);
}

Circle::~Circle() {
}

bool Circle::inside(std::pair<int, int> pos) {
	std::list <std::pair<int, int> >::iterator it = orderedLimits.begin();
	while ( (it != orderedLimits.end()) && ((*it).second > pos.second)) {
		it++;
	}
	if ( ((*it).second != pos.second) || ((*it).first > pos.first))
		return false;
	while ((it != orderedLimits.end()) && ((*it).second == pos.second) && ((*it).first < pos.first) ) {
		it++;
	}
	if ((*it).first < pos.first)
		return false;

	return true;
}

void Circle::clear() {
	limits.clear();
	orderedLimits.clear();
}

void Circle::initialize(std::pair<int, int> center, int range) {
	int x = range, y = 0;
	int xChange = 1 - range*2;
	int yChange = 0;
	int rangeError = 0;

	while (x >= y) {
		limits.insert(std::make_pair(x + center.first, y + center.second));
		limits.insert(std::make_pair(y + center.first, x + center.second));
		limits.insert(std::make_pair(-x + center.first, y + center.second));
		limits.insert(std::make_pair(-y + center.first, x + center.second));
		limits.insert(std::make_pair(-x + center.first, -y + center.second));
		limits.insert(std::make_pair(-y + center.first, -x + center.second));
		limits.insert(std::make_pair(x + center.first, -y + center.second));
		limits.insert(std::make_pair(y + center.first, -x + center.second));

		y++;
		rangeError += yChange;
		yChange += 2;
		if(((rangeError << 1) + xChange) > 0)
		{
			x--;
			rangeError += xChange;
			xChange += 2;
		}
	}
	std::copy(limits.begin(), limits.end(), std::inserter(orderedLimits, orderedLimits.begin()));
	//orderedLimits.assign(limits.begin(), limits.end());
	orderedLimits.sort(comparator);
}

void Circle::fill() {
	if (orderedLimits.size() < 5)
		return;
	std::list <std::pair<int, int> >::iterator it = orderedLimits.begin();
	int maxValueY = (*it).second;

	while ((it != orderedLimits.end()) && ((*it).second == maxValueY)) {
		it++;
	}

	std::pair<int, int> pos1 = (*it);
	it++;
	std::pair<int, int> pos2 = (*it);
	it++;
	while ((it != orderedLimits.end()) && (pos1.second == pos2.second) && (pos1.second != (*it).second)){

		for (int i = (pos1.first + 1); i < pos2.first; i++) {
			limits.insert(std::make_pair(i, pos1.second));
		}
		
		pos1 = (*it);
		it++;
		if (it != orderedLimits.end())
			pos2 = (*it);
		it++;
	}
	itlim = limits.begin();
}

bool Circle::hasNext() {
	return itlim != limits.end();
}

std::pair<int, int> Circle::next() {
	std::pair<int, int> aux = (*itlim);
	itlim++;
	return aux;
}