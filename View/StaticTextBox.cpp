#include "StaticTextBox.h"

StaticTextBox::StaticTextBox() { }

StaticTextBox::~StaticTextBox() {
	SDL_FreeSurface(_box);
	SDL_FreeSurface(_text);
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
    if(loadedImage!=NULL)
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

bool StaticTextBox::load(string imagePath) {
	//Load images
	_box = load_SDLimage(imagePath);
	//Open the font
	_font = TTF_OpenFont("../Fonts/arial.ttf", 16);
	//If there was a problem in loading the background
	if (_box==NULL) {
		return false;
	}
	//If there was an error in loading the font
	if (_font==NULL) {
		return false;
	}
	//If everything loaded fine
	return true; 
}

bool StaticTextBox::initialize(string backgroundImagePath, string text, int offsetX, int offsetY) {
	if (!load(backgroundImagePath))
		return false;
	_textColor.r = 0;
	_textColor.g = 0;
	_textColor.b = 0;
	_strText = text; // DE PRUEBA
	_text = TTF_RenderText_Solid(_font, _strText.c_str(), _textColor); // DE PRUEBA
	//_strText = "";
	//_text = NULL;
	_boxRect.x = offsetX;
	_boxRect.y = offsetY;
	_boxRect.w = _box->w;
	_boxRect.h = _box->h;
	_textRect.x = _boxRect.x+10;
	_textRect.y = _boxRect.y+5;
	_textRect.w = _boxRect.w;
	_textRect.h = _boxRect.h;
}

void StaticTextBox::render(Camera &camera) {
	camera.render(_boxRect, _box);
	camera.render(_textRect, _text);
}

void StaticTextBox::update(int offsetX, int offsetY) {
	_boxRect.x = offsetX;
	_boxRect.y = offsetY;
	_textRect.x = _boxRect.x+10;
	_textRect.y = _boxRect.y+5;
}

int StaticTextBox::getOffsetX() {
	return _boxRect.x;
}

int StaticTextBox::getOffsetY() {
	return _boxRect.y;
}

int StaticTextBox::getHeight() {
	return _boxRect.h;
}

int StaticTextBox::getWidth() {
	return _boxRect.w;
}