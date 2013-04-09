#include "YAMLParser.h"

using namespace std;
using namespace YAML;


YAMLParser::YAMLParser() {
}

YAMLParser::~YAMLParser() {
}

void operator >> (const Node& node, Screen& screen) {
	bool widthFound = false, heightFound = false;

	for(unsigned int i=0; i<node.size(); i++) {
		try {
			node[i]["ancho"] >> screen.width;
			widthFound = true;
			if (screen.width<0) {
				Logger::instance().log("Parser Error: Negative value in field 'ancho' in 'pantalla'.");
				screen.width = DEFAULT_SCREEN_WIDTH;
			}
		} catch (KeyNotFound) {	} catch (InvalidScalar) { };
		try {
			node[i]["alto"] >> screen.height;
			heightFound = true;
			if (screen.height<0) {
				Logger::instance().log("Parser Error: Negative value in field 'alto' in 'pantalla'.");
				screen.height = DEFAULT_SCREEN_HEIGHT;
			}
		} catch (KeyNotFound) {	} catch (InvalidScalar) { };
	}

	if (!widthFound) {
		Logger::instance().log("Parser Error: Field 'ancho' is not defined in 'pantalla'.");
		screen.width = DEFAULT_SCREEN_WIDTH;
	}
	if (!heightFound) {
		Logger::instance().log("Parser Error: Field 'alto' is not defined in 'pantalla'.");
		screen.height = DEFAULT_SCREEN_HEIGHT;
	}
}

void operator >> (const Node& node, Configuration& configuration) {
	bool mainCharacterSpeedFound = false, scrollMarginFound = false;

	for(unsigned int i=0; i<node.size(); i++) {
		try {
			node[i]["vel_personaje"] >> configuration.main_character_speed;
			mainCharacterSpeedFound = true;
			if (configuration.main_character_speed<0) {
				Logger::instance().log("Parser Error: Negative value in field 'vel_personaje' in 'configuracion'.");
				configuration.main_character_speed = DEFAULT_MAIN_CHARACTER_SPEED;
			}
		} catch (KeyNotFound) {	} catch (InvalidScalar) { };
		try {
			node[i]["margen_scroll"] >> configuration.scroll_margin;
			scrollMarginFound = true;
			if (configuration.scroll_margin<0) {
				Logger::instance().log("Parser Error: Negative value in field 'margen_scroll' in 'configuracion'.");
				configuration.scroll_margin = DEFAULT_SCROLL_MARGIN;
			}
		} catch (KeyNotFound) {	} catch (InvalidScalar) { };
	}

	if (!mainCharacterSpeedFound) {
		Logger::instance().log("Parser Error: Field 'vel_personaje' is not defined in 'configuracion'.");
		configuration.main_character_speed = DEFAULT_MAIN_CHARACTER_SPEED;
	}
	if (!scrollMarginFound) {
		Logger::instance().log("Parser Error: Field 'margen_scroll' is not defined in 'configuracion'.");
		configuration.scroll_margin = DEFAULT_SCROLL_MARGIN;
	}
}

bool validateImagePath(string imagePath) {
	ifstream file;
	file.open(imagePath);
	if (!file.is_open()) {
		Logger::instance().log("Parser Error: Image path '"+imagePath+"' not found.");
		return false;
	}
	return true;
}

void operator >> (const Node& node, EntityObject& entity) { // ENTIDADES CON NOMBRES IGUALES
	string name, imagePath;
	int baseWidth, baseHeight, pixelRefX, pixelRefY;
	bool baseWidthFound = false, baseHeightFound = false, pixelRefXFound = false, pixelRefYFound = false;

	try {
		node["nombre"] >> name;
		if (name=="~")
			name = "";
	} catch (KeyNotFound) {
		name = "";
	};
	try {
		node["imagen"] >> imagePath;
		if ((imagePath=="~") )//|| (!validateImagePath(imagePath)))
			imagePath = DEFAULT_TILE_IMAGE;
	} catch (KeyNotFound) {
		Logger::instance().log("Parser Error: Field 'imagen' is not defined in entity '"+name+"'.");
		imagePath = DEFAULT_TILE_IMAGE;
	};
	try {
		node["ancho_base"] >> baseWidth;
		baseWidthFound = true;
		if (baseWidth<0) {
			Logger::instance().log("Parser Error: Negative value in field 'ancho_base' in entity '"+name+"'.");
			baseWidth = DEFAULT_BASE_WIDTH;
		}
	} catch (KeyNotFound) { } catch (InvalidScalar) { };
	try {
		node["alto_base"] >> baseHeight;
		baseHeightFound = true;
		if (baseHeight<0) {
			Logger::instance().log("Parser Error: Negative value in field 'alto_base' in entity '"+name+"'.");
			baseHeight = DEFAULT_BASE_HEIGHT;
		}
	} catch (KeyNotFound) { } catch (InvalidScalar) { };
	try {
		node["pixel_ref_x"] >> pixelRefX;
		pixelRefXFound = true;
		if (pixelRefX<0) {
			Logger::instance().log("Parser Error: Negative value in field 'pixel_ref_x' in entity '"+name+"'.");
			pixelRefX = DEFAULT_PIXEL_REF_X;
		}
	} catch (KeyNotFound) { } catch (InvalidScalar) { };
	try {
		node["pixel_ref_y"] >> pixelRefY;
		pixelRefYFound = true;
		if (pixelRefY<0) {
			Logger::instance().log("Parser Error: Negative value in field 'pixel_ref_y' in entity '"+name+"'.");
			pixelRefY = DEFAULT_PIXEL_REF_Y;
		}
	} catch (KeyNotFound) { } catch (InvalidScalar) { };

	if (!baseWidthFound) {
		Logger::instance().log("Parser Error: Field 'ancho_base' is not defined in entity '"+name+"'.");
		baseWidth = DEFAULT_BASE_WIDTH;
	}
	if (!baseHeightFound) {
		Logger::instance().log("Parser Error: Field 'alto_base' is not defined in entity '"+name+"'.");
		baseHeight = DEFAULT_BASE_WIDTH;
	}
	if (!pixelRefXFound) {
		Logger::instance().log("Parser Error: Field 'pixel_ref_x' is not defined in entity '"+name+"'.");
		pixelRefX = DEFAULT_PIXEL_REF_X;
	}
	if (!pixelRefYFound) {
		Logger::instance().log("Parser Error: Field 'pixel_ref_y' is not defined in entity '"+name+"'.");
		pixelRefY = DEFAULT_PIXEL_REF_Y;
	}

	EntityObject entity_aux(name, imagePath, baseWidth, baseHeight, pixelRefX, pixelRefY);
	entity = entity_aux;
}

void operator >> (const Node& node, AnimatedEntity& animatedEntity) {
	int fps, delay;
	bool fpsFound = false, delayFound = false;
	EntityObject entity_aux;
	node >> entity_aux;

	try {
		node["fps"] >> fps;
		fpsFound = true;
		if (fps<0) {
			Logger::instance().log("Parser Error: Negative value in field 'fps' in entity '"+entity_aux.name()+"'.");
			fps = DEFAULT_FPS;
		}
	} catch (KeyNotFound) { } catch (InvalidScalar) { };
	try {
		node["delay"] >> delay;
		delayFound = true;
		if (delay<0) {
			Logger::instance().log("Parser Error: Negative value in field 'delay' in entity '"+entity_aux.name()+"'.");
			delay = DEFAULT_DELAY;
		}
	} catch (KeyNotFound) { } catch (InvalidScalar) { };

	if (!fpsFound) {
		Logger::instance().log("Parser Error: Field 'fps' is not defined in entity '"+entity_aux.name()+"'.");
		fps = DEFAULT_FPS;
	}
	if (!delayFound) {
		Logger::instance().log("Parser Error: Field 'delay' is not defined in entity '"+entity_aux.name()+"'.");
		delay = DEFAULT_DELAY;
	}

	AnimatedEntity animatedEntity_aux(entity_aux.name(), entity_aux.imagePath(), entity_aux.baseWidth(), entity_aux.baseHeight(), entity_aux.pixelRefX(), entity_aux.pixelRefY(), fps, delay);
	animatedEntity = animatedEntity_aux;
}

void operator >> (const Node& node, Entities& entities) {
	for(unsigned int i=0; i<node.size(); i++) {
		bool isAnimated = false;
		int fps, delay;

		// Veo si es animada o no.
		try {
			node[i]["fps"] >> fps;
			isAnimated = true;
		} catch (KeyNotFound) {	} catch (InvalidScalar) { };
		try {
			node[i]["delay"] >> delay;
			isAnimated = true;
		} catch (KeyNotFound) {	} catch (InvalidScalar) { };

		if (isAnimated) {
			AnimatedEntity entity;
			node[i] >> entity;
			if (entity.name().size()>0) // Si tiene nombre se guarda.
				entities.vAnimatedEntities.push_back(entity);
		}
		else {
			EntityObject entity;
			node[i] >> entity;
			if (entity.name().size()>0) // Si tiene nombre se guarda.
				entities.vEntitiesObject.push_back(entity);
		}
	}
}

void operator >> (const Node& node, EntityDef& entityDef) {
	bool xFound = false, yFound = false;

	try {
		node["entidad"] >> entityDef.entity;
		if (entityDef.entity=="~")
			entityDef.entity = "";
	} catch (KeyNotFound) {
		entityDef.entity = "";
	};
	try {
		node["x"] >> entityDef.x;
		xFound = true;
		if (entityDef.x<0)
			Logger::instance().log("Parser Error: Negative value in field 'x' in one of the entities '"+entityDef.entity+"'.");
	} catch (KeyNotFound) { } catch (InvalidScalar) { };
	try {
		node["y"] >> entityDef.y;
		yFound = true;
		if (entityDef.y<0)
			Logger::instance().log("Parser Error: Negative value in field 'y' in one of the entities '"+entityDef.entity+"'.");
	} catch (KeyNotFound) { } catch (InvalidScalar) { };

	if (!xFound) {
		Logger::instance().log("Parser Error: Field 'x' is not defined in one of the entities '"+entityDef.entity+"'.");
	}
	if (!yFound) {
		Logger::instance().log("Parser Error: Field 'y' is not defined in one of the entities '"+entityDef.entity+"'.");
	}
}

void operator >> (const Node& node, sMainCharacter& mainCharacter) {
	bool xFound = false, yFound = false;

	try {
		node["tipoEntidad"] >> mainCharacter.entityType;
		if (mainCharacter.entityType=="~")
			mainCharacter.entityType = "";
	} catch (KeyNotFound) {
		mainCharacter.entityType = "";
	};
	try {
		node["x"] >> mainCharacter.x;
		xFound = true;
		if (mainCharacter.x<0) {
			Logger::instance().log("Parser Error: Negative value in field 'x' in main character '"+mainCharacter.entityType+"'.");
			mainCharacter.x = DEFAULT_MAIN_CHARACTER_X;
		}
	} catch (KeyNotFound) { } catch (InvalidScalar) { };
	try {
		node["y"] >> mainCharacter.y;
		yFound = true;
		if (mainCharacter.y<0) {
			Logger::instance().log("Parser Error: Negative value in field 'y' in main character '"+mainCharacter.entityType+"'.");
			mainCharacter.y = DEFAULT_MAIN_CHARACTER_Y;
		}
	} catch (KeyNotFound) { } catch (InvalidScalar) { };

	if (!xFound) {
		Logger::instance().log("Parser Error: Field 'x' is not defined in main character '"+mainCharacter.entityType+"'.");
		mainCharacter.x = DEFAULT_MAIN_CHARACTER_X;
	}
	if (!yFound) {
		Logger::instance().log("Parser Error: Field 'y' is not defined in main character '"+mainCharacter.entityType+"'.");
		mainCharacter.y = DEFAULT_MAIN_CHARACTER_Y;
	}
}

void operator >> (const Node& node, sStage& stage) {
	bool sizeXFound = false, sizeYFound = false;

	try {
		node["nombre"] >> stage.name;
		if (stage.name=="~")
			stage.name = "";
	} catch (KeyNotFound) {
		stage.name = "";
	};
	try {
		node["size_x"] >> stage.size_x;
		sizeXFound = true;
		if (stage.size_x<0) {
			Logger::instance().log("Parser Error: Negative value in field 'size_x' in stage '"+stage.name+"'.");
			stage.size_x = DEFAULT_STAGE_SIZE_X;
		}
	} catch (KeyNotFound) { } catch (InvalidScalar) { };
	if (!sizeXFound) {
		Logger::instance().log("Parser Error: Field 'size_x' is not defined in stage '"+stage.name+"'.");
		stage.size_x = DEFAULT_STAGE_SIZE_X;
	}
	try {
		node["size_y"] >> stage.size_y;
		sizeYFound = true;
		if (stage.size_y<0) {
			Logger::instance().log("Parser Error: Negative value in field 'size_y' in stage '"+stage.name+"'.");
			stage.size_y = DEFAULT_STAGE_SIZE_Y;
		}
	} catch (KeyNotFound) { } catch (InvalidScalar) { };
	if (!sizeYFound) {
		Logger::instance().log("Parser Error: Field 'size_y' is not defined in stage '"+stage.name+"'.");
		stage.size_y = DEFAULT_STAGE_SIZE_Y;
	}

	try {
		const Node& node_aux = node["entidadesDef"];
		for(unsigned int i=0; i<node_aux.size(); i++) {
			EntityDef entityDef;
			node_aux[i] >> entityDef;
			if ((entityDef.entity.size()>0) && ((entityDef.x>=stage.size_x) || (entityDef.y>=stage.size_y)))
				Logger::instance().log("Parser Error: Entity '"+entityDef.entity+"''s position is out of map range.");
			else
				if ((entityDef.entity.size()>0) && (entityDef.x>=0) && (entityDef.y>=0)) // Si tiene nombre de entidad y posición válida se guarda.
					stage.vEntitiesDef.push_back(entityDef);
		}
	} catch (KeyNotFound) { };
	try {
		const Node& node_aux = node["protagonista"];
		for(unsigned int i=0; i<node_aux.size(); i++) {
			sMainCharacter mainCharacter;
			node_aux[i] >> mainCharacter;
			if (mainCharacter.entityType.size()>0) {
				if ((mainCharacter.x>=stage.size_x) || (mainCharacter.y>=stage.size_y)) {
					Logger::instance().log("Parser Error: Main character '"+mainCharacter.entityType+"''s position is out of map range.");
					mainCharacter.x = DEFAULT_MAIN_CHARACTER_X;
					mainCharacter.y = DEFAULT_MAIN_CHARACTER_Y;
				}
				stage.vMainCharacters_aux.push_back(mainCharacter);
			}
		}
	} catch (KeyNotFound) {	};
}

void operator >> (const Node& node, Stages& stages) {
	for(unsigned int i=0; i<node.size(); i++) {
		sStage stage;
		node[i] >> stage;
		if (stage.name.size()>0) // Si tiene nombre se guarda.
			stages.vStages_aux.push_back(stage);
		else {
			string str_i = static_cast<std::ostringstream*>(&(ostringstream() << i+1))->str();
			Logger::instance().log("Parser Error: Field 'nombre' is not defined in stage number "+str_i+".");
		}
	}
}

Configuration YAMLParser::generateDefaultConfiguration() {
	Configuration configuration;
	configuration.main_character_speed = DEFAULT_MAIN_CHARACTER_SPEED;
	configuration.scroll_margin = DEFAULT_SCROLL_MARGIN;
	return configuration;
}

Screen YAMLParser::generateDefaultScreen() {
	Screen screen;
	screen.width = DEFAULT_SCREEN_WIDTH;
	screen.height = DEFAULT_SCREEN_HEIGHT;
	return screen;
}

MainCharacter YAMLParser::generateDefaultMainCharacter() {
	if (entities.vAnimatedEntities.size()<=0) {
		AnimatedEntity animatedEntity_default;
		entities.vAnimatedEntities.push_back(animatedEntity_default);
	}
	MainCharacter mainCharacter(&entities.vAnimatedEntities[0], DEFAULT_MAIN_CHARACTER_X, DEFAULT_MAIN_CHARACTER_Y); // Uso la primera entidad porque ahí va estar el default en caso de no haber ninguna entidad.
	return mainCharacter;
}

sStage YAMLParser::generateDefaultStage() {
	sStage stage;
	stage.name = "DEFAULT";
	stage.size_x = DEFAULT_STAGE_SIZE_X;
	stage.size_y = DEFAULT_STAGE_SIZE_Y;
	loadEntitiesToMap(0);
	stage.vMainCharacters.push_back(generateDefaultMainCharacter());
	return stage;
}

AnimatedEntity* YAMLParser::findAnimatedEntityType(string name) {
	unsigned int i = 0;
	bool found = false;
	while ((i<entities.vAnimatedEntities.size()) && (!found)) {
		if (entities.vAnimatedEntities[i].name()==name)
			found = true;
		else
			i++;
	}
	if (found)
		return &entities.vAnimatedEntities[i];
	return NULL;
}

EntityObject* YAMLParser::findEntityObjectType(string name) {
	unsigned int i = 0;
	bool found = false;
	while ((i<entities.vEntitiesObject.size()) && (!found)) {
		if (entities.vEntitiesObject[i].name()==name)
			found = true;
		else
			i++;
	}
	if (found)
		return &entities.vEntitiesObject[i];
	return NULL;
}

void YAMLParser::loadEntitiesToMap(int stage_index) {
	sStage stage_aux = stages.vStages_aux[stage_index];
	map <KeyPair, EntityObject*> entityMap;
	for(unsigned int i=0; i<stage_aux.vEntitiesDef.size(); i++) {
		KeyPair key(stage_aux.vEntitiesDef[i].x, stage_aux.vEntitiesDef[i].y);
		EntityObject *entityObjectType = findEntityObjectType(stage_aux.vEntitiesDef[i].entity);
		if (!entityObjectType)
			Logger::instance().log("Parser Error: Entity type '"+stage_aux.vEntitiesDef[i].entity+"' defined in stage '"+stage_aux.name+"' not found.");
		else {
			pair<map<KeyPair,EntityObject*>::iterator,bool> ret;
			ret = entityMap.insert(make_pair(key, entityObjectType));
			if (!ret.second) {
				string str_x = static_cast<std::ostringstream*>(&(ostringstream() << stage_aux.vEntitiesDef[i].x))->str();
				string str_y = static_cast<std::ostringstream*>(&(ostringstream() << stage_aux.vEntitiesDef[i].y))->str();
				Logger::instance().log("Parser Error: Position '("+str_x+","+str_y+")' already defined for stage '"+stage_aux.name+"'.");
			}
		}
	}
	for(unsigned int i=0; i<stage_aux.size_x; i++) // Completo el mapa con entidad objeto default guardada en la primera posición.
		for(unsigned int j=0; j<stage_aux.size_y; j++) {
			KeyPair key(i, j);
			entityMap.insert(make_pair(key, &entities.vEntitiesObject[0]));
		}
	Stage stage(stage_aux.name, stage_aux.size_x, stage_aux.size_y, stage_aux.vEntitiesDef, entityMap, stage_aux.vMainCharacters);
	stages.vStages.push_back(stage);
}

void YAMLParser::loadMainCharacters(int stage_index) {
	sStage stage_aux = stages.vStages_aux[stage_index];
	for(unsigned int j=0; j<stage_aux.vMainCharacters_aux.size(); j++) {
		sMainCharacter mainCharacter_aux = stage_aux.vMainCharacters_aux[j];
		AnimatedEntity *animatedEntityType = findAnimatedEntityType(mainCharacter_aux.entityType);
		if (!animatedEntityType)
			Logger::instance().log("Parser Error: Entity type '"+mainCharacter_aux.entityType+"' for main character in stage '"+stage_aux.name+"' not found.");
		else {
			MainCharacter mainCharacter(animatedEntityType, mainCharacter_aux.x, mainCharacter_aux.y);
			stage_aux.vMainCharacters.push_back(mainCharacter);
		}
	}
	if (stage_aux.vMainCharacters.size()<=0) { // Verifico que para cada escenario exista al menos un protagonista.
		Logger::instance().log("Parser Error: Field 'protagonista' is not defined in stage '"+stage_aux.name+"'.");
		stage_aux.vMainCharacters.push_back(generateDefaultMainCharacter());
	}
	stages.vStages_aux[stage_index] = stage_aux;
}

void YAMLParser::manageEntityCase() {
	if (entities.vAnimatedEntities.size()<=0) { // Verifico que exista al menos una entidad animada.	
		Logger::instance().log("Parser Error: No animated entities found.");
		AnimatedEntity animatedEntity;
		entities.vAnimatedEntities.push_back(animatedEntity);
	}
}

void YAMLParser::manageStageCase() {
	for(unsigned int i=0; i<stages.vStages_aux.size(); i++) {
		loadMainCharacters(i);
		loadEntitiesToMap(i);
	}
	if (stages.vStages_aux.size()<=0) { // Verifico que exista al menos un escenario.
		Logger::instance().log("Parser Error: No stages found.");
		stages.vStages_aux.push_back(generateDefaultStage());
	}
}

void YAMLParser::parse(string inputFilePath) {
	Node doc;
	bool screenFound = false, stagesFound = false, entitiesFound = false, configurationFound = false;
	ifstream inputFile(inputFilePath);
	// Verificar si existe el archivo y si está vacío
	Parser parser(inputFile);

	// MEJORAR INICIALIZAR. VER EL RESTO (EJ ANIMADAS)
	EntityObject entity_default;
	entities.vEntitiesObject.push_back(entity_default); // Cargo en la primera posición una entidad default.

	try {
		parser.GetNextDocument(doc);
		try {
			doc["pantalla"] >> screen;
			screenFound = true;
		} catch (KeyNotFound) { };
		try {
			doc["configuracion"] >> configuration;
			configurationFound = true;
		} catch (KeyNotFound) { };
		try {
			doc["entidades"] >> entities;
			manageEntityCase();
			entitiesFound = true;
		} catch (KeyNotFound) { };
		try {
			doc["escenarios"] >> stages;
			manageStageCase();
			stagesFound = true;
		} catch (KeyNotFound) { };
		
		if (!screenFound) {
			Logger::instance().log("Parser Error: Field 'pantalla' is not defined.");
			screen = generateDefaultScreen();
		}
		if (!stagesFound) {
			Logger::instance().log("Parser Error: Field 'escenarios' is not defined.");
			sStage stage_aux = generateDefaultStage();
		}
		if (!entitiesFound) {
			Logger::instance().log("Parser Error: Field 'entidades' is not defined.");
			manageEntityCase();
		}
		if (!configurationFound) {
			Logger::instance().log("Parser Error: Field 'configuracion' is not defined.");
			configuration = generateDefaultConfiguration();
		}
	} catch (Exception& parserException) { // SI ES UN ERROR DE SINTAXIS TERMINAR EL PROGRAMA O CARGAR TODO DEFAULT Y LOGGEAR EL ERROR?
		Logger::instance().log(parserException.what());
		cout << parserException.what() << endl;
	};

	/*
	// TESTEO RAPIDO
	cout << "Pantalla:\n   Ancho: " << screen.width << " Alto: " << screen.height << endl;
	cout << "Configuracion:\n   Vel_Personaje: " << configuration.main_character_speed << " Margen_Scroll: " << configuration.scroll_margin << endl;
	cout << "Entidades:" << endl;
	for(unsigned int i=0; i<entities.vEntitiesObject.size(); i++) {
		cout << "   Nombre: " << entities.vEntitiesObject[i].name() << " Imagen: " << entities.vEntitiesObject[i].imagePath() << endl;
	}
	for(unsigned int i=0; i<entities.vAnimatedEntities.size(); i++) {
		cout << "   Nombre: " << entities.vAnimatedEntities[i].name() << " Imagen: " << entities.vAnimatedEntities[i].imagePath() <<
			" Fps: " << entities.vAnimatedEntities[i].fps() << endl;
	}
	cout << "Escenarios:" << endl;
	for(unsigned int i=0; i<stages.vStages.size(); i++) {
		Stage stage = stages.vStages[i];
		cout << "   Nombre: " << stage.name() << " Size_X: " << stage.width() << " Size_Y: " << stage.height() << endl;
		cout << "   Entidades:" << endl;
		for(unsigned int j=0; j<stage.vEntitiesDef().size(); j++) {
			EntityDef entityDef = stage.vEntitiesDef()[j];
			cout << "      Entidad: " << entityDef.entity << " X: " << entityDef.x << " Y: " << entityDef.y << endl;
		}
		/*cout << "   Mapa: " << endl;
		for(unsigned int j=0; j<stage.height(); j++) {
			for(unsigned int k=0; k<stage.width(); k++) {
				KeyPair key(k,j);
				cout << " " << (*stage.entityMap()[key]).name();
			}
			cout << endl;
		}
		cout << "   Protagonistas:" << endl;
		for(unsigned int j=0; j<stage.vMainCharacters().size(); j++) {
			MainCharacter mainCharacter = stage.vMainCharacters()[j];
			cout << "      TipoEntidad: " << (*mainCharacter.entityType()).name() << " X: " << mainCharacter.x() << " Y: " << mainCharacter.y() << endl;
		}
	}*/
}

vector <Stage> YAMLParser::vStages() {
	return stages.vStages;
}

vector <EntityObject> YAMLParser::vEntitiesObject() {
	return entities.vEntitiesObject;
}

vector <AnimatedEntity> YAMLParser::vAnimatedEntities() {
	return entities.vAnimatedEntities;
}