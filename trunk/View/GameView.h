#pragma once

#include "Personaje.h"
#include "Stage.h"
#include "ChatView.h"
#include "ClientUpdater.h"
#include "CharacterFactory.h"
#include "Notification.h"

enum gameStatus_t {
	STATUS_UPDATING_FILES,
	STATUS_SERVER_UNREACHEABLE,
	STATUS_UPDATING_CONNECTION_LOST,
	STATUS_FILES_UPDATED_OK,
	STATUS_INIT_ERROR,
	STATUS_LOGIN_FAILED,
	STATUS_SIMULATION_CONNECTED,
	STATUS_SIMULATION_CONNECTION_LOST
};


class GameView {
public:
	GameView(void);
	~GameView(void);
	bool initialize();
	view::Stage* getWorldView();
	Personaje* getMyPersonaje();
	Personaje* getPersonaje(string name);
	void newPersonaje(string name,string char_id);
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
	void setStatus(gameStatus_t status);
	gameStatus_t getStatus();
	bool isThereAChar(string & name,int x,int y,float cameraX,float cameraY);
	SpriteAnimado* getErrorImage();
	void setActivatedAt(int activeAt);
	int getActivatedAt();

private:
	view::Camera camera;
	view::Stage worldView;
	Personaje* personaje;
	view::ChatView chat;
	view::Notification notification;
	bool connected;
	//bool firstConnection;
	bool serverReached;
	map <string, Personaje*> personajes;
	map <string, Personaje*>::iterator itPersonajes;
	string playerName; //este atributo se repite dentro del Personaje del cliente.
	string playerCharacterId;
	CharacterFactory characterFactory;
	SpriteAnimado* errorImage;
	int activatedAt;
	gameStatus_t gameStatus;
};

