#include "GameView.h"
#include "TileModel.h"


GameView::GameView(void) {
	this->errorImage = NULL;
}

GameView::~GameView(void) {
	map<string, Personaje*>::iterator it;
	it = personajes.begin();
	for( ;it != personajes.end(); it++) {
		if ((*it).second)
			delete (*it).second;
	}
	if (errorImage != NULL) {
		delete errorImage;
	}
}

bool GameView::initialize() {
	bool cameraInitialized = this->camera.initialize();
	bool mapInitialized = false;
	bool textInitialized = true;
	bool chatInitialized = false;
	bool notificationInitialized = false;
	this->serverReached = true;

	this->chat.setIsTyping(false);

	//Initialize SDL_ttf
	if (TTF_Init() == -1)
		textInitialized = false;

	if (cameraInitialized) {
		notificationInitialized = notification.initialize(camera);
		if ( (this->getStatus() == STATUS_FILES_UPDATED_OK) ||(this->getStatus() == STATUS_SIMULATION_CONNECTED)) {
			mapInitialized = worldView.initialize();
			chatInitialized = chat.initialize(camera);
			worldView.setTilesInCamera(this->camera.getWidth(), this->camera.getHeight());
			this->personaje = characterFactory.createViewCharacter(this->getPlayerCharacterId(), this->getPlayerName());
			this->addPersonaje(this->getPlayerName(), this->personaje);
			if (!mapInitialized)
				this->setStatus(STATUS_INIT_ERROR);
		}
	}
	

	//si hubo errores de inicializacion salgo
	bool running = mapInitialized & cameraInitialized & textInitialized; 

	if (mapInitialized) {
		//TODO: cambiar por this->camera.setCenterPixel(worldView.personaje()->getPixelPosition());
		std::pair<int,int> posPersonaje = this->personaje->getPixelPosition();
		this->camera.setOffsetX(static_cast<float>(posPersonaje.first-332));
		this->camera.setOffsetY(static_cast<float>(posPersonaje.second-204));
		AnimatedEntity errorEntity;
		errorEntity.loadImages(ERROR_ANIMATED_DIR);
		errorEntity.delay(0);
		this->errorImage = new SpriteAnimado(&errorEntity);
	}

	return running;
}

GameView& GameView::instance() {
	static GameView singleton;
	return singleton;
}

view::Stage* GameView::getWorldView() {
	return &worldView;
}

Camera* GameView::getCamera() {
	return &camera;
}

view::ChatView* GameView::getChat() {
	return &chat;
}

Personaje* GameView::getPersonaje(string name) {
	Personaje* personaje = NULL;
	map<string, Personaje*>::iterator it;
	it = this->personajes.find(name);

	if (it != this->personajes.end())
		personaje = it->second;

	return personaje;
}

void GameView::newPersonaje(string name, string char_id) {
	Personaje* personaje = characterFactory.createViewCharacter(char_id, name);
	this->addPersonaje(name, personaje);
}

void GameView::addPersonaje(string name,Personaje * personaje) {
	this->personajes.insert(std::make_pair<string,Personaje *>(name,personaje));
}

Personaje* GameView::getMyPersonaje() {
	if (this->personaje) {
		return this->personaje;
	}
	Logger::instance().nullPointer("function Personaje* GameView::getMyPersonaje");
	return NULL;
}

void GameView::setPlayerName(string name) {
	this->playerName = name;
}

string GameView::getPlayerName() {
	return this->playerName;
}

void GameView::setPlayerCharacterId(string char_id) {
	playerCharacterId = char_id;
}

string GameView::getPlayerCharacterId() {
	return this->playerCharacterId;
}

void GameView::cleanUp() {
	this->camera.cleanUp();
	if ((this->getStatus() == STATUS_SIMULATION_CONNECTED)||(this->getStatus() == STATUS_SIMULATION_CONNECTION_LOST)) {
		this->chat.modelChat->cleanUp();
	}
}

void GameView::render() {

	SDL_FillRect(this->camera.cameraSurface, NULL, 0);

	if (this->getStatus() != STATUS_SIMULATION_CONNECTED) {
		this->notification.render(this->camera);
	} else {
		this->worldView.render(this->camera);
		if (chat.isTyping())
			this->chat.render(this->camera);
	}

	SDL_Flip(this->camera.cameraSurface);

}

SpriteAnimado* GameView::getErrorImage() {
	return errorImage;
}


void GameView::update() {

	this->camera.update();

	switch (this->getStatus()) {
		case STATUS_INIT_ERROR:
			this->notification.addNotification("      ERROR LOADING CLIENT");
			this->notification.update(camera);
			this->notification.setColor(Camera::RED_COLOR);
			this->notification.setFontSize(24);
		break;
		case STATUS_SERVER_UNREACHEABLE:
			this->notification.addNotification("        SERVER UNREACHABLE");
			this->notification.update(camera);
			this->notification.setColor(Camera::RED_COLOR);
		break;
		case STATUS_UPDATING_FILES:
			this->notification.addNotification("        UPDATING FILES");
			this->notification.update(camera);
			this->notification.setColor(Camera::BLACK_COLOR);
			this->notification.setFontSize(24);
		break;
		case STATUS_FILES_UPDATED_OK:
			
		break;
		case STATUS_UPDATING_CONNECTION_LOST:
			this->notification.addNotification("UPDATED FAILED CONNECTION LOST");
			this->notification.update(camera);
			this->notification.setColor(Camera::RED_COLOR);
			this->notification.setFontSize(20);
		break;
		case STATUS_SIMULATION_CONNECTED:
			this->worldView.update();
			this->chat.update(camera);
		break;
		case STATUS_SIMULATION_CONNECTION_LOST:
			this->notification.addNotification("   SERVER CONNECTION LOST");
			this->notification.update(camera);
			this->notification.setColor(Camera::RED_COLOR);
			this->notification.setFontSize(24);
		break;
		case STATUS_LOGIN_FAILED:
			this->notification.addNotification(" LOGIN FAILED USER NAME UNAVAILABLE");
			this->notification.update(camera);
			this->notification.setColor(Camera::RED_COLOR);
			this->notification.setFontSize(15);
		break;
	}

	//agregar update personajes
}

bool GameView::insidePlayerVision(std::pair<int,int> pos) {
	bool inside = this->getMyPersonaje()->personajeModelo()->getVision()->isInsideVision(pos);

	if (!inside) {
		TileModel* relatedTile = this->worldView.getWorldModel()->getTileAt(pos)->getRelatedTile();
		if (relatedTile) {//TODO: mejorar para optimizar codigo
			// preguntar si es drawable() e ir salteando..
			while ( (!inside) && (relatedTile != this->getWorldView()->getWorldModel()->getTileAt(pos)) ) {
				pair<int, int> posRelated = relatedTile->getPosition();
				inside = this->getMyPersonaje()->personajeModelo()->getVision()->isInsideVision(posRelated);
				relatedTile = relatedTile->getRelatedTile();
			}
		}
	}
	return inside;
}

bool GameView::isKnownByPlayer(std::pair<int,int> pos) { 
	return  this->getMyPersonaje()->personajeModelo()->getVision()->testPosition(pos);
}

void GameView::startRenderingCharacters() { 
	this->itPersonajes = this->personajes.begin();
}

Personaje* GameView::nextCharacter() { 
	Personaje* aux = NULL;
	if (this->itPersonajes != this->personajes.end()) {
		aux = this->itPersonajes->second;
		this->itPersonajes++;
	}
	return aux;
}

bool GameView::isThereAChar(string & name,int x,int y,float cameraX,float cameraY) {
	pair<int,int> tilePos = Game::instance().world()->destination(x,y,cameraX,cameraY);
	if(Game::instance().world()->isInsideWorld(tilePos))
	{
		map <string, Personaje*>::iterator it;
		for(it=this->personajes.begin(); it!=this->personajes.end(); it++)
		{
			pair<int,int> posChar = (*it).second->getPosicionEnTiles();
			if(posChar == tilePos)
			{
				name = (*it).first;
				return true;
			}
		}
	}
	return false;
}

void GameView::setStatus(gameStatus_t status) {
	this->gameStatus = status;
}

gameStatus_t GameView::getStatus() {
	return this->gameStatus;
}