#ifndef _TEXTBOX_H_
#define _TEXTBOX_H_

#include "Camera.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include <string>


using namespace view;
using namespace std;


class Textbox {

public:
	Textbox();
	~Textbox();
	bool initialize(string backgroundImagePath, SDL_Color color, char *fontPath, float offsetX, float offsetY);
	virtual void render(Camera &camera);
	virtual void update(float offsetX, float offsetY);
	void handleInput(SDL_Event *sdlEvent);
	void cleanTextBox();
	float getOffsetX();
	void setOffsetX(float offsetX);
	float getOffsetY();
	int getWidth();
	int getHeight();
	
private:
	SDL_Surface *box;
	SDL_Surface *message;
	string str;
	TTF_Font *font;
	SDL_Color textColor;
	SDL_Rect boxRect;
	SDL_Rect messageRect;
	bool load(string backgroundImagePath, char *fontPath);

};


#endif