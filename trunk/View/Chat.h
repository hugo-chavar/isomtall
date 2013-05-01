#ifndef _CHAT_H_
#define _CHAT_H_

#include "Sprite.h"
#include "Camera.h"
#include "Textbox.h"


using namespace view;


class Chat {

public:
	Chat();
	~Chat();
	bool initialize(Camera &camera);
	bool isTyping();
	void setIsTyping(bool state);
	virtual void render(Camera &camera);
	virtual void update(Camera &camera);
	void type(SDL_Event *sdlEvent);
	void cleanInput();
	bool isClosing(int x, int y);
	bool load();

private:
	Textbox textbox;
	SDL_Surface *nameBox;
	SDL_Surface *nameText;
	SDL_Surface *messagesBox;
	SDL_Surface *messagesText;
	TTF_Font *font;
	SDL_Color textColor;
	SDL_Rect nameBoxRect;
	SDL_Rect nameTextRect;
	SDL_Rect messagesBoxRect;
	SDL_Rect messagesTextRect;
	string name;
	string messages;
	bool typing;

};


#endif