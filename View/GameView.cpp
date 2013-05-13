#include "GameView.h"


GameView::GameView(void)
{
}


GameView::~GameView(void)
{
}

bool GameView::initialize(view::Camera camera)
{
		bool mapInitialized = worldView.initialize();
		bool chatInitialized = chat.initialize(camera);
		return (mapInitialized && chatInitialized);
}

GameView& GameView::instance() {
	static GameView singleton;
	return singleton;
}

view::Stage* GameView::getWorldView() {
	return &worldView;
}

view::Chat* GameView::getChat() {
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

Personaje* GameView::getMyPersonaje()
{
	return personaje;
}