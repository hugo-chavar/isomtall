#include "StaticTextBox.h"
#include "Constants.h"


StaticTextBox::StaticTextBox() {
	this->_box = NULL;
	this->_font = NULL;
}

StaticTextBox::~StaticTextBox() {
	SDL_FreeSurface(_box);
	for (unsigned i =0;i < lines.size(); i++)	{
		lines[i]->liberar();
		delete lines[i];
	}
	if (_font)
		TTF_CloseFont(_font);
}

SDL_Surface *load_SDLimage(string filename)
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load(filename.c_str());

    //If the image loaded
    if(loadedImage != NULL)
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat(loadedImage);

        //Free the old image
        SDL_FreeSurface(loadedImage);

        //If the image was optimized just fine
        if(optimizedImage!=NULL)
        {
            //Map the color key
            Uint32 colorkey = SDL_MapRGB(optimizedImage->format, 0, 0xFF, 0xFF);

            //Set all pixels of color R 0, G 0xFF, B 0xFF to be transparent
            SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);
        }
    }

    //Return the optimized image
    return optimizedImage;
}

bool StaticTextBox::load(string imagePath, char *fontPath, int textSize) {
	//Load images
	this->_box = load_SDLimage(imagePath);
	//Open the font
	this->_font = TTF_OpenFont(fontPath, textSize);
	//If there was a problem in loading the background
	if (_box == NULL) {
		return false;
	}
	//If there was an error in loading the font
	if (this->_font == NULL) {
		return false;
	}
	//If everything loaded fine
	return true; 
}

bool StaticTextBox::initialize(string backgroundImagePath, SDL_Color color, char *fontPath, float offsetX, float offsetY,int textSize,int max_lines) {
	if (!load(backgroundImagePath, fontPath,textSize))
		return false;
	this->setTextColor(color);
	this->setTextSize(textSize);
	this->maxLines = max_lines;
	//_strTexts.push_back("");
	//_texts.push_back(NULL);
	_boxRect.x = static_cast<Sint16>(offsetX);
	_boxRect.y = static_cast<Sint16>(offsetY);
	_boxRect.w = static_cast<Uint16>(_box->w);
	_boxRect.h = static_cast<Uint16>(_box->h);
	/*_textRects.push_back(new SDL_Rect());
	_textRects[0]->x = _boxRect.x+10;
	_textRects[0]->y = _boxRect.y+5;
	_textRects[0]->w = _boxRect.w;
	_textRects[0]->h = _boxRect.h;*/
	this->addLine("");
	return true;
}

//void StaticTextBox::setLine(string text,int pos) {
//	lines[pos]->setLine(text,this->_font,this->_textColor);
//	_strTexts[pos] = text;
//	_texts[pos] = TTF_RenderText_Solid(_font, _strTexts[pos].c_str(), _textColor);
//}

void StaticTextBox::render(Camera &camera) {

	//Escribo en el fondo las lineas adecuadas
	camera.render(_boxRect, _box);
	int max = this->lines.size() - 1;
	for(unsigned i = 0; i < this->lines.size(); i++) {
		SDL_Rect rect;
		rect.x = static_cast<Sint16>(_boxRect.x+10);
		rect.y = static_cast<Sint16>(_boxRect.y+5+(max-i)*TTF_FontLineSkip(_font));
		camera.render(rect, lines[i]->getText());
	}
}

void StaticTextBox::update(float offsetX, float offsetY) {
	this->_boxRect.x = static_cast<Sint16>(offsetX);
	this->_boxRect.y = static_cast<Sint16>(offsetY);
}

float StaticTextBox::getOffsetX() {
	return this->_boxRect.x;
}

float StaticTextBox::getOffsetY() {
	return _boxRect.y;
}

int StaticTextBox::getHeight() {
	return this->_boxRect.h;
}

int StaticTextBox::getWidth() {
	return this->_boxRect.w;
}

//string StaticTextBox::getText(int pos)
//{
//	return this->_strText[pos];
//}

void StaticTextBox::addLine(string newMsg) {
	this->lines.push_back(new Line(newMsg, this->_font, this->_textColor));
	if (lines.size() > this->maxLines) {
		this->lines[0]->liberar();
		delete this->lines[0];
		this->lines.erase(this->lines.begin());
	}
}

vector <Line *> StaticTextBox::getLines() {
	return this->lines;
}

void StaticTextBox::setTextColor(SDL_Color color) {
	this->_textColor = color;
}

void StaticTextBox::setTextSize(int size) {
	this->_textSize = size;
	if (this->_font)
		TTF_CloseFont(this->_font);
	this->_font = TTF_OpenFont(DEFAULT_FONT_PATH, this->_textSize);
}