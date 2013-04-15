#ifndef _GAME_H_
#define _GAME_H_

#include <fstream>
#include <string>
#include "DataTypes.h"
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
		EntLists allEntities;
		//vector <EntityObject*>* vEntitiesObject();
		AnimatedEntity* animatedEntityAt(unsigned pos);
		EntityObject* entityObjectAt(unsigned pos);
		PersonajeModelo * personaje();
		CameraModel* cameraModel();
		
	private:
		Game();
		Stage _world;
		CameraModel* _cameraModel;
		TimeManager _time;
		PersonajeModelo * _personaje;
		//vector <EntityObject*>* _vEntitiesObject;
		//vector <AnimatedEntity*>* _vAnimatedEntities;
		//ofstream fd;
	};
};

#endif