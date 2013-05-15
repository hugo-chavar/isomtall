#ifndef _GAME_H_
#define _GAME_H_
#pragma warning(disable: 4512)

#include <fstream>
#include <string>
#include "DataTypes.h"
#include "PersonajeModelo.h"
#include "Configuration.h"
#include "StageModel.h"
#include "..\View\TimeManager.h"
#include "..\Model\YAMLParser.h"
#include "Login.h"
#include "Connector.h"
#include "InstructionQueue.h"
#include "ModelUpdater.h"

class Game
{
public:
	~Game();

	static Game& instance();
	StageModel* world();
	TimeManager* time();
	model::Login* getLogin();
	ModelUpdater* getModelUpdater();
	bool initialize(); 
	bool insidePlayerVision(std::pair<int,int> );
	bool isKnownByPlayer(std::pair<int,int> );
	EntLists allEntities;
	YAMLParser yParser;
	AnimatedEntity* animatedEntityAt(unsigned pos);
	EntityObject* entityObjectAt(unsigned pos);
	PersonajeModelo * personaje();
	Configuration* configuration();
	PersonajeModelo* getPersonaje(string name);
	void setPlayerName(string name);
	string getPlayerName();
	void setPlayerCharacterId(string char_id);
	string getPlayerCharacterId();

private:
	Game();
	StageModel _world;
	Configuration _configuration;
	TimeManager _time;
	PersonajeModelo * _personaje;
	model::Login _login;
	ModelUpdater _modelUpdater;
	map <string,PersonajeModelo*> personajes;
	string playerName;
	string playerCharacterId;
};

#endif