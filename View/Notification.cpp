#include "Notification.h"

view::Notification::Notification() { }

view::Notification::~Notification() { }

bool view::Notification::initialize(Camera &camera) {
	//SDL_Color boxColor;
	////boxColor.r = 255;
	////boxColor.g = 0;
	////boxColor.b = 0;
	//boxColor = Camera::GREEN_COLOR;
	if (!box.initialize("../Images/notificationBox.png", Camera::GREEN_COLOR, "../Fonts/arial.ttf", camera.getOffsetX()+(camera.getWidth()/2), camera.getOffsetY()+(camera.getHeight()/2), 24, 1))
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