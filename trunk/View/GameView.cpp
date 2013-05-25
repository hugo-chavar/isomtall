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
	this->firstConnection = false;
	//connected = true;

	this->chat.setIsTyping(false);

	//Initialize SDL_ttf
	if (TTF_Init()==-1)
		textInitialized = false;

	if (cameraInitialized){
		mapInitialized = worldView.initialize();
		chatInitialized = chat.initialize(camera);
		worldView.setTilesInCamera(this->camera.getWidth(), this->camera.getHeight());
		notificationInitialized = notification.initialize(camera);
	}
	this->personaje = characterFactory.createViewCharacter(this->getPlayerCharacterId(), this->getPlayerName());
	this->addPersonaje(this->getPlayerName(), this->personaje);

	//si hubo errores de inicializacion salgo
	bool running = mapInitialized & cameraInitialized & textInitialized; 

	if (running) {
		//TODO: cambiar por this->camera.setCenterPixel(worldView.personaje()->getPixelPosition());
		std::pair<int,int> posPersonaje = this->personaje->getPixelPosition();
		this->camera.setOffsetX(static_cast<float>(posPersonaje.first-332));
		this->camera.setOffsetY(static_cast<float>(posPersonaje.second-204));

		AnimatedEntity errorEntity;
	
		errorEntity.loadImages(ERROR_ANIMATED_DIR);

		errorEntity.delay(0);

		errorImage = new SpriteAnimado(&errorEntity);
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
	this->chat.modelChat->cleanUp();
}

void GameView::setConnected(bool state) {
	this->connected = state;
}

void GameView::setFirstConnection(bool state) {
	this->firstConnection = state;
}

void GameView::setServerReached(bool state) {
	this->serverReached = state;
}

void GameView::render() {
	SDL_FillRect(this->camera.cameraSurface,NULL,0);
	this->worldView.render(this->camera);
	if (chat.isTyping())
		this->chat.render(this->camera);
	if (!connected)
		this->notification.render(this->camera);
	SDL_Flip(this->camera.cameraSurface);

}

SpriteAnimado* GameView::getErrorImage() {
	return errorImage;
}


void GameView::update() {
	this->camera.update();
	this->worldView.update();
	this->chat.update(camera);

	/*STATUS_CONNECTING_TO_SERVER,
	STATUS_SERVER_UNREACHEABLE,
	STATUS_UPDATING_FILES,
	STATUS_FILES_UPDATED_OK,
	STATUS_UPDATING_CONNECTION_LOST,
	STATUS_CONNECTING_TO_SIMULATION,
	STATUS_SIMULATION_CONNECTED,
	STATUS_SIMULATION_DISCONNECTED,
	STATUS_SIMULATION_CONNECTION_LOST */

	switch (this->getStatus()) {
		case STATUS_CONNECTING_TO_SERVER:
			this->notification.addNotification("        SERVER UNREACHABLE");
			this->notification.update(camera);
		break;
		case STATUS_SERVER_UNREACHEABLE:
			this->notification.addNotification("        SERVER UNREACHABLE");
			this->notification.update(camera);
		break;
		case STATUS_UPDATING_FILES:
			
		break;
		case STATUS_FILES_UPDATED_OK:
			
		break;
		case STATUS_UPDATING_CONNECTION_LOST:
			
		break;
		case STATUS_CONNECTING_TO_SIMULATION:
			
		break;
	}

	if (!serverReached) {
		this->notification.addNotification("        SERVER UNREACHABLE");
		this->notification.update(camera);
		this->notification.setColor(Camera::BLACK_COLOR);
	}
	else {
		if (!this->connected) {
			if (this->firstConnection) {
				this->notification.addNotification("CONNECTION WITH SERVER LOST");
				this->notification.update(camera);
				this->notification.setColor(Camera::RED_COLOR);
			}
			else {
				this->notification.addNotification("      CONNECTING TO SERVER");
				this->notification.update(camera);
				this->notification.setColor(Camera::GREEN_COLOR);
			}
		}
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