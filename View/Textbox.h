#ifndef _TEXTBOX_H_
#define _TEXTBOX_H_

#include "Sprite.h"
#include "Camera.h"
#include "SDL_ttf.h"


using namespace view;


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
	/*
	Chat(Sprite *spriteCargado);
	bool initialize();
	*/
	
private:
	SDL_Surface *background;
	SDL_Surface *closeButton;
	SDL_Surface *message;
	string str;
	TTF_Font *font;
	SDL_Color textColor;
	SDL_Rect rectangle;
	SDL_Rect closeButtonRect;
	SDL_Rect messageRect;

};


#endif