#pragma once
#include "SDL_ttf.h"
#include "SDL_image.h"
#include <string>

using namespace std;

class Line
{
public:
	Line(string text,TTF_Font * _font,SDL_Color _textColor);
	~Line();
	string getStrText();
	SDL_Surface * getText();
	void liberar();

private:
	SDL_Surface * _text;
	string _strText;
};

