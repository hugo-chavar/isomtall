//#pragma warning(disable: 4101) //Unreferenced formal parameter
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
		} catch (KeyNotFound) {	} catch (InvalidScalar) { }
		catch (Exception& parserException ) {
			Logger::instance().logUnexpected(parserException.what());
		};
		try {
			node[i]["alto"] >> screen.height;
			heightFound = true;
			if (screen.height<0) {
				Logger::instance().log("Parser Error: Negative value in field 'alto' in 'pantalla'.");
				screen.height = DEFAULT_SCREEN_HEIGHT;
			}
		} catch (KeyNotFound) {	} catch (InvalidScalar) { }
		catch (Exception& ) { }; //parserException
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
		} catch (KeyNotFound) {	} catch (InvalidScalar) { }
		catch (Exception& parserException ) {
			Logger::instance().logUnexpected(parserException.what());
		};
		try {
			node[i]["margen_scroll"] >> configuration.scroll_margin;
			scrollMarginFound = true;
			if (configuration.scroll_margin<0) {
				Logger::instance().log("Parser Error: Negative value in field 'margen_scroll' in 'configuracion'.");
				configuration.scroll_margin = DEFAULT_SCROLL_MARGIN;
			}
		} catch (KeyNotFound) {	} catch (InvalidScalar) { }
		catch (Exception& parserException ) {
			Logger::instance().logUnexpected(parserException.what());
		};
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
	if ((imagePath[imagePath.size()-1]!='/') && (imagePath[imagePath.size()-1]!='\\')) { // Si no es un directorio.
		if (imagePath.find(IMAGES_EXTENSION)==string::npos) { // Veo que sea '.png'.
			Logger::instance().log("Parser Error: '"+imagePath+"' does not have a valid extension.");
			return false;
		}

		ifstream file;
		file.open(imagePath);
		if (!file.is_open()) { // Veo que exista.
			Logger::instance().log("Parser Error: Image path '"+imagePath+"' not found.");
			return false;
		}
		else {
			file.close();
			return true;
		}
	}
	return false;
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
	}
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
	try {
		node["imagen"] >> imagePath;
		if ((imagePath=="~") || (!validateImagePath(imagePath)))
			imagePath = ERROR_IMAGE;
	} catch (KeyNotFound) {
		Logger::instance().log("Parser Error: Field 'imagen' is not defined in entity '"+name+"'.");
		imagePath = ERROR_IMAGE;
	}
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
	try {
		node["ancho_base"] >> baseWidth;
		baseWidthFound = true;
		if (baseWidth<0) {
			Logger::instance().log("Parser Error: Negative value in field 'ancho_base' in entity '"+name+"'.");
			baseWidth = DEFAULT_BASE_WIDTH;
		}
	} catch (KeyNotFound) { } catch (InvalidScalar) { }
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
	try {
		node["alto_base"] >> baseHeight;
		baseHeightFound = true;
		if (baseHeight<0) {
			Logger::instance().log("Parser Error: Negative value in field 'alto_base' in entity '"+name+"'.");
			baseHeight = DEFAULT_BASE_HEIGHT;
		}
	} catch (KeyNotFound) { } catch (InvalidScalar) { }
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
	try {
		node["pixel_ref_x"] >> pixelRefX;
		pixelRefXFound = true;
		if (pixelRefX<0) {
			Logger::instance().log("Parser Error: Negative value in field 'pixel_ref_x' in entity '"+name+"'.");
			pixelRefX = DEFAULT_PIXEL_REF_X;
		}
	} catch (KeyNotFound) { } catch (InvalidScalar) { }
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
	try {
		node["pixel_ref_y"] >> pixelRefY;
		pixelRefYFound = true;
		if (pixelRefY<0) {
			Logger::instance().log("Parser Error: Negative value in field 'pixel_ref_y' in entity '"+name+"'.");
			pixelRefY = DEFAULT_PIXEL_REF_Y;
		}
	} catch (KeyNotFound) { } catch (InvalidScalar) { }
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};

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

//list <string> loadImagesPaths(string imageDir) {
//	DirList dirList;
//	list <string> imagesPaths;
//	if (dirList.createFromDirectory(imageDir)) {
//		while (dirList.hasNext()) {
//			string dir_aux = dirList.nextFullPath();
//			if (dir_aux.find(IMAGES_EXTENSION)!=string::npos) // Las imágenes de las entidades animadas deben tener la extensión '.png'.
//				imagesPaths.push_back(dir_aux);
//		}
//		if (imagesPaths.empty())
//			Logger::instance().log("Parser Error: No '.png' images found in the directory '"+imageDir+"'.");
//	}
//	else
//		Logger::instance().log("Parser Error: Image directory '"+imageDir+"' not found.");
//	return imagesPaths;
//}

DirList* loadImagesPaths(string imageDir) {
	DirList* dirList = new DirList();
	//list <string> imagesPaths;
	if (dirList->createFromDirectory(imageDir)) {
		while (dirList->hasNext()) {
			string dir_aux = dirList->nextFullPath();
			if (dir_aux.find(IMAGES_EXTENSION)==string::npos) // Las imágenes de las entidades animadas deben tener la extensión '.png'.
				dirList->deletePrevious();
		}
		if (dirList->empty())
			Logger::instance().log("Parser Error: No '.png' images found in the directory '"+imageDir+"'.");
	}
	else
		Logger::instance().log("Parser Error: Image directory '"+imageDir+"' not found.");
	return dirList;
}

void operator >> (const Node& node, AnimatedEntity& animatedEntity) {
	int fps, delay;
	string imageDir;
	DirList* imagesPaths;
	bool fpsFound = false, delayFound = false;
	EntityObject entity_aux;
	node >> entity_aux;

	try {
		node["imagen"] >> imageDir;
		imagesPaths = loadImagesPaths(imageDir);
		if ((imageDir=="~") || (imagesPaths->empty())) {
			imageDir = DEFAULT_ANIMATED_DIR; //Todo: consultar con yami (aca no se carga la lista? imagesPaths queda vacia?)
			//hice esto para arreglarlo
			imagesPaths = loadImagesPaths(DEFAULT_ANIMATED_DIR);
			if (imagesPaths->empty()){
				Logger::instance().log("Parser Error: DEFAULT_ANIMATED_DIR does not contain any file.");
			}
		}
	} catch (KeyNotFound) {
		imagesPaths = loadImagesPaths(DEFAULT_ANIMATED_DIR);
	}
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
	try {
		node["fps"] >> fps;
		fpsFound = true;
		if (fps<0) {
			Logger::instance().log("Parser Error: Negative value in field 'fps' in entity '"+entity_aux.name()+"'.");
			fps = DEFAULT_FPS;
		}
	} catch (KeyNotFound) { } catch (InvalidScalar) { }
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
	try {
		node["delay"] >> delay;
		delayFound = true;
		if (delay<0) {
			Logger::instance().log("Parser Error: Negative value in field 'delay' in entity '"+entity_aux.name()+"'.");
			delay = DEFAULT_DELAY;
		}
	} catch (KeyNotFound) { } catch (InvalidScalar) { }
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};

	if (!fpsFound) {
		Logger::instance().log("Parser Error: Field 'fps' is not defined in entity '"+entity_aux.name()+"'.");
		fps = DEFAULT_FPS;
	}
	if (!delayFound) {
		Logger::instance().log("Parser Error: Field 'delay' is not defined in entity '"+entity_aux.name()+"'.");
		delay = DEFAULT_DELAY;
	}

	AnimatedEntity animatedEntity_aux(entity_aux.name(), "", entity_aux.baseWidth(), entity_aux.baseHeight(), entity_aux.pixelRefX(), entity_aux.pixelRefY(), imagesPaths, fps, delay);
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
		} catch (KeyNotFound) {	} catch (InvalidScalar) { }
		catch (Exception& parserException ) {
			Logger::instance().logUnexpected(parserException.what());
		};
		try {
			node[i]["delay"] >> delay;
			isAnimated = true;
		} catch (KeyNotFound) {	} catch (InvalidScalar) { }
		catch (Exception& parserException ) {
			Logger::instance().logUnexpected(parserException.what());
		};

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
	} catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
	try {
		node["x"] >> entityDef.x;
		xFound = true;
		if (entityDef.x<0)
			Logger::instance().log("Parser Error: Negative value in field 'x' in one of the entities '"+entityDef.entity+"'.");
	} catch (KeyNotFound) { } catch (InvalidScalar) { }
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
	try {
		node["y"] >> entityDef.y;
		yFound = true;
		if (entityDef.y<0)
			Logger::instance().log("Parser Error: Negative value in field 'y' in one of the entities '"+entityDef.entity+"'.");
	} catch (KeyNotFound) { } catch (InvalidScalar) { }
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};

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
	}
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
	try {
		node["x"] >> mainCharacter.x;
		xFound = true;
		if (mainCharacter.x<0) {
			Logger::instance().log("Parser Error: Negative value in field 'x' in main character '"+mainCharacter.entityType+"'.");
			mainCharacter.x = DEFAULT_MAIN_CHARACTER_X;
		}
	} catch (KeyNotFound) { } catch (InvalidScalar) { }
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
	try {
		node["y"] >> mainCharacter.y;
		yFound = true;
		if (mainCharacter.y<0) {
			Logger::instance().log("Parser Error: Negative value in field 'y' in main character '"+mainCharacter.entityType+"'.");
			mainCharacter.y = DEFAULT_MAIN_CHARACTER_Y;
		}
	} catch (KeyNotFound) { } catch (InvalidScalar) { }
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};

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
	}
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
	try {
		node["size_x"] >> stage.size_x;
		sizeXFound = true;
		if (stage.size_x<0) {
			Logger::instance().log("Parser Error: Negative value in field 'size_x' in stage '"+stage.name+"'.");
			stage.size_x = DEFAULT_STAGE_SIZE_X;
		}
	} catch (KeyNotFound) { } catch (InvalidScalar) { }
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
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
	} catch (KeyNotFound) { } catch (InvalidScalar) { }
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
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
	} catch (KeyNotFound) { }
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
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
	} catch (KeyNotFound) {	}
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
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

Stage YAMLParser::generateDefaultStage() {
	vector <EntityDef> vEntitiesDef;
	vector <MainCharacter> vMainCharacters;
	map <KeyPair, EntityObject*>* entityMap = new map <KeyPair, EntityObject*>();
	for(int i=0; i<DEFAULT_STAGE_SIZE_X; i++) // Cargo el mapa con entidad objeto default guardada en la primera posición.
		for(int j=0; j<DEFAULT_STAGE_SIZE_Y; j++) {
			KeyPair key(i, j);
			(*entityMap).insert(make_pair(key, &entities.vEntitiesObject[0]));
		}
	vMainCharacters.push_back(generateDefaultMainCharacter()); // Cargo el personaje default.
	Stage stage("DEFAULT", DEFAULT_STAGE_SIZE_X, DEFAULT_STAGE_SIZE_Y, vEntitiesDef, entityMap, vMainCharacters);
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
	map <KeyPair, EntityObject*>* entityMap = new map <KeyPair, EntityObject*>();
	for(unsigned int i=0; i<stage_aux.vEntitiesDef.size(); i++) {
		KeyPair key(stage_aux.vEntitiesDef[i].x, stage_aux.vEntitiesDef[i].y);
		EntityObject *entityObjectType = findEntityObjectType(stage_aux.vEntitiesDef[i].entity);
		AnimatedEntity *animatedEntityType = findAnimatedEntityType(stage_aux.vEntitiesDef[i].entity);
		if ((!entityObjectType) && (!animatedEntityType)){
			Logger::instance().log("Parser Error: Entity type '"+stage_aux.vEntitiesDef[i].entity+"' defined in stage '"+stage_aux.name+"' not found.");
			stage_aux.vEntitiesDef.erase (stage_aux.vEntitiesDef.begin()+i);
			i--;
		}
		else {
			pair<map<KeyPair,EntityObject*>::iterator,bool> ret;
			ret = (*entityMap).insert(make_pair(key, entityObjectType)); // VER LO DE ENTIDADES ANIMADAS
			if (!ret.second) {
				string str_x = static_cast<std::ostringstream*>(&(ostringstream() << stage_aux.vEntitiesDef[i].x))->str();
				string str_y = static_cast<std::ostringstream*>(&(ostringstream() << stage_aux.vEntitiesDef[i].y))->str();
				Logger::instance().log("Parser Error: Position '("+str_x+","+str_y+")' already defined for stage '"+stage_aux.name+"'.");
			}
		}
	}
	for(int i=0; i<stage_aux.size_x; i++) // Completo el mapa con entidad objeto default guardada en la primera posición.
		for(int j=0; j<stage_aux.size_y; j++) {
			KeyPair key(i, j);
			(*entityMap).insert(make_pair(key, &entities.vEntitiesObject[0]));
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
	if (stages.vStages.size()<=0) { // Verifico que exista al menos un escenario.
		Logger::instance().log("Parser Error: No stages found.");
		stages.vStages.push_back(generateDefaultStage());
	}
}

void YAMLParser::loadEverythingByDefault() {
	screen = generateDefaultScreen();
	configuration = generateDefaultConfiguration();
	manageEntityCase();
	manageStageCase();
}

void YAMLParser::parse(string inputFilePath) {
	Node doc;
	bool screenFound = false, stagesFound = false, entitiesFound = false, configurationFound = false;
	ifstream inputFile_aux;

	EntityObject entity_default;
	entities.vEntitiesObject.push_back(entity_default); // Cargo en la primera posición una entidad default.
	
	inputFile_aux.open(inputFilePath);
	if (!inputFile_aux.is_open()) {
		Logger::instance().log("Parser Error: No se pudo abrir el archivo '"+inputFilePath+"'.");
		loadEverythingByDefault();
	}
	else {
		inputFile_aux.close();
		ifstream inputFile(inputFilePath);
		Parser parser(inputFile);
		
		try {
			parser.GetNextDocument(doc);

			try {
				doc["pantalla"] >> screen;
				screenFound = true;
			} catch (KeyNotFound) { }
			catch (Exception& parserException ) {
				Logger::instance().logUnexpected(parserException.what());
			};
			if (!screenFound) {
				Logger::instance().log("Parser Error: Field 'pantalla' is not defined.");
				screen = generateDefaultScreen();
			}

			try {
				doc["configuracion"] >> configuration;
				configurationFound = true;
			} catch (KeyNotFound) { }
			catch (Exception& parserException ) {
				Logger::instance().logUnexpected(parserException.what());
			};
			if (!configurationFound) {
				Logger::instance().log("Parser Error: Field 'configuracion' is not defined.");
				configuration = generateDefaultConfiguration();
			}

			try {
				doc["entidades"] >> entities;
				manageEntityCase();
				entitiesFound = true;
			} catch (KeyNotFound) { }
			catch (Exception& parserException ) {
				Logger::instance().logUnexpected(parserException.what());
			};
			if (!entitiesFound) {
				Logger::instance().log("Parser Error: Field 'entidades' is not defined.");
				manageEntityCase();
			}

			try {
				doc["escenarios"] >> stages;
				manageStageCase();
				stagesFound = true;
			} catch (KeyNotFound) { }
			catch (Exception& parserException ) {
				Logger::instance().logUnexpected(parserException.what());
			};
			if (!stagesFound) {
				Logger::instance().log("Parser Error: Field 'escenarios' is not defined.");
				manageStageCase();
			}
		
		} catch (Exception& parserException) { // Error de sintaxis.
			Logger::instance().logSyntaxError(inputFilePath,parserException.what());
			loadEverythingByDefault();
		};
	}

	for(unsigned int i=0; i<stages.vStages.size(); i++) // Cargo la velocidad de los personajes.
		stages.vStages[i].mainCharacter_speed(configuration.main_character_speed);
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

int YAMLParser::screenWidth() {
	return screen.width;
}

int YAMLParser::screenHeight() {
	return screen.height;
}

int YAMLParser::scrollMargin() {
	return configuration.scroll_margin;
}