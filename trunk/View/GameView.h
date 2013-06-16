#ifndef _GAMEVIEW_H_
#define _GAMEVIEW_H_

#ifndef gameStatus_t
#define gameStatus_t
enum gameStatus_t {
	STATUS_BAD_CLICK,
	STATUS_READY_TO_UPDATE,
	STATUS_UPDATING_FILES ,
	STATUS_SERVER_UNREACHEABLE,
	STATUS_UPDATING_CONNECTION_LOST,
	STATUS_FILES_UPDATED_OK,
	STATUS_LOGIN_REQUESTED,
	STATUS_INIT_ERROR,
	STATUS_LOGIN_USER_FAILED,
	STATUS_LOGIN_CONNECTION_LOST,
	STATUS_SIMULATION_TRY_CONNECT,
	STATUS_SIMULATION_CONNECTED,
	STATUS_SIMULATION_READY_TO_RECONNECT,
	STATUS_SIMULATION_PLAYING_SINGLEPLAYER,
	STATUS_SIMULATION_CONNECTION_LOST,
	STATUS_SIMULATION_SINGLE_PLAYER,
	STATUS_START_SCREEN,
	STATUS_GAME_OVER,
	STATUS_RESTART_GAME,
	STATUS_EXIT
};
#endif

#include <vector>
#include "GameMenu.h"
#include "Personaje.h"
#include "Stage.h"
#include "ChatView.h"
#include "ClientUpdater.h"
#include "CharacterFactory.h"
#include "Notification.h"
#include "SDL_ttf.h"
#include "ModelUpdater.h"
#include "Login.h"
#include "StatsTable.h"
#include "GameSounds.h"

using namespace std;


class GameView {
public:

	GameView(void);
	~GameView(void);
	void initialize();
	void restart();
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
	void setStatus(unsigned status);
	unsigned getStatus();
	bool isThereAChar(string & name,int x,int y,float cameraX,float cameraY);
	SpriteAnimado* getErrorImage();
	void setActivatedAt(int activeAt);
	int getActivatedAt();
	GameMenu* getGameMenu();
	bool showingMenu();
	void manageMissionInit(string argument);
	void manageMissionUpdate(string argument);
	void setWinner(string userID);
	ModelUpdater* getModelUpdater();
	bool isGameOver();
	model::Login* getLogin();

	StatsTable* getStatsTable();
	void addFontSize(int size);
	TTF_Font* getFontSize(int size);

	GameSounds& getGameSounds();
	bool isSinglePlayerGame();

	Daniable* getDaniableInTile(std::pair <int, int> tile);
private:
	view::Camera camera;
	view::Stage worldView;
	Personaje* personaje;
	view::ChatView chat;
	StatsTable statTable;
	GameMenu* menu; 
	bool connected;
	//bool serverReached;
	map <string, Personaje*> personajes;
	map <string, Personaje*>::iterator itPersonajes;
	string playerName; //este atributo se repite dentro del Personaje del cliente.
	string playerCharacterId;
	string winner;
	CharacterFactory characterFactory;
	SpriteAnimado* errorImage;
	int activatedAt;
	unsigned gameStatus;
	ModelUpdater _modelUpdater;
	model::Login _login;
	map <int, TTF_Font*> fonts;
	map <int, TTF_Font*>::iterator fontsIt;
	bool needsConnectToServer;
	bool needsUpdateFiles;
	bool isSinglePlayer;
	//Sounds
	GameSounds gameSounds;

};

#endif //_GAMEVIEW_H_

