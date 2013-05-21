#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include <set>
//#include <list>
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
private:
	set <pair<int, int> > limits;
	set <pair<int, int> >::iterator itlim;
	//list <pair<int, int> > orderedLimits;
	vector <pair<int, int> > orderedLimits;
	pair<int, int> center;
};


#endif