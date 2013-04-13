#ifndef __ENTITYOBJECT_H_
#define __ENTITYOBJECT_H_

#include <string>
#include "Constants.h"

using namespace std;


class EntityObject {

public:
	EntityObject();
	EntityObject(string name, string imagePath, int baseWidth, int baseHeight, int pixelRefX, int pixelRefY): 
		_name(name), _image_path(imagePath), _base_width(baseWidth), _base_height(baseHeight), _pixel_ref_x(pixelRefX), _pixel_ref_y(pixelRefY) { };
	~EntityObject();

	string name();
	string imagePath();
	int baseWidth();
	int baseHeight();
	int pixelRefX();
	int pixelRefY();
	void imagePath(string);
	virtual bool isAnimated();

private:
	string _name;
	int _base_width;
	int _base_height;
	int _pixel_ref_x;
	int _pixel_ref_y;
	string _image_path;
};


#endif