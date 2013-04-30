#include "Textbox.h"


Textbox::Textbox() { }

Textbox::~Textbox() {
	//Free surfaces
	SDL_FreeSurface(background);
	SDL_FreeSurface(closeButton);
	SDL_FreeSurface(message);
	//Disable Unicode
	SDL_EnableUNICODE(SDL_DISABLE);
}

bool Textbox::initialize(Camera &camera) {
	if (!load())
		return false;
	str = "";
	message = NULL;
	textColor.r = 0;
	textColor.g = 0;
	textColor.b = 0;
	SDL_EnableUNICODE(SDL_ENABLE);
	rectangle.x = camera.getOffsetX()+camera.getWidth()-background->w-5;
	rectangle.y = camera.getOffsetY()+5;
	rectangle.w = background->w;
	rectangle.h = background->h;
	closeButtonRect.x = rectangle.x+rectangle.w-closeButton->w-5;
	closeButtonRect.y = rectangle.y+rectangle.h-closeButton->h-5;
	closeButtonRect.w = closeButton->w;
	closeButtonRect.h = closeButton->h;
	messageRect.x = rectangle.x+5;
	messageRect.y = rectangle.y+5;
	messageRect.w = rectangle.w-closeButtonRect.w-10;
	messageRect.h = rectangle.h;
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

bool Textbox::load() {
	//Load images
	background = load_image("../Images/textbox.png");
	closeButton = load_image("../Images/closeButton.png");
	//Open the font
	font = TTF_OpenFont("../Fonts/arial.ttf", 16);
	//If there was a problem in loading the background
	if (background==NULL) {
		return false;
	}
	if (closeButton==NULL) {
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
	//message = TTF_RenderText_Solid(font, "The quick brown fox jumps over the lazy dog", textColor);
	camera.render(rectangle, background);
	camera.render(closeButtonRect, closeButton);
	camera.render(messageRect, message);
}

void Textbox::update(Camera &camera) {
	rectangle.x = camera.getOffsetX()+camera.getWidth()-background->w-5;
	rectangle.y = camera.getOffsetY()+5;
	closeButtonRect.x = rectangle.x+rectangle.w-closeButton->w-5;
	closeButtonRect.y = rectangle.y+rectangle.h-closeButton->h-5;
	messageRect.x = rectangle.x+5;
	messageRect.y = rectangle.y+5;
}

void Textbox::handleInput(SDL_Event *sdlEvent) {
	//If a key was pressed
	if (sdlEvent->type==SDL_KEYDOWN) {
		//Keep a copy of the current version of the string
		string temp = str;
		//If the key is a space
		if (sdlEvent->key.keysym.unicode==(Uint16)' ') {
			//Append the character
			str += (char)sdlEvent->key.keysym.unicode;
		}
		//If the key is a number
		else
			if ((sdlEvent->key.keysym.unicode>=(Uint16)'0') && (sdlEvent->key.keysym.unicode<=(Uint16)'9')) {
				//Append the character
				str += (char)sdlEvent->key.keysym.unicode;
			}
			//If the key is a uppercase letter
			else
				if ((sdlEvent->key.keysym.unicode>=(Uint16)'A') && (sdlEvent->key.keysym.unicode<=(Uint16)'Z')) {
					//Append the character
					str += (char)sdlEvent->key.keysym.unicode;
				}
				//If the key is a lowercase letter
				else if ((sdlEvent->key.keysym.unicode>=(Uint16)'a') && (sdlEvent->key.keysym.unicode<=(Uint16)'z')) {
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

bool Textbox::pressingClosingBox(int x, int y) {
	if ((x>=closeButtonRect.x) && (x<=(closeButtonRect.x+closeButtonRect.w)) && (y>=closeButtonRect.y) && (y<=(closeButtonRect.y+closeButtonRect.h)))
		return true;
	return false;
}

void Textbox::cleanTextBox() {
	str = "";
	//Free the old surface
	SDL_FreeSurface(message);
	//Render a new text surface
	message = TTF_RenderText_Solid(font, str.c_str(), textColor);
}

int Textbox::getOffsetX() {
	return rectangle.x;
}

int Textbox::getOffsetY() {
	return rectangle.y;
}

int Textbox::getHeight() {
	return rectangle.h;
}

int Textbox::getWidth() {
	return rectangle.w;
}

/*
Chat::Chat(Sprite *spriteCargado) {
	sprite = spriteCargado;
	spriteRect.x = 0;
	spriteRect.y = 0;
	spriteRect.w = (Uint16)(sprite->getFrameActual()->getSuperficie()->w);
	spriteRect.h = (Uint16)(sprite->getFrameActual()->getSuperficie()->h);
}

bool Chat::initialize() {
	//Initialize SDL_ttf
	if (TTF_Init()==-1) {
		return false;
	}
	return true;
}
*/