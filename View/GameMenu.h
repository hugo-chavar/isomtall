#ifndef _GAME_MENU_H_
#define _GAME_MENU_H_

#include "Camera.h"
#include "StaticTextBox.h"
#include <vector>
#include "Notification.h"
#include "Surface.h"
#include "Button.h"
#include "SDL_ttf.h"
//#include "GameView.h"


class GameMenu {

public:
	GameMenu();
	~GameMenu();
	void initialize(/*Camera &camera*/);
	void render(Camera &camera);
	//void update(Camera &camera);
	void setNotificationFontColor(SDL_Color color);
	void setNotificationFont(TTF_Font* size);
	void setButtonFontColor(SDL_Color color);
	SDL_Color getButtonFontColor();
	void setButtonFont(TTF_Font* font);
	void setImagePath(std::string path);
	void setButtonImagePath(std::string path);
	std::string getButtonImagePath();
	std::string getImagePath();
	//void show();
	void setNotificationMessage(std::string msg);
	void setDisplayNotification(bool display);
	void addButton(std::string label, unsigned returnValue, std::pair<float,float> pos );
	void updateMouse(int x, int y);
	unsigned select(int x, int y);
	bool displayingNotification();
	void hideButtons();
private:
	std::vector <Button* > buttons;
	view::Surface background;
	SDL_Color buttonFontColor;
	view::Notification notification;
	std::string imagePath;
	std::string buttonImagePath;
	bool displayNotification;
	TTF_Font* buttonFont;
};




#endif //_GAME_MENU_H_