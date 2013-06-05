#ifndef _GAME_MENU_H_
#define _GAME_MENU_H_

#include "Camera.h"
#include "StaticTextBox.h"
#include <vector>
#include "Notification.h"
#include "Surface.h"
#include "Button.h"
//#include "GameView.h"


class GameMenu {

public:
	GameMenu();
	~GameMenu();
	void initialize(Camera &camera);
	void render(Camera &camera);
	//void update(Camera &camera);
	void setNotificationFontColor(SDL_Color color);
	void setNotificationFontSize(int size);
	int getButtonFontSize();
	void setButtonFontColor(SDL_Color color);
	SDL_Color getButtonFontColor();
	void setButtonFontSize(int size);
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
private:
	std::vector <Button* > buttons;
	view::Surface background;
	SDL_Color buttonFontColor;
	view::Notification notification;
	std::string imagePath;
	std::string buttonImagePath;
	bool displayNotification;
	int buttonFontSize;
};




#endif //_GAME_MENU_H_