#ifndef _GAME_H_
#define _GAME_H_

#include <fstream>
#include <string>
#include "PersonajeModelo.h"
#include "Stage.h"
#include "..\View\TimeManager.h"
#include "..\Model\YAMLParser.h"

//using namespace std;

namespace model
{
	class Game
	{
	public:
		~Game();

		static Game& instance();
		Stage& world();
		TimeManager& time();
		void initialize();
		vector <EntityObject> vEntitiesObject();
		vector <AnimatedEntity> vAnimatedEntities();
		PersonajeModelo * personaje();
		//void setFile(string path);
		
	private:
		Game();
		Stage _world;
		TimeManager _time;
		PersonajeModelo * _personaje; // CAMBIAR POR PERSONAJE MODELO
		vector <EntityObject> _vEntitiesObject;
		vector <AnimatedEntity> _vAnimatedEntities;
		//ofstream fd;
	};
};

#endif