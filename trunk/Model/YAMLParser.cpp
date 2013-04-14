#include <windows.h>
#include "YAMLParser.h"


using namespace std;
using namespace YAML;


YAMLParser::YAMLParser() {
}

YAMLParser::~YAMLParser() {
	//vector <AnimatedEntity>::iterator it;
	//for(it = entities.vAnimatedEntities.begin(); it != entities.vAnimatedEntities.end();it++)
	//	it->destroy();
}

void operator >> (const Node& node, Screen& screen) {
	string field;
	bool widthFound = false, heightFound = false;

	for(unsigned int i=0; i<node.size(); i++) {
		field = "ancho";
		try {
			node[i][field] >> screen.width;
			widthFound = true;
			if (screen.width<0) {
				Logger::instance().log("Parser Error: Negative value in field '"+field+"' in 'pantalla'.");
				screen.width = DEFAULT_SCREEN_WIDTH;
			}
		} catch (KeyNotFound) {	} catch (InvalidScalar) {
			widthFound = true;
			Logger::instance().logInvalidValueInConfiguration("pantalla",field,"a positive integer");
			screen.width = DEFAULT_SCREEN_WIDTH;
		}
		catch (Exception& parserException ) {
			Logger::instance().logUnexpected(parserException.what());
		};
		field = "alto";
		try {
			node[i][field] >> screen.height;
			heightFound = true;
			if (screen.height<0) {
				Logger::instance().log("Parser Error: Negative value in field '"+field+"' in 'pantalla'.");
				screen.height = DEFAULT_SCREEN_HEIGHT;
			}
		} catch (KeyNotFound) {	} catch (InvalidScalar) {
			heightFound = true;
			Logger::instance().logInvalidValueInConfiguration("pantalla",field,"a positive integer");
			screen.height = DEFAULT_SCREEN_HEIGHT;
		}
		catch (Exception& parserException ) {
			Logger::instance().logUnexpected(parserException.what());
		};
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
	string field;
	bool mainCharacterSpeedFound = false, scrollMarginFound = false;

	for(unsigned int i=0; i<node.size(); i++) {
		field = "vel_personaje";
		try {
			node[i][field] >> configuration.main_character_speed;
			mainCharacterSpeedFound = true;
			if (configuration.main_character_speed<0) {
				Logger::instance().log("Parser Error: Negative value in field '"+field+"' in 'configuracion'.");
				configuration.main_character_speed = DEFAULT_MAIN_CHARACTER_SPEED;
			}
		} catch (KeyNotFound) {	} catch (InvalidScalar) {
			mainCharacterSpeedFound = true;
			Logger::instance().logInvalidValueInConfiguration("configuracion",field,"a positive integer");
			configuration.main_character_speed = DEFAULT_MAIN_CHARACTER_SPEED;
		}
		catch (Exception& parserException ) {
			Logger::instance().logUnexpected(parserException.what());
		};
		field = "margen_scroll";
		try {
			node[i][field] >> configuration.scroll_margin;
			scrollMarginFound = true;
			if (configuration.scroll_margin<0) {
				Logger::instance().log("Parser Error: Negative value in field '"+field+"' in 'configuracion'.");
				configuration.scroll_margin = DEFAULT_SCROLL_MARGIN;
			}
		} catch (KeyNotFound) {	} catch (InvalidScalar) {
			scrollMarginFound = true;
			Logger::instance().logInvalidValueInConfiguration("configuracion",field,"a positive integer");
			configuration.scroll_margin = DEFAULT_SCROLL_MARGIN;
		}
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

bool isNotDirectory(string file){
	DWORD fileAttr = GetFileAttributesA(file.c_str());
	if (fileAttr & FILE_ATTRIBUTE_DIRECTORY) 
	{
		return false;
	}
	return true;
}

bool canOpenFile(string file){
	DWORD fileAttr = GetFileAttributesA(file.c_str());
	if(INVALID_FILE_ATTRIBUTES == fileAttr)
	{
		return false;
	}
	return true;
}

bool validateImagePath(string imagePath) {
	//if ((imagePath[imagePath.size()-1]!='/') && (imagePath[imagePath.size()-1]!='\\'))// Si no es un directorio.
	if (isNotDirectory(imagePath)) //aca se valida si es directorio
	{ 
		if (imagePath.find(IMAGES_EXTENSION)==string::npos) { // Veo que sea '.png'.
			Logger::instance().log("Parser Error: '"+imagePath+"' does not have a valid extension.");
			return false;
		}

		if (canOpenFile(imagePath)){
			return true;
		}
		
		Logger::instance().log("Parser Error: Unable to open '"+imagePath+"'.");
		return false;

		//ifstream file;
		//file.open(imagePath);
		//if (canOpenFile(imagePath)) { // Veo que exista. //!file.is_open() metodo muy lento
		//	Logger::instance().log("Parser Error: Image path '"+imagePath+"' not found.");
		//	return false;
		//}
		//else {
		//	file.close();
		//	return true;
		//}
	}
	return false;
}

void operator >> (const Node& node, EntityObject& entity) { // ENTIDADES CON NOMBRES IGUALES
	string name, imagePath, field;
	int baseWidth, baseHeight, pixelRefX, pixelRefY;
	bool baseWidthFound = false, baseHeightFound = false, pixelRefXFound = false, pixelRefYFound = false;
	field = "nombre";
	try {
		node[field] >> name;
		if (name=="~")
			name = "";
	} catch (KeyNotFound) {
		name = "";
	}
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
	field = "imagen";
	try {
		node[field] >> imagePath;
		if ((imagePath=="~") || (!validateImagePath(imagePath))){
			imagePath = ERROR_IMAGE;
		}
	} catch (KeyNotFound) {
		Logger::instance().log("Parser Error: Field '"+field+"' is not defined in entity '"+name+"'.");
		imagePath = ERROR_IMAGE;
	}
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
	field = "ancho_base";
	try {
		node[field] >> baseWidth;
		baseWidthFound = true;
		if (baseWidth<0) {
			Logger::instance().log("Parser Error: Negative value in field '"+field+"' in entity '"+name+"'.");
			baseWidth = DEFAULT_BASE_WIDTH;
		}
	} catch (KeyNotFound) { }
	catch (InvalidScalar) {
		baseWidthFound = true;
		Logger::instance().logInvalidValueInEntity(name,field,"a positive integer");
		baseWidth = DEFAULT_BASE_WIDTH;
	}
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
	field = "alto_base";
	try {
		node[field] >> baseHeight;
		baseHeightFound = true;
		if (baseHeight<0) {
			Logger::instance().log("Parser Error: Negative value in field '"+field+"' in entity '"+name+"'.");
			baseHeight = DEFAULT_BASE_HEIGHT;
		}
	} catch (KeyNotFound) { } catch (InvalidScalar) {
		baseHeightFound = true;
		Logger::instance().logInvalidValueInEntity(name,field,"a positive integer");
		baseHeight = DEFAULT_BASE_HEIGHT;
	}
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
	field = "pixel_ref_x";
	try {
		node[field] >> pixelRefX;
		pixelRefXFound = true;
		if (pixelRefX<0) {
			Logger::instance().log("Parser Error: Negative value in field '"+field+"' in entity '"+name+"'.");
			pixelRefX = DEFAULT_PIXEL_REF_X;
		}
	} catch (KeyNotFound) { } catch (InvalidScalar) {
		pixelRefXFound = true;
		Logger::instance().logInvalidValueInEntity(name,field,"a positive integer");
		pixelRefX = DEFAULT_PIXEL_REF_X;
	}
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
	field = "pixel_ref_y";
	try {
		node[field] >> pixelRefY;
		pixelRefYFound = true;
		if (pixelRefY<0) {
			Logger::instance().log("Parser Error: Negative value in field '"+field+"' in entity '"+name+"'.");
			pixelRefY = DEFAULT_PIXEL_REF_Y;
		}
	} catch (KeyNotFound) { } catch (InvalidScalar) {
		pixelRefYFound = true;
		Logger::instance().logInvalidValueInEntity(name,field,"a positive integer");
		pixelRefY = DEFAULT_PIXEL_REF_Y;
	}
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

//DirList* loadImagesPaths(string imageDir) {
//	DirList* dirList = new DirList();
//	if (dirList->createFromDirectory(imageDir)) {
//		while (dirList->hasNext()) {
//			string dir_aux = dirList->nextFullPath();
//			if (dir_aux.find(IMAGES_EXTENSION)==string::npos) // Las imágenes de las entidades animadas deben tener la extensión '.png'.
//				dirList->deletePrevious();
//		}
//		if (dirList->empty())
//			Logger::instance().log("Parser Error: No '.png' images found in the directory '"+imageDir+"'.");
//	}
//	else
//		Logger::instance().log("Parser Error: Image directory '"+imageDir+"' not found.");
//	return dirList;
//}

void operator >> (const Node& node, AnimatedEntity& animatedEntity) {
	int fps, delay;
	string imageDir, field;
	//DirList* imagesPaths;
	bool fpsFound = false, delayFound = false;
	EntityObject entity_aux;
	node >> entity_aux;

	field = "imagen";
	try {
		node[field] >> imageDir;
		//imagesPaths = loadImagesPaths(imageDir);
		animatedEntity.loadImages(imageDir);
		if ((imageDir=="~") || (animatedEntity.hasNoImages())) {
			imageDir = DEFAULT_ANIMATED_DIR;
			animatedEntity.loadImages(DEFAULT_ANIMATED_DIR);
			//imagesPaths = loadImagesPaths(DEFAULT_ANIMATED_DIR);
		}
	} catch (KeyNotFound) {
		//imagesPaths = loadImagesPaths(DEFAULT_ANIMATED_DIR);
		animatedEntity.loadImages(DEFAULT_ANIMATED_DIR);
	}
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
	field = "fps";
	try {
		node[field] >> fps;
		fpsFound = true;
		if (fps<0) {
			Logger::instance().log("Parser Error: Negative value in field '"+field+"' in entity '"+entity_aux.name()+"'.");
			fps = DEFAULT_FPS;
		}
	} catch (KeyNotFound) { } catch (InvalidScalar) {
		fpsFound = true;
		Logger::instance().logInvalidValueInEntity(entity_aux.name(),field,"a positive integer");
		fps = DEFAULT_FPS;
	}
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
	field = "delay";
	try {
		node[field] >> delay;
		delayFound = true;
		if (delay<0) {
			Logger::instance().log("Parser Error: Negative value in field '"+field+"' in entity '"+entity_aux.name()+"'.");
			delay = DEFAULT_DELAY;
		}
	} catch (KeyNotFound) { } catch (InvalidScalar) {
		delayFound = true;
		Logger::instance().logInvalidValueInEntity(entity_aux.name(),field,"a positive integer");
		delay = DEFAULT_DELAY;
	}
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
	animatedEntity.fps(fps);
	animatedEntity.delay(delay);
	//AnimatedEntity animatedEntity_aux(entity_aux.name(), "", entity_aux.baseWidth(), entity_aux.baseHeight(), entity_aux.pixelRefX(), entity_aux.pixelRefY(), imagesPaths, fps, delay);
	//animatedEntity = animatedEntity_aux;
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
	string field;
	bool xFound = false, yFound = false;

	field = "entidad";
	try {
		node[field] >> entityDef.entity;
		if (entityDef.entity=="~")
			entityDef.entity = "";
	} catch (KeyNotFound) {
		entityDef.entity = "";
	} catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
	field = "x";
	try {
		node[field] >> entityDef.x;
		xFound = true;
		if (entityDef.x<0)
			Logger::instance().log("Parser Error: Negative value in field '"+field+"' in one of the entities '"+entityDef.entity+"'.");
	} catch (KeyNotFound) { } catch (InvalidScalar) {
		xFound = true;
		Logger::instance().logInvalidValueInEntityDef(entityDef.entity,field,"a positive integer");
	}
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
	field = "y";
	try {
		node[field] >> entityDef.y;
		yFound = true;
		if (entityDef.y<0)
			Logger::instance().log("Parser Error: Negative value in field '"+field+"' in one of the entities '"+entityDef.entity+"'.");
	} catch (KeyNotFound) { } catch (InvalidScalar) {
		yFound = true;
		Logger::instance().logInvalidValueInEntityDef(entityDef.entity,field,"a positive integer");
	}
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
	string field;
	bool xFound = false, yFound = false;

	field = "tipoEntidad";
	try {
		node[field] >> mainCharacter.entityType;
		if (mainCharacter.entityType=="~")
			mainCharacter.entityType = "";
	} catch (KeyNotFound) {
		mainCharacter.entityType = "";
	}
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
	field = "x";
	try {
		node[field] >> mainCharacter.x;
		xFound = true;
		if (mainCharacter.x<0) {
			Logger::instance().log("Parser Error: Negative value in field '"+field+"' in main character '"+mainCharacter.entityType+"'.");
			mainCharacter.x = DEFAULT_MAIN_CHARACTER_X;
		}
	} catch (KeyNotFound) { } catch (InvalidScalar) {
		xFound = true;
		Logger::instance().logInvalidValueInMainCharacter(mainCharacter.entityType,field,"a positive integer");
		mainCharacter.x = DEFAULT_MAIN_CHARACTER_X;
	}
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
	field = "y";
	try {
		node[field] >> mainCharacter.y;
		yFound = true;
		if (mainCharacter.y<0) {
			Logger::instance().log("Parser Error: Negative value in field '"+field+"' in main character '"+mainCharacter.entityType+"'.");
			mainCharacter.y = DEFAULT_MAIN_CHARACTER_Y;
		}
	} catch (KeyNotFound) { } catch (InvalidScalar) {
		yFound = true;
		Logger::instance().logInvalidValueInMainCharacter(mainCharacter.entityType,field,"a positive integer");
		mainCharacter.y = DEFAULT_MAIN_CHARACTER_Y;
	}
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
	string field;
	bool sizeXFound = false, sizeYFound = false;

	field = "nombre";
	try {
		node[field] >> stage.name;
		if (stage.name=="~")
			stage.name = "";
	} catch (KeyNotFound) {
		stage.name = "";
	}
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
	field = "size_x";
	try {
		node[field] >> stage.size_x;
		sizeXFound = true;
		if (stage.size_x<0) {
			Logger::instance().log("Parser Error: Negative value in field '"+field+"' in stage '"+stage.name+"'.");
			stage.size_x = DEFAULT_STAGE_SIZE_X;
		}
	} catch (KeyNotFound) { } catch (InvalidScalar) {
		sizeXFound = true;
		Logger::instance().logInvalidValueInStage(stage.name,field,"a positive integer");
		stage.size_x = DEFAULT_STAGE_SIZE_X;
	}
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
	if (!sizeXFound) {
		Logger::instance().log("Parser Error: Field '"+field+"' is not defined in stage '"+stage.name+"'.");
		stage.size_x = DEFAULT_STAGE_SIZE_X;
	}
	field = "size_y";
	try {
		node[field] >> stage.size_y;
		sizeYFound = true;
		if (stage.size_y<0) {
			Logger::instance().log("Parser Error: Negative value in field '"+field+"' in stage '"+stage.name+"'.");
			stage.size_y = DEFAULT_STAGE_SIZE_Y;
		}
	} catch (KeyNotFound) { } catch (InvalidScalar) {
		sizeYFound = true;
		Logger::instance().logInvalidValueInStage(stage.name,field,"a positive integer");
		stage.size_y = DEFAULT_STAGE_SIZE_Y;
	}
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
	if (!sizeYFound) {
		Logger::instance().log("Parser Error: Field '"+field+"' is not defined in stage '"+stage.name+"'.");
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
		ifstream inputFile(inputFilePath);//porque se abre 2 veces el archivo??
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