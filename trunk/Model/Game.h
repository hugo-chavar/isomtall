#ifndef _GAME_H_
#define _GAME_H_
#pragma warning(disable: 4512)

#include <fstream>
#include <string>
#include "DataTypes.h"
#include "PersonajeModelo.h"
#include "Configuration.h"
#include "StageModel.h"
#include "../View/TimeManager.h"
#include "YAMLParser.h"
//#include "Login.h"
//#include "Connector.h"
#include "InstructionQueue.h"


class Game {
public:
	~Game();

	static Game& instance();
	StageModel* world();
	TimeManager* getTimer();
	bool initialize(); 
	void restart();
	//bool insidePlayerVision(std::pair<int,int> );
	//bool isKnownByPlayer(std::pair<int,int> );
	EntLists allEntities;
	YAMLParser yParser;
	AnimatedEntity* animatedEntityAt(unsigned pos);
	EntityObject* entityObjectAt(unsigned pos);
	//PersonajeModelo * personaje();
	Configuration* configuration();
	//PersonajeModelo* getPersonaje(string name);
	//void setPlayerName(string name);
	//string getPlayerName();
	//void setPlayerCharacterId(string char_id);
	//string getPlayerCharacterId();
	int getStageNumber();
	void setStageNumber(int stageNo);
	void setStageNumberStatus(bool status);
	bool isStageNumberSet();
	void startWorld();
	float getRandom();

private:
	Game();
	StageModel _world;
	Configuration _configuration;
	TimeManager _time;
	//PersonajeModelo * _personaje;
	//map <string,PersonajeModelo*> personajesEnJuego;
	//string playerName;
	//string playerCharacterId;
	bool stageNumberSet;
	int stageNumber;
};

#endif