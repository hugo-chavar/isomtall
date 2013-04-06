#ifndef __YAMLPARSER_H__
#define __YAMLPARSER_H__

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "yaml-cpp/yaml.h"
#include "Logger.h"
#include "..\Model\MainCharacter.h"

using namespace std;
using namespace model;
using namespace YAML;


namespace common {

	// Data types

	struct Screen {
		unsigned int width;
		unsigned int height;
	};

	struct Configuracion {
		float vel_personaje;
		float margen_scroll;
	};

	struct Entities {
		vector <EntityObject> vEntitiesObject;
		vector <AnimatedEntity> vAnimatedEntities;
	};

	struct EntidadDef {
		string entidad;
		unsigned int x;
		unsigned int y;
	};

	struct sMainCharacter {
		string entityType;
		int x;
		int y;
	};

	struct Escenario {
		string nombre;
		unsigned int size_x;
		unsigned int size_y;
		vector <EntidadDef> vEntidadesDef;
		//map <Par, void*> entityMap;
		vector <sMainCharacter> vMainCharacters_aux;
		vector <MainCharacter> vMainCharacters;
	};

	struct Escenarios {
		vector <Escenario> vEscenarios;
	};


	// Class

	class YAMLParser {

	private:
		Screen screen;
		Configuracion configuracion;
		Entities entities;
		Escenarios escenarios;

		Screen generateDefaultScreen();
		MainCharacter generateDefaultMainCharacter();
		Escenario generateDefaultStage();
		void manageEntityCase();
		void manageStageCase();

	public:
		YAMLParser();
		~YAMLParser();
		void parse(string inputFilePath);
		AnimatedEntity *findAnimatedEntityType(string name);
	};
}


#endif