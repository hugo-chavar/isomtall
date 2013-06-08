#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include <set>
#include <vector>

using namespace std;

class Circle {
public:
	Circle();
	Circle(pair<int, int>, int);
	~Circle();
	bool inside(pair<int, int>);
	void initialize(pair<int, int>, int);
	void clear();
	void fill();
	bool hasNext();
	pair<int, int> next();
	int distanceToCenter(pair<int, int>);
private:
	set <pair<int, int> > limits;
	set <pair<int, int> >::iterator itlim;
	vector <pair<int, int> > orderedLimits;
	pair<int, int> center;
	int radius;
};


#endif