#include "ChatView.h"

view::ChatView::ChatView() { }

view::ChatView::~ChatView() {
	SDL_FreeSurface(closeButton);
	delete modelChat;
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

bool view::ChatView::initializeCloseButton() {
	closeButton = load_surface("../Images/closeButton.png");
	if (closeButton==NULL) {
		return false;
	}
	closeButtonRect.x = static_cast<Sint16>(textbox.getOffsetX()+textbox.getWidth()+6);
	closeButtonRect.y = static_cast<Sint16>(textbox.getOffsetY()+textbox.getHeight()-closeButton->h-5);
	closeButtonRect.w = static_cast<Uint16>(closeButton->w);
	closeButtonRect.h = static_cast<Uint16>(closeButton->h);
	return true;
}

bool view::ChatView::initialize(Camera &camera) {
	//Ver si es el lugar adecuado para hacerlo
	modelChat = new model::Chat();
	modelChat->initialize();
	SDL_Color textboxColor;
	textboxColor.r = 0;
	textboxColor.g = 0;
	textboxColor.b = 0;
	if (!textbox.initialize("../Images/textbox.png", textboxColor, "../Fonts/arial.ttf", camera.getOffsetX()+camera.getWidth()-35, camera.getOffsetY()+5,16))
		return false;
	textbox.setOffsetX(camera.getOffsetX()+camera.getWidth()-textbox.getWidth()-5);
	SDL_Color nameColor;
	nameColor.r = 0;
	nameColor.g = 0;
	nameColor.b = 0;
	if (!nameBox.initialize("../Images/nameBox.png", nameColor, "../Fonts/arial.ttf", camera.getOffsetX()+5, camera.getOffsetY()+5,16,1))
		return false;
	SDL_Color messagesColor;
	messagesColor.r = 0;
	messagesColor.g = 0;
	messagesColor.b = 0;
	if (!messagesBox.initialize("../Images/messagesBox.png", messagesColor, "../Fonts/arial.ttf", textbox.getOffsetX(), textbox.getOffsetY()+nameBox.getHeight()+5,10,5))
		return false;
	if (!initializeCloseButton())
		return false;
	return true;
}

bool view::ChatView::isTyping() {
	return typing;
}

void view::ChatView::setIsTyping(bool state) {
	typing = state;
}

void view::ChatView::render(Camera &camera) {
	nameBox.render(camera);
	messagesBox.render(camera);
	textbox.render(camera);
	camera.render(closeButtonRect, closeButton);
}

void view::ChatView::update(Camera &camera) {
	this->receiveMsgs();
	nameBox.update(camera.getOffsetX()+5, camera.getOffsetY()+5);
	textbox.update(camera.getOffsetX()+camera.getWidth()-textbox.getWidth()-35, camera.getOffsetY()+5);
	messagesBox.update(textbox.getOffsetX(), textbox.getOffsetY()+textbox.getHeight()+5);
	closeButtonRect.x = static_cast<Sint16>(textbox.getOffsetX()+textbox.getWidth()+6);
	closeButtonRect.y = static_cast<Sint16>(textbox.getOffsetY()+textbox.getHeight()-closeButton->h-5);
}

void view::ChatView::type(SDL_Event *sdlEvent) {
	textbox.handleInput(sdlEvent);
}

void view::ChatView::cleanInput() {
	textbox.cleanTextBox();
}

bool view::ChatView::isClosing(float x, float y) {
	if ((x>=closeButtonRect.x) && (x<=(closeButtonRect.x+closeButtonRect.w)) && (y>=closeButtonRect.y) && (y<=(closeButtonRect.y+closeButtonRect.h)))
		return true;
	return false;
}

void view::ChatView::sendMessage()
{
	modelChat->setInputBuffer(this->textbox.getText());
	modelChat->setTo(this->nameBox.getLines()[0]->getStrText());
	modelChat->sendMessage();
	this->cleanInput();
}

void view::ChatView::receiveMsgs()
{
	if (modelChat->getMessagesListMutex().tryLock()) {
		for (std::list<std::string>::iterator it = modelChat->getMessagesList().begin(); it != modelChat->getMessagesList().end(); ++it) {
			messagesBox.addLine((*it));
		}
	}
	modelChat->getMessagesList().clear();
	modelChat->getMessagesListMutex().unlock();
}

void view::ChatView::setTo(string To)
{
	this->nameBox.addLine(To);
}