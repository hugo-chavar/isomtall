#ifndef _GAME_H_
#define _GAME_H_

#include <fstream>
#include <string>
#include "DataTypes.h"
#include "PersonajeModelo.h"
#include "Configuration.h"
#include "StageModel.h"
#include "..\View\TimeManager.h"
#include "..\Model\YAMLParser.h"

class Game
{
public:
	~Game();

	static Game& instance();
	StageModel* world();
	TimeManager* time();
	bool initialize(string nombreJugador);
	bool insidePlayerVision(std::pair<int,int> );
	bool isKnownByPlayer(std::pair<int,int> );
	EntLists allEntities;
	YAMLParser yParser;
	AnimatedEntity* animatedEntityAt(unsigned pos);
	EntityObject* entityObjectAt(unsigned pos);
	PersonajeModelo * personaje();
	Configuration* configuration();

private:
	Game();
	StageModel _world;
	Configuration* _configuration;
	TimeManager _time;
	PersonajeModelo * _personaje;
};

#endif