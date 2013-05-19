#include "GameView.h"
#include "TileModel.h"


GameView::GameView(void) {
}

GameView::~GameView(void) {
	map<string, Personaje*>::iterator it = personajes.begin();
	for( ;it != personajes.end(); it++) {
		//if (it->second != this->worldView.personaje()) Andy para que estaba este if???
			delete (*it).second;
	}
}

bool GameView::initialize() {
	bool cameraInitialized = this->camera.initialize();
	bool mapInitialized = false;
	bool textInitialized = true;
	bool chatInitialized = false;

	this->chat.setIsTyping(false);

	//Initialize SDL_ttf
	if (TTF_Init()==-1)
		textInitialized = false;

	if (cameraInitialized){
		mapInitialized = worldView.initialize();
		chatInitialized = chat.initialize(camera);
		worldView.setTilesInCamera(this->camera.getWidth(), this->camera.getHeight());
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
	map<string, Personaje*>::iterator it = this->personajes.find(name);

	if (it != this->personajes.end())
		personaje = it->second;

	return personaje;
}

//Falta implementar este metodo
void GameView::newPersonaje(string name, string char_id) {
	//if (this->getPersonaje(name))
	//	return; //si ya existe salgo, faltaria chequear si cambio de char_id.. pero eso es otro tema

	Personaje* personaje = characterFactory.createViewCharacter(char_id, name);
	//Aca deberia relacionarle al personaje su sprite, a partir del char_id, el cual deberia ya estar cargado en memoria
	//Hugo: andy esto que decis lo hace automaticamente el characterFactory
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

void GameView::render() {
	SDL_FillRect(this->camera.cameraSurface,NULL,0);
	this->worldView.render(this->camera);
	if (chat.isTyping())
		this->chat.render(this->camera);
	SDL_Flip(this->camera.cameraSurface);

}

void GameView::update() {
	this->camera.update();
	this->worldView.update();
	this->chat.update(camera);
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