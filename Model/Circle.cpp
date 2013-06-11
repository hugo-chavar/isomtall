#include "Circle.h"
#include <iterator>
#include <algorithm>


bool comparator(pair<int, int> p1, pair<int, int> p2 ) {
	if ( (p1.second > p2.second) || ((p1.second == p2.second) && (p1.first < p2.first)))
		return true;
	return false;
}

Circle::Circle() {
}

Circle::Circle(pair<int, int> center, int range) {
	this->initialize(center, range);
}

Circle::~Circle() {
}

bool Circle::inside(pair<int, int> pos) {
	return (this->distanceToCenter(pos) <= this->radius);
}

void Circle::clear() {
	limits.clear();
}

void Circle::initialize(pair<int, int> centerPoint, int range) {
	this->radius = range;
	this->center = centerPoint;
	this->clear();
	int x = range, y = 0;
	int xChange = 1 - range*2;
	int yChange = 0;
	int rangeError = 0;

	while (x >= y) {
		limits.insert(make_pair(x + this->center.first, y + this->center.second));
		limits.insert(make_pair(y + this->center.first, x + this->center.second));
		limits.insert(make_pair(-x + this->center.first, y + this->center.second));
		limits.insert(make_pair(-y + this->center.first, x + this->center.second));
		limits.insert(make_pair(-x + this->center.first, -y + this->center.second));
		limits.insert(make_pair(-y + this->center.first, -x + this->center.second));
		limits.insert(make_pair(x + this->center.first, -y + this->center.second));
		limits.insert(make_pair(y + this->center.first, -x + this->center.second));

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
	vector <pair<int, int> > aux;
	std::copy(limits.begin(), limits.end(), std::inserter(aux, aux.begin()));
	std::sort (aux.begin(), aux.end(), comparator);
	orderedLimits.assign(aux.begin(),aux.end());
}

void Circle::fill() {
	if (orderedLimits.size() < 5)
		return;
	vector <pair<int, int> >::iterator itBegin;
	itBegin = orderedLimits.begin();
	vector <pair<int, int> >::iterator itEnd;
	pair<int, int> pos1;
	pair<int, int> pos2 = orderedLimits.back();
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

pair<int, int> Circle::next() {
	pair<int, int> aux = (*itlim);
	itlim++;
	return aux;
}

int Circle::distanceToCenter(pair<int, int> point) {
	int firstCoordinate = center.first - point.first;
	int secondCoordinate = center.second - point.second;
	firstCoordinate = firstCoordinate*firstCoordinate;
	secondCoordinate = secondCoordinate*secondCoordinate;
	double distance = sqrt(static_cast<double>(firstCoordinate + secondCoordinate));
	return static_cast<int> (std::floor(distance + 0.5));
}