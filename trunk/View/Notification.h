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

	private:
		StaticTextBox box;

	};

}


#endif