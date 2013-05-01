#include "Chat.h"


Chat::Chat() { }

Chat::~Chat() {
	SDL_FreeSurface(nameBox);
	SDL_FreeSurface(nameText);
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

bool Chat::load() {
	//Load images
	nameBox = load_SDLimage("../Images/nameBox.png");
	messagesBox = load_SDLimage("../Images/messagesBox.png");
	//Open the font
	font = TTF_OpenFont("../Fonts/arial.ttf", 16);
	//If there was a problem in loading the background
	if (nameBox==NULL) {
		return false;
	}
	if (messagesBox==NULL) {
		return false;
	}
	//If there was an error in loading the font
	if (font==NULL) {
		return false;
	}
	//If everything loaded fine
	return true; 
}

bool Chat::initialize(Camera &camera) {
	if (!textbox.initialize(camera))
		return false;
	if (!load())
		return false;
	textColor.r = 0;
	textColor.g = 0;
	textColor.b = 0;
	name = "Jugador 1"; // DE PRUEBA
	nameText = TTF_RenderText_Solid(font, name.c_str(), textColor); // DE PRUEBA
	//name = "";
	//nameText = NULL;
	messages = "Hola"; // DE PRUEBA
	messagesText = TTF_RenderText_Solid(font, messages.c_str(), textColor); // DE PRUEBA
	//messages = "";
	//messagesText = NULL;
	nameBoxRect.x = camera.getOffsetX()+5;
	nameBoxRect.y = camera.getOffsetY()+5;
	nameBoxRect.w = nameBox->w;
	nameBoxRect.h = nameBox->h;
	nameTextRect.x = nameBoxRect.x+10;
	nameTextRect.y = nameBoxRect.y+5;
	nameTextRect.w = nameBox->w;
	nameTextRect.h = nameBox->h;
	messagesBoxRect.x = nameBoxRect.x;
	messagesBoxRect.y = nameBoxRect.y+nameBoxRect.h+10;
	messagesBoxRect.w = messagesBox->w;
	messagesBoxRect.h = messagesBox->h;
	messagesTextRect.x = messagesBoxRect.x+10;
	messagesTextRect.y = messagesBoxRect.y+5;
	messagesTextRect.w = messagesBoxRect.w;
	messagesTextRect.h = messagesBoxRect.h;
	return true;
}

bool Chat::isTyping() {
	return typing;
}

void Chat::setIsTyping(bool state) {
	typing = state;
}

void Chat::render(Camera &camera) {
	camera.render(nameBoxRect, nameBox);
	camera.render(nameTextRect, nameText);
	camera.render(messagesBoxRect, messagesBox);
	camera.render(messagesTextRect, messagesText);
	textbox.render(camera);
}

void Chat::update(Camera &camera) {
	nameBoxRect.x = camera.getOffsetX()+5;
	nameBoxRect.y = camera.getOffsetY()+5;
	nameTextRect.x = nameBoxRect.x+10;
	nameTextRect.y = nameBoxRect.y+5;
	messagesBoxRect.x = nameBoxRect.x;
	messagesBoxRect.y = nameBoxRect.y+nameTextRect.h+10;
	messagesTextRect.x = messagesBoxRect.x+10;
	messagesTextRect.y = messagesBoxRect.y+5;
	textbox.update(camera);
}

void Chat::type(SDL_Event *sdlEvent) {
	textbox.handleInput(sdlEvent);
}

void Chat::cleanInput() {
	textbox.cleanTextBox();
}

bool Chat::isClosing(int x, int y) {
	return textbox.pressingClosingBox(x, y);
}