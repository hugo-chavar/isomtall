#include "Notification.h"
#include "Constants.h"


view::Notification::Notification() { }

view::Notification::~Notification() { }

bool view::Notification::initialize(Camera &camera) {
	if (!box.initialize(this->getImagePath(), Camera::GREEN_COLOR, camera.getOffsetX()+(camera.getWidth()/2), camera.getOffsetY()+(camera.getHeight()/2), 24, 1))
		return false;
	box.update(box.getOffsetX()-(box.getWidth()/2), box.getOffsetY()-(box.getHeight()/2));
	return true;
}

void view::Notification::addNotification(string message) {
	box.addLine(message);
}

void view::Notification::render(Camera &camera) {
	box.render(camera);
}

void view::Notification::update(Camera &camera) {
	box.update(camera.getOffsetX()+(camera.getWidth()/2)-(box.getWidth()/2), camera.getOffsetY()+(camera.getHeight()/2)-(box.getHeight()/2));
}

void view::Notification::setColor(SDL_Color color) {
	box.setTextColor(color);
}

void view::Notification::setFontSize(int size) {
	box.setTextSize(size);
}

void view::Notification::setImagePath(string path) {
	this->imagePath = path;
}

string view::Notification::getImagePath() {
	return this->imagePath;
}