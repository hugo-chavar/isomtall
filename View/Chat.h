#ifndef _CHAT_H_
#define _CHAT_H_

#include "Camera.h"
#include "Textbox.h"
#include "StaticTextBox.h"


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

private:
	Textbox textbox;
	StaticTextBox nameBox;
	StaticTextBox messagesBox;
	bool typing;

};


#endif