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
	orderedLimits.sort(comparator);
}

void Circle::fill() {
	if (orderedLimits.size() < 5)
		return;
	std::list <std::pair<int, int> >::iterator itBegin = orderedLimits.begin();
	std::list <std::pair<int, int> >::iterator itEnd;
	std::pair<int, int> pos1;
	std::pair<int, int> pos2 = orderedLimits.back();
	int maxValueY = (*itBegin).second;
	int minValueY = (pos2.second >= -1) ? pos2.second : -1;

	while ((itBegin != orderedLimits.end()) && ((*itBegin).second == maxValueY)) {
		itBegin++;
	}

	pos1 = (*itBegin);
	itEnd = itBegin;
	while ((itBegin != orderedLimits.end()) && (minValueY < (*itBegin).second ) ) { 
		while ((itEnd != orderedLimits.end()) && (pos1.second == (*itEnd).second ) ) {
			pos2 = (*itEnd);
			itEnd++;
		}

		for (int i = (pos1.first + 1); i < pos2.first; i++) {
			limits.insert(std::make_pair(i, pos1.second));
		}

		itBegin = itEnd;
		pos1 = (*itBegin);
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