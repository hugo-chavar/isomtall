#include "Chat.h"


Chat::Chat() { }

Chat::~Chat() { }

bool Chat::initialize(Camera &camera) {
	if (!textbox.initialize(camera))
		return false;
	if (!nameBox.initialize("../Images/nameBox.png", "Jugador 1", camera.getOffsetX()+5, camera.getOffsetY()+5))
		return false;
	if (!messagesBox.initialize("../Images/messagesBox.png", "Hola", nameBox.getOffsetX(), nameBox.getOffsetY()+nameBox.getHeight()+10))
		return false;
	return true;
}

bool Chat::isTyping() {
	return typing;
}

void Chat::setIsTyping(bool state) {
	typing = state;
}

void Chat::render(Camera &camera) {
	nameBox.render(camera);
	messagesBox.render(camera);
	textbox.render(camera);
}

void Chat::update(Camera &camera) {
	nameBox.update(camera.getOffsetX()+5, camera.getOffsetY()+5);
	messagesBox.update(nameBox.getOffsetX(), nameBox.getOffsetY()+nameBox.getHeight()+10);
	textbox.update(camera);
}

void Chat::type(SDL_Event *sdlEvent) {
	textbox.handleInput(sdlEvent);
}

void Chat::cleanInput() {
	textbox.cleanTextBox();
}

bool Chat::isClosing(int x, int y) {
	return textbox.pressingClosingBox(x, y);
}