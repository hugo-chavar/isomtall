#include "ChatView.h"

view::ChatView::ChatView() {
	this->initialized = false;
}

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
	textbox.setFont(this->getBigFont());
	if (!textbox.initialize("../Images/textbox.png", Camera::BLACK_COLOR , camera.getOffsetX()+camera.getWidth()-35, camera.getOffsetY()+5))
		return false;
	textbox.setOffsetX(camera.getOffsetX()+camera.getWidth()-textbox.getWidth()-5);
	if (!nameBox.initialize("../Images/nameBox.png", Camera::BLACK_COLOR, camera.getOffsetX()+5, camera.getOffsetY()+5,this->getBigFont(),1))
		return false;
	if (!messagesBox.initialize("../Images/messagesBox.png", Camera::BLACK_COLOR, textbox.getOffsetX(), textbox.getOffsetY()+nameBox.getHeight()+5, this->getSmallFont(),5))
		return false;
	if (!initializeCloseButton())
		return false;
	this->initialized = true;
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
	std::list<std::string>::iterator it;
	bool recibido=false;
	if (modelChat->getMessagesListMutex().tryLock()) {
		for ( it = modelChat->getMessagesList().begin(); it != modelChat->getMessagesList().end(); ++it) {
			messagesBox.addLine((*it));
			recibido=true;
		}
	}
	modelChat->getMessagesList().clear();
	modelChat->getMessagesListMutex().unlock();
	if(recibido)
	{
		this->setIsTyping(true);
	}
}

void view::ChatView::setTo(string To)
{
	this->nameBox.addLine(To);
}

void view::ChatView::setBigFont(TTF_Font* font) {
	this->bigFont = font;
}

void view::ChatView::setSmallFont(TTF_Font* font) {
	this->smallFont = font;
}

TTF_Font* view::ChatView::getBigFont() {
	return this->bigFont;
}

TTF_Font* view::ChatView::getSmallFont() {
	return this->smallFont;
}

bool view::ChatView::isInitialized() {
	return this->initialized;
}