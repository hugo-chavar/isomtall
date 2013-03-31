#include "EntityObject.h"

using namespace model;

int EntityObject::positionX()
{
	return _positionX;
}

int EntityObject::positionY()
{
	return _positionY;
}

void EntityObject::position(int valueX, int valueY)
{
	_positionX = valueX;
	_positionY = valueY;
}

void EntityObject::imagePath(string value)
{
	_imagepath = value;
}

string EntityObject::imagePath()
{
	return _imagepath;
}