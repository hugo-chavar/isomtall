#ifndef _NOTIFICATION_H_
#define _NOTIFICATION_H_

#include "Camera.h"
#include "StaticTextBox.h"


namespace view {

	class Notification {

	public:
		Notification();
		~Notification();
		bool initialize(Camera &camera);
		virtual void render(Camera &camera);
		virtual void update(Camera &camera);
		void addNotification(string message);
		void setColor(SDL_Color color);
		void setFontSize(int size);
		void setImagePath(string path);
		string getImagePath();
	private:
		StaticTextBox box;
		string imagePath;
	};

}


#endif