#ifndef _CHAT_H_
#define _CHAT_H_

#include "Camera.h"
#include "Textbox.h"
#include "StaticTextBox.h"
#include "Chat.h"

namespace view {

	class ChatView {

	public:
		ChatView();
		~ChatView();
		bool initialize(Camera &camera);
		bool isTyping();
		void setIsTyping(bool state);
		virtual void render(Camera &camera);
		virtual void update(Camera &camera);
		void type(SDL_Event *sdlEvent);
		void cleanInput();
		bool isClosing(float x, float y);
		void sendMessage();
		void setTo(string To);


		model::Chat * modelChat;
	private:
		Textbox textbox;
		StaticTextBox nameBox;
		StaticTextBox messagesBox;
		SDL_Surface *closeButton;
		SDL_Rect closeButtonRect;
		bool typing;
		bool initializeCloseButton();
//		model::Chat * modelChat;
		void receiveMsgs();

	};

}


#endif