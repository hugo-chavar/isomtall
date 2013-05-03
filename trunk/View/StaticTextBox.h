#ifndef _STATICTEXTBOX_H_
#define _STATICTEXTBOX_H_

#include "Camera.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include <string>
#include <vector>
#include "Line.h"


using namespace view;
using namespace std;


class StaticTextBox {

public:
	StaticTextBox();
	~StaticTextBox();
	bool initialize(string backgroundImagePath, SDL_Color color, char *fontPath, float offsetX, float offsetY,int textSize,int maxLines);
	virtual void render(Camera &camera);
	virtual void update(float offsetX, float offsetY);
	//void setText(string text,int pos);
	//void setLine(string text,int pos);
	float getOffsetX();
	float getOffsetY();
	int getWidth();
	int getHeight();
	vector<Line *> getLines();
	//string getText(int pos);
	void addLine(string newMsg);

private:
	SDL_Surface *_box;
	SDL_Rect _boxRect;
	SDL_Color _textColor;
	TTF_Font *_font;
	unsigned maxLines;
	vector<Line *> lines;
	//vector<SDL_Surface *> _texts;//convendria encapsularlo
	//vector<SDL_Rect *> _textRects;//convendria encapsularlo
	//vector<string> _strTexts;//
	bool load(string imagePath, char *fontPath, int textSize);

};


#endif