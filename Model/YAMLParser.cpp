#include <windows.h>
#include "YAMLParser.h"
#include "stringUtilities.h"


using namespace std;
using namespace YAML;


YAMLParser::YAMLParser() {
}

YAMLParser::~YAMLParser() {
	if (config)
		delete config;

	for (unsigned i=0; i<entities.vEntitiesObject.size(); i++)
		delete entities.vEntitiesObject[i];
	entities.vEntitiesObject.clear();
	for (unsigned i=0; i<entities.vAnimatedEntities.size(); i++)
		delete entities.vAnimatedEntities[i];
	entities.vAnimatedEntities.clear();
	for (unsigned i=0; i < stages.vStages.size(); i++){
		stages.vStages[i].clearStage();
		stages.vStages_aux[i].vEntitiesDef.clear();
		stages.vStages_aux[i].vMainCharacters.clear();
		stages.vStages_aux[i].vMainCharacters_aux.clear();
		stages.vStages.clear();
		stages.vStages_aux.clear();
	}
}


bool managePositiveIntCase(const Node& node, int &result, string context, string affectedConfig, string field, int defaultValue, ForceDefault force){
	try {
		node[field] >> result;
		if (result < 0) {
			Logger::instance().logInvalidValue(context, field, affectedConfig, "a positive integer");
			result = defaultValue;
		}
	} catch (KeyNotFound) {	
		if ((force == YES) || (force == YES_IGNORE_LOG)){  //fuerzo el valor x default
			result = defaultValue;
			if (force == YES_IGNORE_LOG)
				return true;
			Logger::instance().logFieldNotDefined(context, field , affectedConfig);
			return true;
		}
		return false;
	} catch (InvalidScalar) {
		if ((force == YES) || (force == YES_IGNORE_LOG) || (force == ONLY_INVALID)){  //fuerzo el valor x default
			result = defaultValue;
			if (force == YES_IGNORE_LOG)
				return true;
			Logger::instance().logInvalidValue(context, field, affectedConfig, "a positive integer");
			return true;
		}
		return false;
	}
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
		return false;
	};

	return true;
}

bool managePositiveFloatCase(const Node& node, float &result, string context, string affectedConfig, string field, float defaultValue, ForceDefault force){
	try {
		node[field] >> result;
		if (result < 0) {
			Logger::instance().logInvalidValue(context, field, affectedConfig, "a positive float");
			result = defaultValue;
		}
	} catch (KeyNotFound) {
		if ((force == YES) || (force == YES_IGNORE_LOG)){  //fuerzo el valor x default
			result = defaultValue;
			if (force == YES_IGNORE_LOG)
				return true;
			Logger::instance().logFieldNotDefined(context, field , affectedConfig);
			return true;
		}
		return false;
	} catch (InvalidScalar) {
		if ((force == YES) || (force == YES_IGNORE_LOG) || (force == ONLY_INVALID)){  //fuerzo el valor x default
			result = defaultValue;
			if (force == YES_IGNORE_LOG)
				return true;
			Logger::instance().logInvalidValue(context, field, affectedConfig, "a positive float");
			return true;
		}
		return false;
	}
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
		return false;
	};

	return true;
}


void operator >> (const Node& node, Screen& screen) {
	string field;
	bool widthFound = false, heightFound = false;

	for(unsigned int i=0; i<node.size(); i++) {
		if (!widthFound) {
			widthFound = managePositiveIntCase(node[i],screen.width, "pantalla","","ancho", DEFAULT_SCREEN_WIDTH, ONLY_INVALID);
		}
		/*field = "ancho";
		try {
			node[i][field] >> screen.width;
			widthFound = true;
			if (screen.width<0) {
				Logger::instance().logInvalidValue("pantalla", field, "", "a positive integer");
				screen.width = DEFAULT_SCREEN_WIDTH;
			}
		} catch (KeyNotFound) {	} catch (InvalidScalar) {
			widthFound = true;
			Logger::instance().logInvalidValue("pantalla", field, "", "a positive integer");
			screen.width = DEFAULT_SCREEN_WIDTH;
		}
		catch (Exception& parserException ) {
			Logger::instance().logUnexpected(parserException.what());
		};*/
		if (!heightFound) {
			heightFound = managePositiveIntCase(node[i],screen.height, "pantalla","","alto", DEFAULT_SCREEN_HEIGHT, ONLY_INVALID);
		}
		//field = "alto";
		//try {
		//	node[i][field] >> screen.height;
		//	heightFound = true;
		//	if (screen.height<0) {
		//		Logger::instance().logInvalidValue("pantalla", field, "", "a positive integer");
		//		screen.height = DEFAULT_SCREEN_HEIGHT;
		//	}
		//} catch (KeyNotFound) {	} catch (InvalidScalar) {
		//	heightFound = true;
		//	Logger::instance().logInvalidValue("pantalla", field, "", "a positive integer");
		//	screen.height = DEFAULT_SCREEN_HEIGHT;
		//}
		//catch (Exception& parserException ) {
		//	Logger::instance().logUnexpected(parserException.what());
		//};
	}

	if (!widthFound) {
		Logger::instance().logFieldNotDefined("pantalla", "ancho", "");
		screen.width = DEFAULT_SCREEN_WIDTH;
	}
	if (!heightFound) {
		Logger::instance().logFieldNotDefined("pantalla", "alto", "");
		screen.height = DEFAULT_SCREEN_HEIGHT;
	}
}

void operator >> (const Node& node, Config& configuration) {
	string field;
	bool mainCharacterSpeedFound = false, scrollMarginFound = false, visionRangeFound = false, serverPortFound = false;
	
	for(unsigned int i=0; i<node.size(); i++) {
		if (! mainCharacterSpeedFound){
			mainCharacterSpeedFound = managePositiveFloatCase(node[i],configuration.main_character_speed,"configuracion","","vel_personaje",DEFAULT_MAIN_CHARACTER_SPEED, ONLY_INVALID);
		}
		//field = "vel_personaje";
		//try {
		//	node[i][field] >> configuration.main_character_speed;
		//	mainCharacterSpeedFound = true;
		//	if (configuration.main_character_speed <= 0) {
		//		Logger::instance().logInvalidValue("configuracion", field, "", "a positive float");
		//		configuration.main_character_speed = DEFAULT_MAIN_CHARACTER_SPEED;
		//	}
		//} catch (KeyNotFound) {	} catch (InvalidScalar) {
		//	mainCharacterSpeedFound = true;
		//	Logger::instance().logInvalidValue("configuracion", field, "", "a positive float");
		//	configuration.main_character_speed = DEFAULT_MAIN_CHARACTER_SPEED;
		//}
		//catch (Exception& parserException ) {
		//	Logger::instance().logUnexpected(parserException.what());
		//};
		if (!visionRangeFound){
			visionRangeFound = managePositiveIntCase(node[i], configuration.vision_range,"configuracion", "","vision_personaje",DEFAULT_VISION_RANGE, ONLY_INVALID);
		}
		if (!serverPortFound){
			serverPortFound = managePositiveIntCase(node[i], configuration.port,"configuracion", "","puerto_servidor",DEFAULT_SERVER_PORT, ONLY_INVALID);
		}
		if (!scrollMarginFound){
			scrollMarginFound = managePositiveIntCase(node[i], configuration.scroll_margin,"configuracion", "","margen_scroll",DEFAULT_SCROLL_MARGIN, ONLY_INVALID);
		}
		//field = "margen_scroll";
		//try {
		//	node[i][field] >> configuration.scroll_margin;
		//	scrollMarginFound = true;
		//	if (configuration.scroll_margin<0) {
		//		Logger::instance().logInvalidValue("configuracion", field, "", "a positive float");
		//		configuration.scroll_margin = DEFAULT_SCROLL_MARGIN;
		//	}
		//} catch (KeyNotFound) {	} catch (InvalidScalar) {
		//	scrollMarginFound = true;
		//	Logger::instance().logInvalidValue("configuracion", field, "", "a positive integer");
		//	configuration.scroll_margin = DEFAULT_SCROLL_MARGIN;
		//}
		//catch (Exception& parserException ) {
		//	Logger::instance().logUnexpected(parserException.what());
		//};
	}

	if (!mainCharacterSpeedFound) {
		Logger::instance().logFieldNotDefined("configuración", "vel_personaje", "");
		configuration.main_character_speed = DEFAULT_MAIN_CHARACTER_SPEED;
	}
	if (!scrollMarginFound) {
		Logger::instance().logFieldNotDefined("configuración", "margen_scroll", "");
		configuration.scroll_margin = DEFAULT_SCROLL_MARGIN;
	}

	if (!visionRangeFound){
		Logger::instance().logFieldNotDefined("configuración", "vision_personaje", "");
		configuration.vision_range = DEFAULT_VISION_RANGE;
	}
	if (!serverPortFound){
		Logger::instance().logFieldNotDefined("configuración", "puerto_servidor", "");
		configuration.port = DEFAULT_SERVER_PORT;
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
	if (isNotDirectory(imagePath)) //aca se valida si es directorio
	{ 
		if (imagePath.find(IMAGES_EXTENSION) == string::npos) { // Veo que sea '.png'.
			Logger::instance().log("Parser Error: '"+imagePath+"' does not have a valid extension.");
			return false;
		}

		if (canOpenFile(imagePath)){
			return true;
		}
		
		Logger::instance().log("Parser Error: Unable to open '"+imagePath+"'.");
		return false;
	}
	return false;
}

void operator >> (const Node& node, EntityObject* &entity) { // ENTIDADES CON NOMBRES IGUALES
	string name, imagePath, field;
	int baseWidth, baseHeight, pixelRefX, pixelRefY;
	bool baseWidthFound = false, baseHeightFound = false, pixelRefXFound = false, pixelRefYFound = false, imagePathFound = false;

	entity = new EntityObject();
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
		imagePathFound = true;
		if ((imagePath=="~") || (!validateImagePath(imagePath))){
			imagePathFound = false;
			imagePath = ERROR_IMAGE;
		}
	} catch (KeyNotFound) {
		Logger::instance().logFieldNotDefined(name, field, "entity");
		imagePath = ERROR_IMAGE;
	}
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
	baseWidthFound = managePositiveIntCase(node,baseWidth,name, "entity","ancho_base",DEFAULT_BASE_WIDTH, NO);
	//field = "ancho_base";
	//try {
	//	node[field] >> baseWidth;
	//	baseWidthFound = true;
	//	if (baseWidth<0) {
	//		Logger::instance().logInvalidValue(name, field, "entity", "a positive integer");
	//		baseWidth = DEFAULT_BASE_WIDTH;
	//	}
	//} catch (KeyNotFound) { }
	//catch (InvalidScalar) {
	//	baseWidthFound = true;
	//	Logger::instance().logInvalidValue(name, field, "entity", "a positive integer");
	//	baseWidth = DEFAULT_BASE_WIDTH;
	//}
	//catch (Exception& parserException ) {
	//	Logger::instance().logUnexpected(parserException.what());
	//};
	if (!baseHeightFound){
		baseHeightFound = managePositiveIntCase(node, baseHeight, name, "entity","alto_base", DEFAULT_BASE_HEIGHT, YES);
	}
	//field = "alto_base";
	//try {
	//	node[field] >> baseHeight;
	//	baseHeightFound = true;
	//	if (baseHeight<0) {
	//		Logger::instance().logInvalidValue(name, field, "entity", "a positive integer");
	//		baseHeight = DEFAULT_BASE_HEIGHT;
	//	}
	//} catch (KeyNotFound) { } catch (InvalidScalar) {
	//	baseHeightFound = true;
	//	Logger::instance().logInvalidValue(name, field, "entity", "a positive integer");
	//	baseHeight = DEFAULT_BASE_HEIGHT;
	//}
	//catch (Exception& parserException ) {
	//	Logger::instance().logUnexpected(parserException.what());
	//};
	if (!pixelRefXFound){
		pixelRefXFound = managePositiveIntCase(node, pixelRefX, name, "entity","pixel_ref_x",DEFAULT_ENTITY_OBJECT_PIXEL_REF_X, YES);
	}
	//field = "pixel_ref_x";
	//try {
	//	node[field] >> pixelRefX;
	//	pixelRefXFound = true;
	//	if (pixelRefX<0) {
	//		Logger::instance().logInvalidValue(name, field, "entity", "a positive integer");
	//		pixelRefX = DEFAULT_ENTITY_OBJECT_PIXEL_REF_X;
	//	}
	//} catch (KeyNotFound) { } catch (InvalidScalar) {
	//	pixelRefXFound = true;
	//	Logger::instance().logInvalidValue(name, field, "entity", "a positive integer");
	//	pixelRefX = DEFAULT_ENTITY_OBJECT_PIXEL_REF_X;
	//}
	//catch (Exception& parserException ) {
	//	Logger::instance().logUnexpected(parserException.what());
	//};
	if (!pixelRefYFound){
		pixelRefYFound = managePositiveIntCase(node, pixelRefY, name, "entity","pixel_ref_y",DEFAULT_ENTITY_OBJECT_PIXEL_REF_Y, YES);
	}
	//field = "pixel_ref_y";
	//try {
	//	node[field] >> pixelRefY;
	//	pixelRefYFound = true;
	//	if (pixelRefY<0) {
	//		Logger::instance().logInvalidValue(name, field, "entity", "a positive integer");
	//		pixelRefY = DEFAULT_ENTITY_OBJECT_PIXEL_REF_Y;
	//	}
	//} catch (KeyNotFound) { } catch (InvalidScalar) {
	//	pixelRefYFound = true;
	//	Logger::instance().logInvalidValue(name, field, "entity", "a positive integer");
	//	pixelRefY = DEFAULT_ENTITY_OBJECT_PIXEL_REF_Y;
	//}
	//catch (Exception& parserException ) {
	//	Logger::instance().logUnexpected(parserException.what());
	//};

	if (!baseWidthFound) {
		Logger::instance().logFieldNotDefined(name, "ancho_base", "entity");
		baseWidth = DEFAULT_BASE_WIDTH;
	}
	if (!baseHeightFound) {
		Logger::instance().logFieldNotDefined(name, "alto_base", "entity");
		baseHeight = DEFAULT_BASE_WIDTH;
	}
	if (!pixelRefXFound) {
		Logger::instance().logFieldNotDefined(name, "pixel_ref_x", "entity");
		pixelRefX = DEFAULT_ENTITY_OBJECT_PIXEL_REF_X;
	}
	if (!pixelRefYFound) {
		Logger::instance().logFieldNotDefined(name, "pixel_ref_y", "entity");
		pixelRefY = DEFAULT_ENTITY_OBJECT_PIXEL_REF_Y;
	}
	if (!imagePathFound) {
		pixelRefX = ERROR_IMAGE_PIXEL_REF_X;
		pixelRefY = ERROR_IMAGE_PIXEL_REF_Y;
	}

	entity->name(name);
	entity->imagePath(imagePath);
	entity->baseWidth(baseWidth);
	entity->baseHeight(baseHeight);
	entity->pixelRefX(pixelRefX);
	entity->pixelRefY(pixelRefY);
}

void operator >> (const Node& node, AnimatedEntity* &animatedEntity) {
	int pixelRefX, pixelRefY, fps, delay;
	string imageDir, field;
	bool pixelRefXFound = false, pixelRefYFound = false, fpsFound = false, delayFound = false, imageDirFound = false;

	EntityObject *entity_aux;
	node >> entity_aux;
	animatedEntity = new AnimatedEntity();
	field = "imagen";
	try {
		node[field] >> imageDir;
		if (!(imageDir=="~")) {
			animatedEntity->loadImages(imageDir);
			imageDirFound = true;
			if ((animatedEntity->hasNoDir()) && (animatedEntity->hasNoImages())) {
				imageDirFound = false;
				imageDir = ERROR_ANIMATED_DIR;
				animatedEntity->loadImages(imageDir);
			} 
			if (animatedEntity->hasNoImages()){
				animatedEntity->imagesPaths()->loadFromDir(DEFAULT_ANIMATED_DIR);
			}
		}
		else {
			imageDir = ERROR_ANIMATED_DIR;
			animatedEntity->loadImages(imageDir);
		}
	} catch (KeyNotFound) {
		imageDir = ERROR_ANIMATED_DIR;
		animatedEntity->loadImages(imageDir);
	}
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};

	if (!pixelRefXFound){
		pixelRefXFound = managePositiveIntCase(node, pixelRefX, entity_aux->name(), "entity","pixel_ref_x",DEFAULT_ANIMATED_ENTITY_PIXEL_REF_X, YES_IGNORE_LOG);
	}
	//field = "pixel_ref_x";
	//try {
	//	node[field] >> pixelRefX;
	//	pixelRefXFound = true;
	//	if (pixelRefX<0)
	//		pixelRefX = DEFAULT_ANIMATED_ENTITY_PIXEL_REF_X;
	//} catch (KeyNotFound) { } catch (InvalidScalar) {
	//	pixelRefXFound = true;
	//	pixelRefX = DEFAULT_ANIMATED_ENTITY_PIXEL_REF_X;
	//}
	//catch (Exception& parserException ) {
	//	Logger::instance().logUnexpected(parserException.what());
	//};
	if (!pixelRefYFound){
		pixelRefYFound = managePositiveIntCase(node, pixelRefY, entity_aux->name(), "entity","pixel_ref_y",DEFAULT_ANIMATED_ENTITY_PIXEL_REF_Y, YES_IGNORE_LOG);
	}
	//field = "pixel_ref_y";
	//try {
	//	node[field] >> pixelRefY;
	//	pixelRefYFound = true;
	//	if (pixelRefY<0)
	//		pixelRefY = DEFAULT_ANIMATED_ENTITY_PIXEL_REF_Y;
	//} catch (KeyNotFound) { } catch (InvalidScalar) {
	//	pixelRefYFound = true;
	//	pixelRefY = DEFAULT_ANIMATED_ENTITY_PIXEL_REF_Y;
	//}
	//catch (Exception& parserException ) {
	//	Logger::instance().logUnexpected(parserException.what());
	//};

	if (!fpsFound){
		fpsFound = managePositiveIntCase(node, fps, entity_aux->name(), "entity","fps",DEFAULT_FPS, YES);
	}
	//field = "fps";
	//try {
	//	node[field] >> fps;
	//	fpsFound = true;
	//	if (fps<0) {
	//		Logger::instance().logInvalidValue(entity_aux->name(), field, "entity", "a positive integer");
	//		fps = DEFAULT_FPS;
	//	}
	//} catch (KeyNotFound) { } catch (InvalidScalar) {
	//	fpsFound = true;
	//	Logger::instance().logInvalidValue(entity_aux->name(), field, "entity", "a positive integer");
	//	fps = DEFAULT_FPS;
	//}
	//catch (Exception& parserException ) {
	//	Logger::instance().logUnexpected(parserException.what());
	//};
	if (!delayFound){
		delayFound = managePositiveIntCase(node, delay, entity_aux->name(), "entity","delay",DEFAULT_DELAY, YES);
	}
	//field = "delay";
	//try {
	//	node[field] >> delay;
	//	delayFound = true;
	//	if (delay<0) {
	//		Logger::instance().logInvalidValue(entity_aux->name(), field, "entity", "a positive integer");
	//		delay = DEFAULT_DELAY;
	//	}
	//} catch (KeyNotFound) { } catch (InvalidScalar) {
	//	delayFound = true;
	//	Logger::instance().logInvalidValue(entity_aux->name(), field, "entity", "a positive integer");
	//	delay = DEFAULT_DELAY;
	//}
	//catch (Exception& parserException ) {
	//	Logger::instance().logUnexpected(parserException.what());
	//};

	if (!fpsFound) {
		Logger::instance().logFieldNotDefined(entity_aux->name(), "fps", "entity");
		fps = DEFAULT_FPS;
	}
	if (!delayFound) {
		Logger::instance().logFieldNotDefined(entity_aux->name(), "delay", "entity");
		delay = DEFAULT_DELAY;
	}
	//if (!pixelRefXFound)
	//	pixelRefX = DEFAULT_ANIMATED_ENTITY_PIXEL_REF_X;
	//if (!pixelRefYFound)
	//	pixelRefY = DEFAULT_ANIMATED_ENTITY_PIXEL_REF_Y;
	if (!imageDirFound) {
		pixelRefX = ERROR_ANIMATED_PIXEL_REF_X;
		pixelRefY = ERROR_ANIMATED_PIXEL_REF_Y;
	}

	animatedEntity->name(entity_aux->name());
	animatedEntity->baseWidth(entity_aux->baseWidth());
	animatedEntity->baseHeight(entity_aux->baseHeight());
	animatedEntity->pixelRefX(pixelRefX);
	animatedEntity->pixelRefY(pixelRefY);
	animatedEntity->fps(fps);
	animatedEntity->delay(delay);
	delete entity_aux;
}

void operator >> (const Node& node, EntLists& entities) {
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
			AnimatedEntity* entity;
			node[i] >> entity;
			if (entity->name().size() > 0) // Si tiene nombre se guarda.
				entities.vAnimatedEntities.push_back(entity);
		}
		else {
			EntityObject* entity;
			node[i] >> entity;
			if (entity->name().size() > 0) // Si tiene nombre se guarda.
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
			Logger::instance().logInvalidValue(entityDef.entity, field, "one of the entities", "a positive integer");
	} catch (KeyNotFound) { } catch (InvalidScalar) {
		xFound = true;
		Logger::instance().logInvalidValue(entityDef.entity, field, "one of the entities", "a positive integer");
	}
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
	field = "y";
	try {
		node[field] >> entityDef.y;
		yFound = true;
		if (entityDef.y<0)
			Logger::instance().logInvalidValue(entityDef.entity, field, "one of the entities", "a positive integer");
	} catch (KeyNotFound) { } catch (InvalidScalar) {
		yFound = true;
		Logger::instance().logInvalidValue(entityDef.entity, field, "one of the entities", "a positive integer");
	}
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};

	if (!xFound)
		Logger::instance().logFieldNotDefined(entityDef.entity, "x", "one of the entities");
	if (!yFound)
		Logger::instance().logFieldNotDefined(entityDef.entity, "y", "one of the entities");
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
	xFound = managePositiveIntCase(node, mainCharacter.x, mainCharacter.entityType, "main character","x",DEFAULT_MAIN_CHARACTER_X, YES);
	/*field = "x";
	try {
		node[field] >> mainCharacter.x;
		xFound = true;
		if (mainCharacter.x<0) {
			Logger::instance().logInvalidValue(mainCharacter.entityType, field, "main character", "a positive integer");
			mainCharacter.x = DEFAULT_MAIN_CHARACTER_X;
		}
	} 
	catch (KeyNotFound) { }
	catch (InvalidScalar) {
		xFound = true;
		Logger::instance().logInvalidValue(mainCharacter.entityType, field, "main character", "a positive integer");
		mainCharacter.x = DEFAULT_MAIN_CHARACTER_X;
	}
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};*/
	yFound = managePositiveIntCase(node,  mainCharacter.y, mainCharacter.entityType, "main character","y",DEFAULT_MAIN_CHARACTER_Y, YES);
	//field = "y";
	//try {
	//	node[field] >> mainCharacter.y;
	//	yFound = true;
	//	if (mainCharacter.y<0) {
	//		Logger::instance().logInvalidValue(mainCharacter.entityType, field, "main character", "a positive integer");
	//		mainCharacter.y = DEFAULT_MAIN_CHARACTER_Y;
	//	}
	//} catch (KeyNotFound) { } catch (InvalidScalar) {
	//	yFound = true;
	//	Logger::instance().logInvalidValue(mainCharacter.entityType, field, "main character", "a positive integer");
	//	mainCharacter.y = DEFAULT_MAIN_CHARACTER_Y;
	//}
	//catch (Exception& parserException ) {
	//	Logger::instance().logUnexpected(parserException.what());
	//};

	//if (!xFound) {
	//	Logger::instance().logFieldNotDefined(mainCharacter.entityType, "x", "main character");
	//	mainCharacter.x = DEFAULT_MAIN_CHARACTER_X;
	//}
	//if (!yFound) {
	//	Logger::instance().logFieldNotDefined(mainCharacter.entityType, "y", "main character");
	//	mainCharacter.y = DEFAULT_MAIN_CHARACTER_Y;
	//}
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
	sizeXFound = managePositiveIntCase(node, stage.size_x, stage.name, "stage","size_x",DEFAULT_STAGE_SIZE_X, YES);
	//field = "size_x";
	//try {
	//	node[field] >> stage.size_x;
	//	sizeXFound = true;
	//	if (stage.size_x<0) {
	//		Logger::instance().logInvalidValue(stage.name, field, "stage", "a positive integer");
	//		stage.size_x = DEFAULT_STAGE_SIZE_X;
	//	}
	//} catch (KeyNotFound) { } catch (InvalidScalar) {
	//	sizeXFound = true;
	//	Logger::instance().logInvalidValue(stage.name, field, "stage", "a positive integer");
	//	stage.size_x = DEFAULT_STAGE_SIZE_X;
	//}
	//catch (Exception& parserException ) {
	//	Logger::instance().logUnexpected(parserException.what());
	//};
	//if (!sizeXFound) {
	//	Logger::instance().logFieldNotDefined(stage.name, field, "stage");
	//	stage.size_x = DEFAULT_STAGE_SIZE_X;
	//}
	sizeYFound = managePositiveIntCase(node, stage.size_y, stage.name, "stage","size_y",DEFAULT_STAGE_SIZE_Y, YES);
	/*field = "size_y";
	try {
		node[field] >> stage.size_y;
		sizeYFound = true;
		if (stage.size_y<0) {
			Logger::instance().logInvalidValue(stage.name, field, "stage", "a positive integer");
			stage.size_y = DEFAULT_STAGE_SIZE_Y;
		}
	} catch (KeyNotFound) { } catch (InvalidScalar) {
		sizeYFound = true;
		Logger::instance().logInvalidValue(stage.name, field, "stage", "a positive integer");
		stage.size_y = DEFAULT_STAGE_SIZE_Y;
	}
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
	if (!sizeYFound) {
		Logger::instance().logFieldNotDefined(stage.name, field, "stage");
		stage.size_y = DEFAULT_STAGE_SIZE_Y;
	}*/

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
		for( unsigned int i=0 ; i < node_aux.size(); i++) {
			sMainCharacter mainCharacter;
			node_aux[i] >> mainCharacter;
			if ( mainCharacter.entityType.size() > 0 ) {
				if ((mainCharacter.x >= stage.size_x) || (mainCharacter.y >= stage.size_y)) {
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
	for(unsigned int i=0; i < node.size(); i++) {
		sStage stage;
		node[i] >> stage;
		if (stage.name.size() > 0) // Si tiene nombre se guarda.
			stages.vStages_aux.push_back(stage);
		else {
			string str_i = static_cast<std::ostringstream*>(&(ostringstream() << i+1))->str();
			Logger::instance().logFieldNotDefined(str_i, "nombre", "stage number");
		}
	}
}

Config YAMLParser::generateDefaultConfiguration() {
	Config configuration;
	configuration.main_character_speed = DEFAULT_MAIN_CHARACTER_SPEED;
	configuration.scroll_margin = DEFAULT_SCROLL_MARGIN;
	configuration.port = DEFAULT_SERVER_PORT;
	configuration.vision_range = DEFAULT_VISION_RANGE;
	return configuration;
}

Screen YAMLParser::generateDefaultScreen() {
	Screen screen;
	screen.width = DEFAULT_SCREEN_WIDTH;
	screen.height = DEFAULT_SCREEN_HEIGHT;
	return screen;
}

PersonajeModelo* YAMLParser::generateDefaultMainCharacter() {
	//if (entities.vAnimatedEntities.size()<=0) {
	//	AnimatedEntity* animatedEntity_default = new AnimatedEntity() ;
	//	entities.vAnimatedEntities.push_back(animatedEntity_default);
	//}
	PersonajeModelo *mainCharacter = new PersonajeModelo();
	mainCharacter->setCurrent(DEFAULT_MAIN_CHARACTER_X, DEFAULT_MAIN_CHARACTER_Y);
	mainCharacter->setDestino(DEFAULT_MAIN_CHARACTER_X, DEFAULT_MAIN_CHARACTER_Y);
	mainCharacter->animation(entities.vAnimatedEntities[0]); // Uso la primera entidad porque ahí va estar el default en caso de no haber ninguna entidad.
	return mainCharacter;
}

StageModel YAMLParser::generateDefaultStage() {
	vector <EntityDef> vEntitiesDef;
	vector <PersonajeModelo*> vMainCharacters;
	map <KeyPair, EntityObject*>* entityMap = new map <KeyPair, EntityObject*>();
	for(int i=0; i<DEFAULT_STAGE_SIZE_X; i++) // Cargo el mapa con entidad objeto default guardada en la primera posición.
		for(int j=0; j<DEFAULT_STAGE_SIZE_Y; j++) {
			KeyPair key(i, j);
			(*entityMap).insert(make_pair(key, entities.vEntitiesObject[0]));
		}
	vMainCharacters.push_back(generateDefaultMainCharacter()); // Cargo el personaje default.

	StageModel stage("DEFAULT", DEFAULT_STAGE_SIZE_X, DEFAULT_STAGE_SIZE_Y, vEntitiesDef, entityMap, vMainCharacters);
	return stage;
}

AnimatedEntity* YAMLParser::findAnimatedEntityType(string name) {
	unsigned int i = 0;
	bool found = false;
	while ((i<entities.vAnimatedEntities.size()) && (!found)) {
		if (entities.vAnimatedEntities[i]->name() == name)
			found = true;
		else
			i++;
	}
	if (found)
		return entities.vAnimatedEntities[i];
	return NULL;
}

EntityObject* YAMLParser::findEntityObjectType(string name) {
	unsigned int i = 0;
	bool found = false;
	while ((i<entities.vEntitiesObject.size()) && (!found)) {
		if (entities.vEntitiesObject[i]->name() == name)
			found = true;
		else
			i++;
	}
	if (found)
		return entities.vEntitiesObject[i];
	return NULL;
}

bool YAMLParser::entityBaseIsInMapRange(int entityDef_index, sStage stage_aux, EntityObject *entityObjectType, AnimatedEntity *animatedEntityType) {
	EntityDef entityDef = stage_aux.vEntitiesDef[entityDef_index];
	if (entityObjectType) {
		if (((entityDef.x+entityObjectType->baseWidth()-1)<stage_aux.size_x) && ((entityDef.y+entityObjectType->baseHeight()-1)<stage_aux.size_y))
			return true;
	}
	else
		if (animatedEntityType) {
			if (((entityDef.x+animatedEntityType->baseWidth()-1)<stage_aux.size_x) && ((entityDef.y+animatedEntityType->baseHeight()-1)<stage_aux.size_y))
				return true;
		}
	return false;
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
			stage_aux.vEntitiesDef.erase(stage_aux.vEntitiesDef.begin()+i);
			i--;
		}
		else {
			if (entityBaseIsInMapRange(i, stage_aux, entityObjectType, animatedEntityType)) {
				pair<map<KeyPair,EntityObject*>::iterator,bool> ret;
				ret = (*entityMap).insert(make_pair(key, entityObjectType)); // VER LO DE ENTIDADES ANIMADAS
				//if (!ret.second) {
				//	string str_x = static_cast<std::ostringstream*>(&(ostringstream() << stage_aux.vEntitiesDef[i].x))->str();
				//	string str_y = static_cast<std::ostringstream*>(&(ostringstream() << stage_aux.vEntitiesDef[i].y))->str();
				//	Logger::instance().log("Parser Error: Position '("+str_x+","+str_y+")' already defined for stage '"+stage_aux.name+"'.");
				//}
			}
			else {
				Logger::instance().log("Parser Error: Entity '"+stage_aux.vEntitiesDef[i].entity+"''s base is out of map range.");
				stage_aux.vEntitiesDef.erase(stage_aux.vEntitiesDef.begin()+i);
				i--;
			}
		}
	}
	for(int i=0; i<stage_aux.size_x; i++) // Completo el mapa con entidad objeto default guardada en la primera posición.
		for(int j=0; j<stage_aux.size_y; j++) {
			KeyPair key(i, j);
			(*entityMap).insert(make_pair(key, entities.vEntitiesObject[0]));
		}
	StageModel stage(stage_aux.name, stage_aux.size_x, stage_aux.size_y, stage_aux.vEntitiesDef, entityMap, stage_aux.vMainCharacters);
	stages.vStages.push_back(stage);
}

void YAMLParser::loadMainCharacters(int stage_index) {
	sStage stage_aux = stages.vStages_aux[stage_index];
	for(unsigned int j=0; j < stage_aux.vMainCharacters_aux.size(); j++) {
		sMainCharacter mainCharacter_aux = stage_aux.vMainCharacters_aux[j];
		AnimatedEntity *animatedEntityType = findAnimatedEntityType(mainCharacter_aux.entityType);
		if (!animatedEntityType)
			Logger::instance().log("Parser Error: Entity type '"+mainCharacter_aux.entityType+"' for main character in stage '"+stage_aux.name+"' not found.");
		else {
			if (animatedEntityType->imagesPaths()->countDir() >= NUMBER_OF_IMAGE_DIRECTORIES_MAIN_CHARACTER) {
				PersonajeModelo* mainCharacter = new PersonajeModelo();
				mainCharacter->setCurrent(mainCharacter_aux.x, mainCharacter_aux.y);
				mainCharacter->setDestino(mainCharacter_aux.x, mainCharacter_aux.y);
				mainCharacter->animation(animatedEntityType);
				stage_aux.vMainCharacters.push_back(mainCharacter);
			}
			else {
				string str_nro = StringUtilities::intToString(NUMBER_OF_IMAGE_DIRECTORIES_MAIN_CHARACTER);
				Logger::instance().log("Parser Error: Entity type '"+mainCharacter_aux.entityType+"' for main character in stage '"+stage_aux.name+"' does not have the "+str_nro+" image directories needed.");
			}
		}
	}
	if (stage_aux.vMainCharacters.size() <= 0) { // Verifico que para cada escenario exista al menos un protagonista.
		Logger::instance().logFieldNotDefined(stage_aux.name, "protagonista", "stage");
		stage_aux.vMainCharacters.push_back(generateDefaultMainCharacter());
	}
	stages.vStages_aux[stage_index] = stage_aux;
}

void YAMLParser::manageEntityCase() {
	if (entities.vAnimatedEntities.size() <= 0) { // Verifico que exista al menos una entidad animada.	
		Logger::instance().log("Parser Error: No animated entities found.");
		AnimatedEntity* animatedEntity = new AnimatedEntity();
		entities.vAnimatedEntities.push_back(animatedEntity);
	}
}

void YAMLParser::manageStageCase() {
	for(unsigned int i=0; i < stages.vStages_aux.size(); i++) {
		loadMainCharacters(i);
		loadEntitiesToMap(i);
	}
	if (stages.vStages.size() <= 0) { // Verifico que exista al menos un escenario.
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

void YAMLParser::parse() {
	bool yamlFilesFound = false,screenFound = false, stagesFound = false, entitiesFound = false, configurationFound = false;
	Node doc;
	DirList yamlFiles;
	yamlFiles.setExtensionRequired(CONFIGFILE_EXTENSION);
	if (yamlFiles.createFromDirectory(CONFIGFILE_DIRECTORY)) {
		if (yamlFiles.empty())
			Logger::instance().log("Parser Error: No '.yaml' files found.");
		else
			yamlFilesFound = true;
	}
	config = new Configuration();
	EntityObject *entity_default = new EntityObject();
	entities.vEntitiesObject.push_back(entity_default); // Cargo en la primera posición una entidad default.
	AnimatedEntity* animatedEntity_default = new AnimatedEntity() ;
	entities.vAnimatedEntities.push_back(animatedEntity_default);
	
	if (!yamlFilesFound)
		loadEverythingByDefault();
	else {
		string inputFilePath = yamlFiles.nextFullPath();
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
		//camera->initialize(screen.width,screen.height,configuration.scroll_margin);
		config->serverPort(configuration.port);
		config->cameraMarginScroll(configuration.scroll_margin);
		config->cameraWidth(screen.width);
		config->cameraHeight(screen.height);
		config->visionRange(configuration.vision_range);
		config->mainCharacterSpeed(configuration.main_character_speed);
	}

	//for(unsigned int i=0; i<stages.vStages.size(); i++) // Cargo la velocidad de los personajes.
	//	stages.vStages[i].mainCharacter_speed(configuration.main_character_speed);
}

vector <StageModel> YAMLParser::vStages() {
	return stages.vStages;
}

PersonajeModelo* YAMLParser::modelMainCharacters(unsigned stage, unsigned pers){
	if ((stage >= stages.vStages.size()) || (stages.vStages[stage].modelMainCharacters(pers) == NULL)){
		Logger::instance().nullPointer("function PersonajeModelo* YAMLParser::modelMainCharacters");
		return NULL;
	}
	return stages.vStages[stage].modelMainCharacters(pers);
}

Configuration* YAMLParser::getConfig(){
	return config;
}

EntLists YAMLParser::allLists(){
	return entities;
}

