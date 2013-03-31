#include "Stage.h"

using namespace model;

int Stage::width()
{
	return _width;
}

int Stage::height()
{
	return _height;
}

void Stage::height(int value)
{
	_height = value;
}

void Stage::width(int value)
{
	_width = value;
}