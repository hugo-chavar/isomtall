#ifndef _GAME_H_
#define _GAME_H_

#include <fstream>
#include <string>
#include "DataTypes.h"
#include "PersonajeModelo.h"
#include "Configuration.h"
#include "Stage.h"
#include "..\View\TimeManager.h"
#include "..\Model\YAMLParser.h"

namespace model
{
	class Game
	{
	public:
		~Game();

		static Game& instance();
		Stage* world();
		TimeManager* time();
		bool initialize();
		EntLists allEntities;
		YAMLParser yParser;
		AnimatedEntity* animatedEntityAt(unsigned pos);
		EntityObject* entityObjectAt(unsigned pos);
		PersonajeModelo * personaje();
		Configuration* configuration();
		
	private:
		Game();
		Stage _world;
		Configuration* _configuration;
		TimeManager _time;
		PersonajeModelo * _personaje;
	};
};

#endif