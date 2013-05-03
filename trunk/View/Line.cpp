#include "Line.h"


Line::Line(string text,TTF_Font * _font,SDL_Color _textColor)
{
	_text=TTF_RenderText_Solid(_font, text.c_str(), _textColor);
	_strText = text;
}

void Line::liberar()
{
	SDL_FreeSurface(_text);
}


Line::~Line()
{
}

string Line::getStrText()
{
	return this->_strText;
}

SDL_Surface * Line::getText()
{
	return this->_text;
}