#pragma once

#include "Personaje.h"
#include "Stage.h"
#include "Chat.h"

class GameView
{
public:
	GameView(void);
	~GameView(void);
	bool initialize(view::Camera camera);
	view::Stage* getWorldView();
	Personaje* getMyPersonaje();
	Personaje* getPersonaje(string name);
	view::Chat* getChat();
	static GameView& instance();

private:
	view::Stage worldView;
	Personaje* personaje;
	view::Chat chat;
	map <string,Personaje*> personajes;//agrego diccionario de personajes
};

