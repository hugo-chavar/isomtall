#include "Button.h"


Button::Button() { }

Button::~Button() { }

void Button::initialize() {
	
	this->box.initialize(this->getButtonImagePath(), 1);
	//TODO: this->box.
}

void Button::render(Camera &camera) {
	if (display)
		this->box.render(camera);
}

void Button::setFontColor(SDL_Color color) {
	this->box.setTextColor(color);
}

void Button::setFont(TTF_Font* font) {
	this->box.setFont(font);
}

void Button::setLabel(std::string label) {
	this->box.addLine(label);
}

std::string Button::getButtonImagePath() {
	return this->buttonImagePath;
}

void Button::setButtonImagePath(std::string path) {
	this->buttonImagePath = path;
}

unsigned Button::getReturnValue() {
	return this->returnValue;
}

void Button::setReturnValue(unsigned value) {
	this->returnValue = value;
}

void Button::setDisplay(bool display) {
	this->display = display;
}

void Button::setPosition(std::pair<float, float> pos) {
	this->box.setOffsetX(pos.first);
	this->box.setOffsetY(pos.second);
}

bool Button::isDisplaying() {
	return this->display;
}


bool Button::contains(int x, int y) {
	if ((x < this->box.getOffsetX())||(x > (this->box.getOffsetX() + this->box.getWidth())))
		return false;
	if ((y < this->box.getOffsetY())||(y > (this->box.getOffsetY() + this->box.getHeight())))
		return false;
	return true;
}

void Button::setTransparent(bool transp) {
	this->box.setTransparent(transp);
}