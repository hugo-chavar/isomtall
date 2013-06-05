#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Camera.h"
#include "StaticTextBox.h"

class Button {

public:
	Button();
	~Button();
	void initialize();
	void render(Camera &camera);
	unsigned getReturnValue();
	void setFontColor(SDL_Color color);
	void setReturnValue(unsigned size);
	void setFontSize(int size);
	void setLabel(std::string path);
	void setButtonImagePath(std::string path);
	std::string getButtonImagePath();
	void setPosition(std::pair<float, float> pos);
	std::string getLabel();
	void setDisplay(bool display);
	bool isDisplaying();
	bool contains(int x, int y);
	void setTransparent(bool);
private:
	StaticTextBox box;
	int returnValue;
	bool display;
	std::string buttonImagePath;

};




#endif