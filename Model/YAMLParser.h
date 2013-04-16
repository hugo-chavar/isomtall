#pragma warning(disable: 4146)
#ifndef __YAMLPARSER_H__
#define __YAMLPARSER_H__

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include "..\Libraries\Parser YAML\include\yaml-cpp\yaml.h"
#include "Logger.h"
#include "DataTypes.h"
#include "Stage.h"
#include "DirList.h"
#include "PersonajeModelo.h"
#include "CameraModel.h"

using namespace std;
using namespace YAML;
using namespace common;
using namespace model;


// Data types

struct Screen {
	int width;
	int height;
};

struct Configuration {
	float main_character_speed;
	int scroll_margin;
};

struct Entities {
	vector <EntityObject*> vEntitiesObject;
	vector <AnimatedEntity*> vAnimatedEntities;
};

struct sMainCharacter {
	string entityType;
	int x;
	int y;
};

struct sStage {
	string name;
	int size_x;
	int size_y;
	vector <EntityDef> vEntitiesDef;
	vector <sMainCharacter> vMainCharacters_aux;
	vector <PersonajeModelo*> vMainCharacters;
};

struct Stages {
	vector <sStage> vStages_aux;
	vector <Stage> vStages;
};


// Class

class YAMLParser {

private:
	Screen screen;
	CameraModel* camera;
	Configuration configuration;
	EntLists entities;
	Stages stages;

	Screen generateDefaultScreen();
	Configuration generateDefaultConfiguration();
	PersonajeModelo* generateDefaultMainCharacter();
	Stage generateDefaultStage();
	void loadEverythingByDefault();
	void loadEntitiesToMap(int stage_index);
	void loadMainCharacters(int stage_index);
	void manageEntityCase();
	void manageStageCase();


public:
	YAMLParser();
	~YAMLParser();

	void parse(string inputFilePath);
	vector <Stage> vStages();
	EntLists allLists();

	AnimatedEntity* findAnimatedEntityType(string name);
	EntityObject* findEntityObjectType(string name);

	//conexion con el modelo logico
	PersonajeModelo* modelMainCharacters(unsigned, unsigned);
	CameraModel* cameraModel();

};


#endif