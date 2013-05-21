#pragma once

#include "Personaje.h"
#include "Stage.h"
#include "ChatView.h"
#include "ClientUpdater.h"
#include "CharacterFactory.h"
#include "Notification.h"

class GameView {
public:
	GameView(void);
	~GameView(void);
	bool initialize();
	view::Stage* getWorldView();
	Personaje* getMyPersonaje();
	Personaje* getPersonaje(string name);
	void newPersonaje(string name,string char_id);//ver como hacerlo  <---- Listo!
	void addPersonaje(string name,Personaje * personaje);
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
	bool insidePlayerVision(std::pair<int,int> pos);
	bool isKnownByPlayer(std::pair<int,int> pos);
	void startRenderingCharacters();
	Personaje* nextCharacter();
	void setConnected(bool state);
	void setLoggedIn(bool state);
	bool isThereAChar(string & name,int x,int y,float cameraX,float cameraY);
	SpriteAnimado* getErrorImage();

private:
	view::Camera camera;
	view::Stage worldView;
	Personaje* personaje;
	view::ChatView chat;
	view::Notification notification;
	bool connected;
	bool loggedIn;
	map <string, Personaje*> personajes;
	map <string, Personaje*>::iterator itPersonajes;
	string playerName; //este atributo se repite dentro del Personaje del cliente.
	string playerCharacterId;
	CharacterFactory characterFactory;
	SpriteAnimado* errorImage;
};

