#include "Notification.h"
#include "Constants.h"


view::Notification::Notification() { 
	this->currentBox = NULL;
	this->font = NULL;
	this->imagePath = "";
}

view::Notification::~Notification() {
	while (!this->boxMap.empty())
	{
		delete this->boxMap.begin()->second;
		this->boxMap.erase(this->boxMap.begin());
	}
}

//bool view::Notification::initialize(Camera &camera) {
//	if (!box.initialize(this->getImagePath(), Camera::GREEN_COLOR, 400 /*camera.getOffsetX()+(camera.getWidth()/2)*/, 300 /*camera.getOffsetY()+(camera.getHeight()/2)*/, 24, 1))
//		return false;
//	box.update(box.getOffsetX()-(box.getWidth()/2), box.getOffsetY()-(box.getHeight()/2));
//	return true;
//}

StaticTextBox* view::Notification::newBox() {
	StaticTextBox* aux = new StaticTextBox();
	aux->initialize(this->getImagePath(), this->currentColor, 400 /*camera.getOffsetX()+(camera.getWidth()/2)*/, 300 /*camera.getOffsetY()+(camera.getHeight()/2)*/, this->getFont(), 1);

	aux->update(aux->getOffsetX()-(aux->getWidth()/2), aux->getOffsetY()-(aux->getHeight()/2));
	return aux;

}

void view::Notification::addNotification(string message) {

	//if (boxIt != boxMap.end())
	if (boxMap.count(message) > 0){
		boxIt = boxMap.find(message);
		this->currentBox = boxIt->second;
	} else {
		StaticTextBox* aBox = this->newBox();
		aBox->addLine(message);
		boxMap[message] = aBox;
		this->currentBox = aBox;
	}
	this->currentBox->setTextColor(this->currentColor);
}

void view::Notification::render(Camera &camera) {
	this->currentBox->render(camera);
}
//
//void view::Notification::update(Camera &camera) {
//	box.update(camera.getOffsetX()+(camera.getWidth()/2)-(box.getWidth()/2), camera.getOffsetY()+(camera.getHeight()/2)-(box.getHeight()/2));
//}

void view::Notification::setColor(SDL_Color color) {
	this->currentColor = color;
}

//void view::Notification::setFont(TTF_Font* ttf) {
//	//box.setFont(ttf);
//	this->font = ttf;
//}

void view::Notification::setImagePath(string path) {
	this->imagePath = path;
}

string view::Notification::getImagePath() {
	return this->imagePath;
}

void view::Notification::setFont(TTF_Font* font) {
	this->font = font;
}

TTF_Font* view::Notification::getFont() {
	return this->font;
}