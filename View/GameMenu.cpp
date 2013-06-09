#include "GameMenu.h"
#include "GameView.h"


GameMenu::GameMenu() { 
	this->buttonFont = NULL;
}

GameMenu::~GameMenu() { 
	for (unsigned i = 0; i < buttons.size(); i++){
		delete buttons[i];
	}
}

void GameMenu::initialize(/*Camera &camera*/) {
	this->setImagePath(DEFAULT_MENU_PATH);
	this->notification.setImagePath(DEFAULT_NOTIFICATIONBOX_PATH);
	this->notification.setFont(GameView::instance().getFontSize(20));
	this->setButtonFont(GameView::instance().getFontSize(23));
	this->setButtonFontColor(Camera::BLACK_COLOR);
	this->setDisplayNotification(false);
	this->setDisplayBackground(true);
	//this->notification.setColor(Camera::RED_COLOR);
	//this->notification.initialize(camera);
	this->setButtonImagePath("../Connection/button.png");
	this->addButton("                 Multiplayer" , STATUS_READY_TO_UPDATE, std::make_pair<float, float>(10.0, 100.0));
	this->addButton("                 Singleplayer", STATUS_SIMULATION_SINGLE_PLAYER, std::make_pair<float, float>(10.0, 200.0));
	this->addButton("                      Exit", STATUS_EXIT, std::make_pair<float, float>(10.0, 300.0));
	this->background.load(this->getImagePath());

}

void GameMenu::setNotificationMessage(std::string message) {
	this->notification.addNotification(message);
}

void GameMenu::render(Camera &camera) {
	SDL_Rect rectangle;
	rectangle.x = 0;
	rectangle.y = 0;
	if (this->displayBackground)
		camera.render(rectangle, this->background.getSurface());

	for (unsigned i = 0; i < buttons.size(); i++){
		if (buttons[i]->isDisplaying())
			buttons[i]->render(camera);
	}
	if (this->displayNotification)
		this->notification.render(camera);
}
//
//void GameMenu::update(Camera &camera) {
//}

void GameMenu::setNotificationFontColor(SDL_Color color) {
	this->notification.setColor(color);
}

void GameMenu::setNotificationFont(TTF_Font* font) {
	this->notification.setFont(font);
}

void GameMenu::setImagePath(std::string path) {
	this->imagePath = path;
}

std::string GameMenu::getImagePath() {
	return this->imagePath;
}

std::string GameMenu::getButtonImagePath() {
	return this->buttonImagePath;
}

void GameMenu::setButtonImagePath(std::string path) {
	this->buttonImagePath = path;
}

void GameMenu::addButton(std::string label, unsigned returnValue, std::pair<float,float> pos ) {
	Button* auxButton = new Button();
	auxButton->setDisplay(true);
	auxButton->setPosition(pos);
	auxButton->setButtonImagePath(this->getButtonImagePath());
	auxButton->setFontColor(this->getButtonFontColor());
	auxButton->setFont(this->buttonFont);
	
	auxButton->setReturnValue(returnValue);
	auxButton->initialize();
	auxButton->setLabel(label);
	buttons.push_back(auxButton);
}
//
//int GameMenu::getButtonFontSize() {
//	return this->buttonFontSize;
//}

void GameMenu::setButtonFont(TTF_Font* font) {
	this->buttonFont = font;
}

void GameMenu::setDisplayNotification(bool display) {
	this->displayNotification = display;
}

void GameMenu::setDisplayBackground(bool display) {
	this->displayBackground = display;
}

SDL_Color GameMenu::getButtonFontColor() {
	return this->buttonFontColor;
}

void GameMenu::setButtonFontColor(SDL_Color color) {
	this->buttonFontColor = color;
}

void GameMenu::updateMouse(int x, int y) {
	for (unsigned i = 0; i < buttons.size(); i++) {
		if (buttons[i]->contains(x,y)) {
			buttons[i]->setTransparent(false);
		} else {
			buttons[i]->setTransparent(true);
		}
	}
}

unsigned GameMenu::select(int x, int y) {
	for (unsigned i = 0; i < buttons.size(); i++) {
		if (buttons[i]->contains(x,y)) {
			return buttons[i]->getReturnValue();
		}
	}
	return STATUS_BAD_CLICK; 
}

bool GameMenu::displayingNotification() {
	return this->displayNotification;
}

void GameMenu::hideButtons() {
	for (unsigned i = 0; i < buttons.size(); i++){
			buttons[i]->setDisplay(false);
	}
}

void GameMenu::showButtons() {
	for (unsigned i = 0; i < buttons.size(); i++){
			buttons[i]->setDisplay(true);
	}
}

void GameMenu::hideBackground() {
	this->setDisplayBackground(false);
}