#include "GameView.h"


GameView::GameView(void)
{
}


GameView::~GameView(void)
{
	std::map<std::string,Personaje*>::iterator it=personajes.begin();
	for(it;it!=personajes.end();it++)
	{
		delete (*it).second;
	}
}

bool GameView::initialize()
{
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

	//si hubo errores de inicializacion salgo
	bool running = mapInitialized & cameraInitialized & textInitialized; 

	if (running) {
		std::pair<int,int> posPersonaje=worldView.personaje()->posicion();
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

Personaje* GameView::getPersonaje(string name)
{
	Personaje* personaje = NULL;
	std::map<std::string,Personaje*>::iterator it = this->personajes.find(name);

	if (it != this->personajes.end())
		personaje = it->second;

	return personaje;
}

void GameView::addPersonaje(string name,string char_id){
	Personaje* personaje=new Personaje(NULL);
	this->personajes.insert(std::pair<string,Personaje *>(name,personaje));
	//Aca deberia relacionarle al personaje su sprite, a partir del char_id, el cual deberia ya estar cargado en memoria
}


Personaje* GameView::getMyPersonaje()
{
	if (this->personaje){
		return this->personaje;
	}
	Logger::instance().nullPointer("function Personaje* GameView::getMyPersonaje");
	return NULL;
}

void GameView::setPlayerName(string name) {
	this->playerName=name;
}

string GameView::getPlayerName() {

	return this->playerName;
}

void GameView::setPlayerCharacterId(string char_id)
{
	playerCharacterId=char_id;
}
string GameView::getPlayerCharacterId()
{
	return this->playerCharacterId;
}

void GameView::cleanUp() {

	this->camera.cleanUp();

	this->chat.modelChat->cleanUp();

}

void GameView::render()
{

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
}