#include "Textbox.h"


Textbox::Textbox() { }

Textbox::~Textbox() {
	//Free surfaces
	SDL_FreeSurface(box);
	SDL_FreeSurface(message);
	//Disable Unicode
	SDL_EnableUNICODE(SDL_DISABLE);
}

bool Textbox::initialize(string backgroundImagePath, SDL_Color color, char *fontPath, float offsetX, float offsetY, int textSize) {
	if (!load(backgroundImagePath, fontPath,textSize))
		return false;
	str = "";
	message = NULL;
	textColor = color;
	SDL_EnableUNICODE(SDL_ENABLE);
	boxRect.x = static_cast<Sint16>(offsetX);
	boxRect.y = static_cast<Sint16>(offsetY);
	boxRect.w = static_cast<Uint16>(box->w);
	boxRect.h = static_cast<Uint16>(box->h);
	messageRect.x = boxRect.x+10;
	messageRect.y = boxRect.y+5;
	messageRect.w = boxRect.w-21-10;
	messageRect.h = boxRect.h;
	return true;
}

SDL_Surface *load_image(string filename)
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

bool Textbox::load(string backgroundImagePath, char *fontPath, int textSize) {
	//Load images
	box = load_image(backgroundImagePath);
	//Open the font
	font = TTF_OpenFont(fontPath, textSize);
	//If there was a problem in loading the background
	if (box==NULL) {
		return false;
	}
	//If there was an error in loading the font
	if (font==NULL) {
		return false;
	}
	//If everything loaded fine
	return true; 
}

void Textbox::render(Camera &camera) {
	camera.render(boxRect, box);
	camera.render(messageRect, message);
}

void Textbox::update(float offsetX, float offsetY) {
	boxRect.x = static_cast<Sint16>(offsetX);
	boxRect.y = static_cast<Sint16>(offsetY);
	messageRect.x = boxRect.x+10;
	messageRect.y = boxRect.y+5;
}

void Textbox::handleInput(SDL_Event *sdlEvent) {
	//If a key was pressed
	if (sdlEvent->type==SDL_KEYDOWN) {
		//Keep a copy of the current version of the string
		string temp = str;
		//If the key is a symbol or character
		if ((sdlEvent->key.keysym.unicode>=(Uint16)' ') && (sdlEvent->key.keysym.unicode<=(Uint16)'ü')) {
			//Append the character
			str += (char)sdlEvent->key.keysym.unicode;
		}
		//If backspace was pressed and the string isn't blank
		if ((sdlEvent->key.keysym.sym==SDLK_BACKSPACE) && (str.length()!=0)) {
			//Remove a character from the end
			str.erase(str.length()-1);
		}
		//If the string was changed
		if (str!=temp) {
			//Free the old surface
			SDL_FreeSurface(message);
			//Render a new text surface
			message = TTF_RenderText_Solid(font, str.c_str(), textColor);
		}
	}
}

void Textbox::cleanTextBox() {
	str = "";
	//Free the old surface
	SDL_FreeSurface(message);
	//Render a new text surface
	message = TTF_RenderText_Solid(font, str.c_str(), textColor);
}

float Textbox::getOffsetX() {
	return boxRect.x;
}

void Textbox::setOffsetX(float offsetX) {
	boxRect.x = static_cast<Sint16>(offsetX);
	messageRect.x = static_cast<Sint16>(boxRect.x+10);
}

float Textbox::getOffsetY() {
	return boxRect.y;
}

int Textbox::getHeight() {
	return boxRect.h;
}

int Textbox::getWidth() {
	return boxRect.w;
}

string Textbox::getText()
{
	return this->str;
}