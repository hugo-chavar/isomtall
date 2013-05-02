#include "Chat.h"


Chat::Chat() { }

Chat::~Chat() {
	SDL_FreeSurface(closeButton);
}

SDL_Surface *load_surface(string filename)
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

bool Chat::initializeCloseButton() {
	closeButton = load_surface("../Images/closeButton.png");
	if (closeButton==NULL) {
		return false;
	}
	closeButtonRect.x = static_cast<Sint16>(textbox.getOffsetX()+textbox.getWidth()-closeButton->w-5);
	closeButtonRect.y = static_cast<Sint16>(textbox.getOffsetY()+textbox.getHeight()-closeButton->h-5);
	closeButtonRect.w = static_cast<Uint16>(closeButton->w);
	closeButtonRect.h = static_cast<Uint16>(closeButton->h);
}

bool Chat::initialize(Camera &camera) {
	SDL_Color textboxColor;
	textboxColor.r = 0;
	textboxColor.g = 0;
	textboxColor.b = 0;
	if (!textbox.initialize("../Images/textbox.png", textboxColor, "../Fonts/arial.ttf", camera.getOffsetX()+camera.getWidth()-5, camera.getOffsetY()+5))
		return false;
	textbox.setOffsetX(camera.getOffsetX()+camera.getWidth()-textbox.getWidth()-5);
	SDL_Color nameColor;
	nameColor.r = 0;
	nameColor.g = 0;
	nameColor.b = 0;
	if (!nameBox.initialize("../Images/nameBox.png", nameColor, "../Fonts/arial.ttf", camera.getOffsetX()+5, camera.getOffsetY()+5))
		return false;
	SDL_Color messagesColor;
	messagesColor.r = 0;
	messagesColor.g = 0;
	messagesColor.b = 0;
	if (!messagesBox.initialize("../Images/messagesBox.png", messagesColor, "../Fonts/arial.ttf", nameBox.getOffsetX(), nameBox.getOffsetY()+nameBox.getHeight()+10))
		return false;
	////// PRUEBA
	nameBox.setText("Jugador 1");
	messagesBox.setText("Hola");
	//////
	if (!initializeCloseButton())
		return false;
	return true;
}

bool Chat::isTyping() {
	return typing;
}

void Chat::setIsTyping(bool state) {
	typing = state;
}

void Chat::render(Camera &camera) {
	nameBox.render(camera);
	messagesBox.render(camera);
	textbox.render(camera);
	camera.render(closeButtonRect, closeButton);
}

void Chat::update(Camera &camera) {
	nameBox.update(camera.getOffsetX()+5, camera.getOffsetY()+5);
	messagesBox.update(nameBox.getOffsetX(), nameBox.getOffsetY()+nameBox.getHeight()+10);
	textbox.update(camera.getOffsetX()+camera.getWidth()-textbox.getWidth()-5, camera.getOffsetY()+5);
	closeButtonRect.x = static_cast<Sint16>(textbox.getOffsetX()+textbox.getWidth()-closeButton->w-5);
	closeButtonRect.y = static_cast<Sint16>(textbox.getOffsetY()+textbox.getHeight()-closeButton->h-5);
}

void Chat::type(SDL_Event *sdlEvent) {
	textbox.handleInput(sdlEvent);
}

void Chat::cleanInput() {
	textbox.cleanTextBox();
}

bool Chat::isClosing(float x, float y) {
	if ((x>=closeButtonRect.x) && (x<=(closeButtonRect.x+closeButtonRect.w)) && (y>=closeButtonRect.y) && (y<=(closeButtonRect.y+closeButtonRect.h)))
		return true;
	return false;
}