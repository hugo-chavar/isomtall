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
	STATUS_INITIALIZING,
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
#include "Mission.h"
#include "Mutex.h"


#ifndef event_t
#define event_t
enum event_t {
	EVENT_VIBRATING,
	EVENT_SOUND_ARROW,
	EVENT_SOUND_ATTACK_ON_SHIELD,
	EVENT_SOUND_ATTACK_ON_WOOD,
	EVENT_SOUND_EAT_ITEM,
	EVENT_SOUND_REGENERATION,
	EVENT_SOUND_EXPLOSION,
	EVENT_SOUND_MAGIC,
	EVENT_ICESPELL_ITEMIMPACT,
	EVENT_STOP_ITEMICEUP,
	EVENT_AMMUNITION_CHANGE,
	EVENT_AMMUNITION_DEATH
};
#endif

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
	Mission* getMission();
	GameSounds& getGameSounds();
	bool isSinglePlayerGame();
	Daniable* getDaniableInTile(std::pair <int, int> tile);
	void updateEvents(string serializedEventsUpdates);
	void updateEvent(string serializedItemUpdate);
	std::vector<CharacterVision *>* getCharactersVisions();
	void deleteCharacterVision(CharacterVision*);
	void setCharacterVision(CharacterVision *);

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
	Mission mission;
	//Sounds
	GameSounds gameSounds;
	std::vector<CharacterVision *> charactersVisions;
	void updateOthersVision();

};

#endif //_GAMEVIEW_H_

