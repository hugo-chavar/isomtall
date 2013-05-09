#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include <set>
#include <list>

class Circle {
public:
	Circle();
	Circle(std::pair<int, int>, int);
	~Circle();
	bool inside(std::pair<int, int>);
	void initialize(std::pair<int, int>, int);
	void clear();
	void fill();
	bool hasNext();
	std::pair<int, int> next();
private:
	//bool comparator(std::pair<int, int>, std::pair<int, int> );
	std::set <std::pair<int, int> > limits;
	std::set <std::pair<int, int> >::iterator itlim;
	std::list <std::pair<int, int> > orderedLimits;
	//std::list <std::list <std::pair<int, int> > > levels;
	std::pair<int, int> center;
};


#endif