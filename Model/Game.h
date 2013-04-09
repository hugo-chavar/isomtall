#ifndef _GAME_H_
#define _GAME_H_

#include <fstream>
#include <string>
#include "Stage.h"
#include "..\Model\YAMLParser.h"

//using namespace std;

namespace model
{
	class Game
	{
	public:
		~Game();

		static Game& instance();
		Stage world();
		void initialize();
		vector <EntityObject> vEntitiesObject();
		//void setFile(string path);
		
	private:
		Game();
		Stage _world;
		MainCharacter _personaje; // CAMBIAR POR PERSONAJE MODELO
		vector <EntityObject> _vEntitiesObject;
		vector <AnimatedEntity> _vAnimatedEntities;
		//ofstream fd;
	};
};

#endif