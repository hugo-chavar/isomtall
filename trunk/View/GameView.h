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
	STATUS_SIMULATION_CONNECTION_LOST,
	STATUS_SIMULATION_SINGLE_PLAYER,
	STATUS_START_SCREEN,
	STATUS_EXIT
	
};
#endif

#include "GameMenu.h"
#include "Personaje.h"
#include "Stage.h"
#include "ChatView.h"
#include "ClientUpdater.h"
#include "CharacterFactory.h"
#include "Notification.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include "ModelUpdater.h"
#include "Login.h"



class GameView {
public:

	GameView(void);
	~GameView(void);
	void initialize();
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
	void startBackgroundMusic();
	void toggleBackgroundMusic();
	GameMenu* getGameMenu();
	bool showingMenu();
	void manageMissionInit(string argument);
	void manageMissionUpdate(string argument);
	ModelUpdater* getModelUpdater();

	model::Login* getLogin();

	void addFontSize(int size);
	TTF_Font* getFontSize(int size);
private:
	view::Camera camera;
	view::Stage worldView;
	Personaje* personaje;
	view::ChatView chat;
	//view::Notification notification;
	GameMenu* menu; 
	bool connected;
	bool serverReached;
	map <string, Personaje*> personajes;
	map <string, Personaje*>::iterator itPersonajes;
	string playerName; //este atributo se repite dentro del Personaje del cliente.
	string playerCharacterId;
	CharacterFactory characterFactory;
	SpriteAnimado* errorImage;
	int activatedAt;
	unsigned gameStatus;

	Mix_Music* _music;
	Mix_Music* getMusic();
	void setMusic(Mix_Music* music);

	ModelUpdater _modelUpdater;

	model::Login _login;
	map <int, TTF_Font*> fonts;
	map <int, TTF_Font*>::iterator fontsIt;
};

#endif //_GAMEVIEW_H_

