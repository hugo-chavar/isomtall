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
	bool initialize(Camera &camera);
	bool load();
	virtual void render(Camera &camera);
	virtual void update(Camera &camera);
	void handleInput(SDL_Event *sdlEvent);
	bool pressingClosingBox(int x, int y);
	void cleanTextBox();
	int getOffsetX();
	int getOffsetY();
	int getWidth();
	int getHeight();
	
private:
	SDL_Surface *box;
	SDL_Surface *closeButton;
	SDL_Surface *message;
	string str;
	TTF_Font *font;
	SDL_Color textColor;
	SDL_Rect boxRect;
	SDL_Rect closeButtonRect;
	SDL_Rect messageRect;

};


#endif