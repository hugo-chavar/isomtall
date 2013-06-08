#ifndef _NOTIFICATION_H_
#define _NOTIFICATION_H_

#include "Camera.h"
#include "StaticTextBox.h"
#include "SDL_ttf.h"
#include <map>


namespace view {

	class Notification {

	public:
		Notification();
		~Notification();
		//bool initialize(Camera &camera);
		void render(Camera &camera);
		//virtual void update(Camera &camera);
		void addNotification(string message);
		void setColor(SDL_Color color);
		/*void setFontSize(TTF_Font* ttf);*/
		void setImagePath(string path);
		string getImagePath();
		void setFont(TTF_Font* font);
		TTF_Font* getFont();
		StaticTextBox* newBox();
	private:
		StaticTextBox* currentBox;
		string imagePath;
		map<string,StaticTextBox*> boxMap;
        map<string,StaticTextBox*>::iterator boxIt;
		TTF_Font* font;
		SDL_Color currentColor;
	};

}


#endif