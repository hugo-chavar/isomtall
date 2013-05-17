#pragma once

#include "Personaje.h"
#include "Stage.h"
#include "ChatView.h"
#include "ClientUpdater.h"

class GameView
{
public:
	GameView(void);
	~GameView(void);
	bool initialize();
	view::Stage* getWorldView();
	Personaje* getMyPersonaje();
	Personaje* getPersonaje(string name);
	void addPersonaje(string name,string char_id);
	view::ChatView* getChat();
	Camera* getCamera();
	static GameView& instance();
	void setPlayerName(string name);
	string getPlayerName();
	void setPlayerCharacterId(string char_id);
	string getPlayerCharacterId();
	void cleanUp();
	void render();
	void update();


private:
	view::Camera camera;
	view::Stage worldView;
	Personaje* personaje;
	view::ChatView chat;
	map <string,Personaje*> personajes;//agrego diccionario de personajes
	std::string playerName;
	std::string playerCharacterId;
};

