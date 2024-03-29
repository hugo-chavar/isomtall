#include <windows.h>
#include "YAMLParser.h"
#include "StringUtilities.h"


using namespace std;
using namespace YAML;


YAMLParser::YAMLParser() {
}

YAMLParser::~YAMLParser() {
	for (unsigned i=0; i<entities.vEntitiesObject.size(); i++)
		delete entities.vEntitiesObject[i];
	entities.vEntitiesObject.clear();
	for (unsigned i=0; i<entities.vAnimatedEntities.size(); i++)
		delete entities.vAnimatedEntities[i];
	entities.vAnimatedEntities.clear();
	for (unsigned i=0; i < stages.vStages.size(); i++){
		stages.vStages[i].clearStage();
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
		if ((force == YES) || (force == YES_IGNORE_LOG) || (force == ONLY_INVALID)){
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
		if ((force == YES) || (force == YES_IGNORE_LOG)) {  //fuerzo el valor x default
			result = defaultValue;
			if (force == YES_IGNORE_LOG)
				return true;
			Logger::instance().logFieldNotDefined(context, field , affectedConfig);
			return true;
		}
		return false;
	} catch (InvalidScalar) {
		if ((force == YES) || (force == YES_IGNORE_LOG) || (force == ONLY_INVALID)){ 
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

	for(unsigned int i = 0; i < node.size(); i++) {
		if (!widthFound) {
			widthFound = managePositiveIntCase(node[i],screen.width, "pantalla","","ancho", DEFAULT_SCREEN_WIDTH, ONLY_INVALID);
		}

		if (!heightFound) {
			heightFound = managePositiveIntCase(node[i],screen.height, "pantalla","","alto", DEFAULT_SCREEN_HEIGHT, ONLY_INVALID);
		}
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
	bool mainCharacterSpeedFound = false, scrollMarginFound = false, visionRangeFound = false;//, serverPortFound = false;
	
	for(unsigned int i=0; i<node.size(); i++) {
		if (! mainCharacterSpeedFound) {
			mainCharacterSpeedFound = managePositiveFloatCase(node[i],configuration.main_character_speed,"configuracion","","vel_personaje",DEFAULT_MAIN_CHARACTER_SPEED, ONLY_INVALID);
		}

		if (!visionRangeFound) {
			visionRangeFound = managePositiveIntCase(node[i], configuration.vision_range,"configuracion", "","vision_personaje",DEFAULT_VISION_RANGE, ONLY_INVALID);
		}
		//if (!serverPortFound){
		//	serverPortFound = managePositiveIntCase(node[i], configuration.port,"configuracion", "","puerto_servidor",DEFAULT_SERVER_PORT, ONLY_INVALID);
		//}
		if (!scrollMarginFound) {
			scrollMarginFound = managePositiveIntCase(node[i], configuration.scroll_margin,"configuracion", "","margen_scroll",DEFAULT_SCROLL_MARGIN, ONLY_INVALID);
		}
	}

	if (!mainCharacterSpeedFound) {
		Logger::instance().logFieldNotDefined("configuración", "vel_personaje", "");
		configuration.main_character_speed = DEFAULT_MAIN_CHARACTER_SPEED;
	}
	if (!scrollMarginFound) {
		Logger::instance().logFieldNotDefined("configuración", "margen_scroll", "");
		configuration.scroll_margin = DEFAULT_SCROLL_MARGIN;
	}

	if (!visionRangeFound) {
		Logger::instance().logFieldNotDefined("configuración", "vision_personaje", "");
		configuration.vision_range = DEFAULT_VISION_RANGE;
	}
	//if (!serverPortFound){
	//	Logger::instance().logFieldNotDefined("configuración", "puerto_servidor", "");
	//	configuration.port = DEFAULT_SERVER_PORT;
	//}

}

void operator >> (const Node& node, Connection& connection) {
	string field;
	bool serverPortFound = false, serverIpFound = false;
	
	for(unsigned int i = 0; i < node.size(); i++) {
		if (! serverPortFound) {
			serverPortFound = managePositiveIntCase(node[i], connection.port, "connection", "", "server_port", DEFAULT_SERVER_PORT, ONLY_INVALID);
		}
		if (!serverIpFound) {
			field = "server_ip";
			try {
				node[i][field] >> connection.ip;
				if (connection.ip == "~")
					connection.ip = "";
			} catch (KeyNotFound) {
				connection.ip = "";
			}
			if (connection.ip != "")
				serverIpFound = true;
			//serverIpFound = managePositiveIntCase(node[i], connection.ip, "connection", "","server_ip", DEFAULT_SERVER_IP, ONLY_INVALID);
		}
	}

	if (serverPortFound) {
		Logger::instance().logFieldNotDefined("connection", "server_port", "");
	}
	if (!serverIpFound) {
		Logger::instance().logFieldNotDefined("connection", "server_ip", "");
	}
}


bool validateImagePath(string imagePath) {
	if (DirList::isNotDirectory(imagePath)) //aca se valida si es directorio
	{ 
		if (imagePath.find(IMAGES_EXTENSION) == string::npos) { // Veo que sea '.png'.
			Logger::instance().log("Parser Error: '"+imagePath+"' does not have a valid extension.");
			return false;
		}

		if (DirList::canOpenFile(imagePath)){
			return true;
		}
		
		Logger::instance().log("Parser Error: Unable to open '"+imagePath+"'.");
		return false;
	}
	return false;
}

void operator >> (const Node& node, EntityObject* &entity) { // ENTIDADES CON NOMBRES IGUALES
	string name, imagePath, field;
	name = "";
	imagePath = "";
	field = "";
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
	managePositiveIntCase(node, baseWidth, name, "entity","ancho_base", DEFAULT_BASE_WIDTH, YES);
	managePositiveIntCase(node, baseHeight, name, "entity","alto_base", DEFAULT_BASE_HEIGHT, YES);
	managePositiveIntCase(node, pixelRefX, name, "entity","pixel_ref_x",DEFAULT_ENTITY_OBJECT_PIXEL_REF_X, YES);
	managePositiveIntCase(node, pixelRefY, name, "entity","pixel_ref_y",DEFAULT_ENTITY_OBJECT_PIXEL_REF_Y, YES);

	if (!imagePathFound) {
		pixelRefX = ERROR_IMAGE_PIXEL_REF_X;
		pixelRefY = ERROR_IMAGE_PIXEL_REF_Y;
		baseWidth = DEFAULT_BASE_WIDTH;
		baseHeight = DEFAULT_BASE_HEIGHT;
	}

	entity->name(name);
	entity->imagePath(imagePath);
	entity->baseWidth(baseWidth);
	entity->baseHeight(baseHeight);
	entity->pixelRefX(pixelRefX);
	entity->pixelRefY(pixelRefY);
}

void operator >> (const Node& node, AnimatedEntity* &animatedEntity) {
	int baseWidth, baseHeight, pixelRefX, pixelRefY, fps, delay;
	string imageDir = "", field ="";
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
	baseWidth = entity_aux->baseWidth();
	baseHeight = entity_aux->baseHeight();

	managePositiveIntCase(node, baseWidth, entity_aux->name(), "entity","ancho_base", DEFAULT_BASE_WIDTH, YES);
	managePositiveIntCase(node, baseHeight, entity_aux->name(), "entity","alto_base", DEFAULT_BASE_HEIGHT, YES);

	managePositiveIntCase(node, pixelRefX, entity_aux->name(), "entity","pixel_ref_x",DEFAULT_ANIMATED_ENTITY_PIXEL_REF_X, YES_IGNORE_LOG);
	managePositiveIntCase(node, pixelRefY, entity_aux->name(), "entity","pixel_ref_y",DEFAULT_ANIMATED_ENTITY_PIXEL_REF_Y, YES_IGNORE_LOG);
	managePositiveIntCase(node, fps, entity_aux->name(), "entity","fps",DEFAULT_FPS, YES);
	managePositiveIntCase(node, delay, entity_aux->name(), "entity","delay",DEFAULT_DELAY, YES);

	if (!imageDirFound) {
		pixelRefX = ERROR_ANIMATED_PIXEL_REF_X;
		pixelRefY = ERROR_ANIMATED_PIXEL_REF_Y;
		baseWidth = DEFAULT_BASE_WIDTH;
		baseHeight = DEFAULT_BASE_HEIGHT;
	}

	animatedEntity->name(entity_aux->name());
	animatedEntity->baseWidth(baseWidth);
	animatedEntity->baseHeight(baseHeight);
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

	if (!xFound) {
		entityDef.x = -1;
		Logger::instance().logFieldNotDefined(entityDef.entity, "x", "one of the entities");
	}
	if (!yFound) {
		entityDef.y = -1;
		Logger::instance().logFieldNotDefined(entityDef.entity, "y", "one of the entities");
	}
}

void operator >> (const Node& node, sMainCharacter& mainCharacter) {
	string field;

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
	managePositiveIntCase(node, mainCharacter.x, mainCharacter.entityType, "main character","x",DEFAULT_MAIN_CHARACTER_X, YES);
	managePositiveIntCase(node, mainCharacter.y, mainCharacter.entityType, "main character","y",DEFAULT_MAIN_CHARACTER_Y, YES);
	managePositiveFloatCase(node, mainCharacter.minPrecision, mainCharacter.entityType, "main character", "precisionMinima", DEFAULT_CHARACTER_MIN_PRECISION, YES);
	managePositiveFloatCase(node, mainCharacter.maxDamage, mainCharacter.entityType, "main character", "danoMaximo", DEFAULT_CHARACTER_MAX_DAMAGE, YES);
	managePositiveFloatCase(node, mainCharacter.maxLife, mainCharacter.entityType, "main character", "vidaMaxima", DEFAULT_CHARACTER_MAX_LIFE, YES);
	managePositiveFloatCase(node, mainCharacter.maxMagic, mainCharacter.entityType, "main character", "magiaMaxima", DEFAULT_CHARACTER_MAX_MAGIC, YES);
}

void operator >> (const Node& node, sItem& item) {
	string field;
	field = "tipo";
	try {
		node[field] >> item.type;
		if (item.type=="~")
			item.type = "";
	} catch (KeyNotFound) {
		item.type = "";
	}
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
	field = "caracteristicas";
	try {
		node[field] >> item.characteristics;
		if (item.characteristics=="~")
			item.characteristics = "";
	} catch (KeyNotFound) {
		item.characteristics = "";
	}
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
}

void operator >> (const Node& node, sItemsDef& itemsDef) {
	string field;
	managePositiveFloatCase(node,itemsDef.percentage,"items","","porcentaje",DEFAULT_ITEMS_PERCENTAGE, ONLY_INVALID);
	
	try {
		const Node& node_aux = node["def"];
		for(unsigned int i=0; i<node_aux.size(); i++) {
			sItem item;
			node_aux[i] >> item;
			if ( item.type.size() > 0 )
				itemsDef.vItems.push_back(item);
		}
	} catch (KeyNotFound) { }
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
}


void operator >> (const Node& node, sStage& stage) {
	string field;

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
	managePositiveIntCase(node, stage.size_x, stage.name, "stage","size_x",DEFAULT_STAGE_SIZE_X, YES);
	managePositiveIntCase(node, stage.size_y, stage.name, "stage","size_y",DEFAULT_STAGE_SIZE_Y, YES);


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
	try {
		const Node& node_aux = node["items"];
		node_aux >> stage.itemsDef;
	} catch (KeyNotFound) {	}
	catch (Exception& parserException ) {
		Logger::instance().logUnexpected(parserException.what());
	};
}

void operator >> (const Node& node, Stages& stages) {
	for(unsigned int i=0; i < node.size(); i++) {
		sStage stage;
		stage.name = "";
		node[i] >> stage;
		if (stage.name.size() > 0) // Si tiene nombre se guarda.
			stages.vStages_aux.push_back(stage);
		else {
			string str_i = stringUtilities::unsignedToString(i+1);
			//string str_i = static_cast<std::ostringstream*>(&(ostringstream() << i+1))->str();
			Logger::instance().logFieldNotDefined(str_i, "nombre", "stage number");
		}
	}
}

Config YAMLParser::generateDefaultConfiguration() {
	Config configuration;
	configuration.main_character_speed = DEFAULT_MAIN_CHARACTER_SPEED;
	configuration.scroll_margin = DEFAULT_SCROLL_MARGIN;
	//configuration.port = DEFAULT_SERVER_PORT;
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
	PersonajeModelo *mainCharacter = new PersonajeModelo();
	mainCharacter->setPosition(std::make_pair<int,int>(DEFAULT_MAIN_CHARACTER_X, DEFAULT_MAIN_CHARACTER_Y));
	mainCharacter->setDestino(DEFAULT_MAIN_CHARACTER_X, DEFAULT_MAIN_CHARACTER_Y);
	mainCharacter->setAnimation(entities.vAnimatedEntities[0]); // Uso la primera entidad porque ahí va estar el default en caso de no haber ninguna entidad.
	mainCharacter->setName("DEFAULT");
	mainCharacter->setDanoMaximo(DEFAULT_CHARACTER_MAX_DAMAGE);
	mainCharacter->setMagiaMaxima(DEFAULT_CHARACTER_MAX_MAGIC);
	mainCharacter->setPrecisionMinima(DEFAULT_CHARACTER_MIN_PRECISION);
	mainCharacter->setVidaMaxima(DEFAULT_CHARACTER_MAX_LIFE);
	return mainCharacter;
}

StageModel YAMLParser::generateDefaultStage() {
	vector <EntityDef> vEntitiesDef;
	vector <PersonajeModelo*> vMainCharacters;
	vMainCharacters.push_back(generateDefaultMainCharacter()); // Cargo el personaje default.

	StageModel stage("DEFAULT", vEntitiesDef, vMainCharacters, DEFAULT_ITEMS_PERCENTAGE);
	stage.setSize(DEFAULT_STAGE_SIZE_X, DEFAULT_STAGE_SIZE_Y);
	stage.generateMap();
	stage.loadByDefault(entities.vEntitiesObject[0]);

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
	loadItemsToMap(stage_index);
	sStage stage_aux = stages.vStages_aux[stage_index];
	StageModel stage(stage_aux.name, stage_aux.vEntitiesDef, stage_aux.vMainCharacters, stage_aux.itemsDef.percentage);
	if (stage_aux.itemsDef.vItems.size() > 0)
		stage.loadMapItems(stage_aux.itemsDef.vItems);
	stage.setSize( stage_aux.size_x, stage_aux.size_y);
	stage.generateMap();

	//comienza refactor
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
				if (entityObjectType){
					stage.insertEntity(key,entityObjectType);
				} else {
					if (animatedEntityType){
						stage.insertEntity(key,animatedEntityType);
					}
				}
			}
			else {
				Logger::instance().log("Parser Error: Entity '"+stage_aux.vEntitiesDef[i].entity+"''s base is out of map range.");
				stage_aux.vEntitiesDef.erase(stage_aux.vEntitiesDef.begin()+i);
				i--;
			}
		}
	}
	//fin refactor
	stage.loadByDefault(entities.vEntitiesObject[0]);
	stages.vStages.push_back(stage);
}

void YAMLParser::loadMainCharacters(int stage_index) {
	sStage stage_aux = stages.vStages_aux[stage_index];
	for(unsigned int j = 0; j < stage_aux.vMainCharacters_aux.size(); j++) {
		sMainCharacter mainCharacter_aux = stage_aux.vMainCharacters_aux[j];
		AnimatedEntity *animatedEntityType = findAnimatedEntityType(mainCharacter_aux.entityType);
		if (!animatedEntityType)
			Logger::instance().log("Parser Error: Entity type '"+mainCharacter_aux.entityType+"' for main character in stage '"+stage_aux.name+"' not found.");
		else {
			if (animatedEntityType->imagesPaths()->countDir() >= NUMBER_OF_IMAGE_DIRECTORIES_MAIN_CHARACTER) {
				PersonajeModelo* mainCharacter = new PersonajeModelo();
				mainCharacter->setPosition(std::make_pair<int,int>(mainCharacter_aux.x, mainCharacter_aux.y));
				mainCharacter->setDestino(mainCharacter_aux.x, mainCharacter_aux.y);
				mainCharacter->setAnimation(animatedEntityType);
				mainCharacter->setName(mainCharacter_aux.entityType);
				mainCharacter->setDanoMaximo(mainCharacter_aux.maxDamage);
				mainCharacter->setMagiaMaxima(mainCharacter_aux.maxMagic);
				mainCharacter->setPrecisionMinima(mainCharacter_aux.minPrecision);
				mainCharacter->setVidaMaxima(mainCharacter_aux.maxLife);
				stage_aux.vMainCharacters.push_back(mainCharacter);
			}
			else {
				string str_nro = stringUtilities::intToString(NUMBER_OF_IMAGE_DIRECTORIES_MAIN_CHARACTER);
				Logger::instance().log("Parser Error: Entity type '"+mainCharacter_aux.entityType+"' for main character in stage '"+stage_aux.name+"' does not have the "+str_nro+" image directories needed.");
			}
		}
	}
	if (stage_aux.vMainCharacters.size() <= 0) { // Verifico que para cada escenario exista al menos un protagonista.
		Logger::instance().logFieldNotDefined(stage_aux.name, "protagonista", "stage");
		
	}
	stage_aux.vMainCharacters.push_back(generateDefaultMainCharacter());
	stages.vStages_aux[stage_index] = stage_aux;
}

void YAMLParser::loadItemsToMap(int stage_index) {
	for(unsigned int i = 0; i < stages.vStages_aux[stage_index].itemsDef.vItems.size(); i++) {
		sItem item_aux = stages.vStages_aux[stage_index].itemsDef.vItems[i];
		EntityObject *entityObjectType = findEntityObjectType(item_aux.type);
		AnimatedEntity *animatedEntityType = findAnimatedEntityType(item_aux.type);
		if ((!entityObjectType) && (!animatedEntityType)){
			Logger::instance().log("Parser Error: Item's entity type '"+item_aux.type+"' defined in stage '"+stages.vStages_aux[stage_index].name+"' not found.");
			stages.vStages_aux[stage_index].itemsDef.vItems.erase(stages.vStages_aux[stage_index].itemsDef.vItems.begin()+i);
			i--;
		}
	}
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

void YAMLParser::parse(string directory, bool connecting) {
	bool yamlFilesFound = false,screenFound = false, stagesFound = false, entitiesFound = false, configurationFound = false;
	Node doc;
	DirList yamlFiles;
	yamlFiles.setExtensionRequired(CONFIGFILE_EXTENSION);
	if (yamlFiles.createFromDirectory(directory)) {
		if (yamlFiles.empty())
			Logger::instance().log("Parser Error: No '.yaml' files found.");
		else
			yamlFilesFound = true;
	}
	if (!connecting) {
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
				// tratamiento de archivos de cliente con datos de conexion
				//try {
				//	doc["connection"] >> connection;
				//	//si esta levantando un cliente, solo parseo datos de conexion
				//	return;
				//} catch (KeyNotFound) { }
				//catch (Exception& parserException ) {
				//	Logger::instance().logUnexpected(parserException.what());
				//};
				////si el codigo continua, no era un archivo de conexion.

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
			}; //try..catch
			game_config.cameraMarginScroll(configuration.scroll_margin);
			game_config.cameraWidth(screen.width);
			game_config.cameraHeight(screen.height);
			game_config.visionRange(configuration.vision_range);
			game_config.mainCharacterSpeed(configuration.main_character_speed);
		} //else
	} else { //if !conecting
		Logger::instance().log("Getting connection data.");
		string inputFilePath = yamlFiles.nextFullPath();
		ifstream inputFile(inputFilePath);
		Parser parser(inputFile);
		try {
			parser.GetNextDocument(doc);
			// tratamiento de archivos de cliente con datos de conexion
			try {
				doc["connection"] >> connection;
				game_config.serverPort(connection.port);
				game_config.serverIp(connection.ip);
			} catch (KeyNotFound) { }
			catch (Exception& parserException ) {
				Logger::instance().logUnexpected(parserException.what());
			};
		} catch (Exception& parserException) { // Error de sintaxis.
			Logger::instance().logSyntaxError(inputFilePath,parserException.what());
		}; //try..catch

	}
}

vector <StageModel> YAMLParser::vStages() {
	return stages.vStages;
}

//PersonajeModelo* YAMLParser::modelMainCharacters(unsigned stage, unsigned pers){
//	if ((stage >= stages.vStages.size()) || (stages.vStages[stage].modelMainCharacters(pers) == NULL)){
//		Logger::instance().nullPointer("function PersonajeModelo* YAMLParser::modelMainCharacters");
//		return NULL;
//	}
//	return stages.vStages[stage].modelMainCharacters(pers);
//}

Configuration YAMLParser::getConfig(){
	return game_config;
}


int YAMLParser::getConfigPort(){
	return game_config.serverPort();
}

std::string YAMLParser::getConfigIp(){
	return game_config.serverIp();
}

EntLists YAMLParser::allLists(){
	return entities;
}

