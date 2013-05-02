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
	bool initialize(string backgroundImagePath, SDL_Color color, char *fontPath, float offsetX, float offsetY);
	virtual void render(Camera &camera);
	virtual void update(float offsetX, float offsetY);
	void setText(string text);
	float getOffsetX();
	float getOffsetY();
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
	bool load(string imagePath, char *fontPath);

};


#endif