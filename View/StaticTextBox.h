#ifndef _STATICTEXTBOX_H_
#define _STATICTEXTBOX_H_

#include "Camera.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include <string>


using namespace view;
using namespace std;


class StaticTextBox {

public:
	StaticTextBox();
	~StaticTextBox();
	bool initialize(string backgroundImagePath, string text, int offsetX, int offsetY);
	bool load(string imagePath);
	virtual void render(Camera &camera);
	virtual void update(int offsetX, int offsetY);
	int getOffsetX();
	int getOffsetY();
	int getWidth();
	int getHeight();

private:
	SDL_Surface *_box;
	SDL_Surface *_text;
	TTF_Font *_font;
	SDL_Color _textColor;
	SDL_Rect _boxRect;
	SDL_Rect _textRect;
	string _strText;

};


#endif