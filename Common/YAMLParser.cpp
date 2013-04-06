#include "YAMLParser.h"

using namespace std;
using namespace YAML;
using namespace common;



YAMLParser::YAMLParser() {
}

YAMLParser::~YAMLParser() {
}

void operator >> (const Node& node, Screen& screen) {
	bool widthFound = false, heightFound = false;
	for(unsigned int i=0; i<node.size(); i++) {
		try {
			node[i]["ancho"] >> screen.width; // VER COMO RECIBIR NUMEROS NEGATIVOS
			widthFound = true;
		} catch (KeyNotFound) {	} catch (InvalidScalar) { };
		try {
			node[i]["alto"] >> screen.height; // VER COMO RECIBIR NUMEROS NEGATIVOS
			heightFound = true;
		} catch (KeyNotFound) {	} catch (InvalidScalar) { };
	}
	if (!widthFound) {
		Logger::instance().log("Parser Error: Field 'ancho' is not defined in 'pantalla'.");
		// DEFINIR DEFAULT
	}
	if (!heightFound) {
		Logger::instance().log("Parser Error: Field 'alto' is not defined in 'pantalla'.");
		// DEFINIR DEFAULT
	}
}

void operator >> (const Node& node, Configuracion& configuracion) {
	bool vel_personajeFound = false, margen_scrollFound = false;
	for(unsigned int i=0; i<node.size(); i++) {
		try {
			node[i]["vel_personaje"] >> configuracion.vel_personaje; // VER COMO RECIBIR NUMEROS NEGATIVOS
			vel_personajeFound = true;
		} catch (KeyNotFound) {	} catch (InvalidScalar) { };
		try {
			node[i]["margen_scroll"] >> configuracion.margen_scroll; // VER COMO RECIBIR NUMEROS NEGATIVOS
			margen_scrollFound = true;
		} catch (KeyNotFound) {	} catch (InvalidScalar) { };
	}
	if (!vel_personajeFound) {
		Logger::instance().log("Parser Error: Field 'vel_personaje' is not defined in 'configuracion'.");
		// DEFINIR DEFAULT
	}
	if (!margen_scrollFound) {
		Logger::instance().log("Parser Error: Field 'margen_scroll' is not defined in 'configuracion'.");
		// DEFINIR DEFAULT
	}
}

void operator >> (const Node& node, EntityObject& entity) { // DEFINIR CONSTANTES
	string name, imagePath;
	int baseWidth, baseHeight, pixelRefX, pixelRefY;
	try {
		node["nombre"] >> name;
		if (name=="~")
			name = "";
	} catch (KeyNotFound) {
		name = "";
	};
	try { // CHEQUEAR QUE EXISTA LA IMAGEN
		node["imagen"] >> imagePath;
		if (imagePath=="~")
			imagePath = "default";
	} catch (KeyNotFound) {
		Logger::instance().log("Parser Error: Field 'imagen' is not defined in entity '"+name+"'.");
		imagePath = "default";
	};
	try {
		node["ancho_base"] >> baseWidth;
	} catch (KeyNotFound) {
		Logger::instance().log("Parser Error: Field 'ancho_base' is not defined in entity '"+name+"'.");
		baseWidth = 1;
	};
	try {
		node["alto_base"] >> baseHeight;
	} catch (KeyNotFound) {
		Logger::instance().log("Parser Error: Field 'alto_base' is not defined in entity '"+name+"'.");
		baseHeight = 1;
	};
	try {
		node["pixel_ref_x"] >> pixelRefX;
	} catch (KeyNotFound) {
		Logger::instance().log("Parser Error: Field 'pixel_ref_x' is not defined in entity '"+name+"'.");
		pixelRefX = 0;
	};
	try {
		node["pixel_ref_y"] >> pixelRefY;
	} catch (KeyNotFound) {
		Logger::instance().log("Parser Error: Field 'pixel_ref_y' is not defined in entity '"+name+"'.");
		pixelRefY = 0;
	};
	EntityObject entity_aux(name, imagePath, baseWidth, baseHeight, pixelRefX, pixelRefY);
	entity = entity_aux;
}

void operator >> (const Node& node, AnimatedEntity& animatedEntity) { // DEFINIR CONSTANTES
	int fps, delay;
	EntityObject entity_aux;
	node >> entity_aux;
	try {
	node["fps"] >> fps;
	} catch (KeyNotFound) {
		Logger::instance().log("Parser Error: Field 'fps' is not defined in entity '"+entity_aux.name()+"'.");
		fps = 0;
	};
	try {
		node["delay"] >> delay;
	} catch (KeyNotFound) {
		Logger::instance().log("Parser Error: Field 'delay' is not defined in entity '"+entity_aux.name()+"'.");
		delay = 0;
	};
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
		} catch (KeyNotFound) {	};
		try {
			node[i]["delay"] >> delay;
			isAnimated = true;
		} catch (KeyNotFound) {	};

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

void operator >> (const Node& node, EntidadDef& entidadDef) {
	try {
		node["entidad"] >> entidadDef.entidad;
		if (entidadDef.entidad=="~")
			entidadDef.entidad = "";
	} catch (KeyNotFound) {
		entidadDef.entidad = "";
	};
	try {
		node["x"] >> entidadDef.x; // VER COMO RECIBIR NUMEROS NEGATIVOS
	} catch (KeyNotFound) {
		Logger::instance().log("Parser Error: Field 'x' is not defined in one of the entities '"+entidadDef.entidad+"'.");
	};
	try {
		node["y"] >> entidadDef.y; // VER COMO RECIBIR NUMEROS NEGATIVOS
	} catch (KeyNotFound) {
		Logger::instance().log("Parser Error: Field 'y' is not defined in one of the entities '"+entidadDef.entidad+"'.");
	};
}

void operator >> (const Node& node, sMainCharacter& mainCharacter) {
	try {
		node["tipoEntidad"] >> mainCharacter.entityType;
		if (mainCharacter.entityType=="~")
			mainCharacter.entityType = "";
	} catch (KeyNotFound) {
		mainCharacter.entityType = "";
	};
	try {
		node["x"] >> mainCharacter.x; // VER COMO RECIBIR NUMEROS NEGATIVOS
	} catch (KeyNotFound) {
		Logger::instance().log("Parser Error: Field 'x' is not defined in main character '"+mainCharacter.entityType+"'.");
		mainCharacter.x = 0; // DEFINIR DEFAULT
	};
	try {
		node["y"] >> mainCharacter.y; // VER COMO RECIBIR NUMEROS NEGATIVOS
	} catch (KeyNotFound) {
		Logger::instance().log("Parser Error: Field 'y' is not defined in main character '"+mainCharacter.entityType+"'.");
		mainCharacter.y = 0; // DEFINIR DEFAULT
	};
}

void operator >> (const Node& node, Escenario& escenario) {
	try {
		node["nombre"] >> escenario.nombre;
		if (escenario.nombre=="~")
			escenario.nombre = "";
	} catch (KeyNotFound) {
		escenario.nombre = "";
	};
	try {
		node["size_x"] >> escenario.size_x; // VER COMO RECIBIR NUMEROS NEGATIVOS
	} catch (KeyNotFound) {
		Logger::instance().log("Parser Error: Field 'size_x' is not defined in stage '"+escenario.nombre+"'.");
		// DEFINIR DEFAULT
	};
	try {
		node["size_y"] >> escenario.size_y; // VER COMO RECIBIR NUMEROS NEGATIVOS
	} catch (KeyNotFound) {
		Logger::instance().log("Parser Error: Field 'size_y' is not defined in stage '"+escenario.nombre+"'.");
		// DEFINIR DEFAULT
	};
	try {
		const Node& node_aux = node["entidadesDef"];
		for(unsigned int i=0; i<node_aux.size(); i++) {
			EntidadDef entidadDef;
			node_aux[i] >> entidadDef;
			if (entidadDef.entidad.size()>0) // Si tiene nombre de entidad se guarda.
				escenario.vEntidadesDef.push_back(entidadDef);
		}
	} catch (KeyNotFound) { };
	try {
		const Node& node_aux = node["protagonista"];
		for(unsigned int i=0; i<node_aux.size(); i++) {
			sMainCharacter mainCharacter;
			node_aux[i] >> mainCharacter;
			if (mainCharacter.entityType.size()>0) // Si tiene tipo de entidad se guarda.
				escenario.vMainCharacters_aux.push_back(mainCharacter);
		}
	} catch (KeyNotFound) {	};
	// COMPLETAR MAPA CON DEFAULT (CHEQUEAR SI LAS QUE TIENE SON ESTATICAS?) Y LOGGEAR ERROR
}

void operator >> (const Node& node, Escenarios& escenarios) {
	for(unsigned int i=0; i<node.size(); i++) {
		Escenario escenario;
		node[i] >> escenario;
		if (escenario.nombre.size()>0) // Si tiene nombre se guarda.
			escenarios.vEscenarios.push_back(escenario);
		else {
			string str_i = static_cast<std::ostringstream*>(&(ostringstream() << i+1))->str();
			Logger::instance().log("Parser Error: Field 'nombre' is not defined in stage number "+str_i+".");
		}
	}
}

Screen YAMLParser::generateDefaultScreen() {
	Screen screen;
	screen.width = 500; // DEFAULT Y EL DE ABAJO TAMBIEN
	screen.height = 600;
	return screen;
}

MainCharacter YAMLParser::generateDefaultMainCharacter() { // DEFINIR DEFAULT POSICION INICIAL
	MainCharacter mainCharacter(&entities.vAnimatedEntities[0], 0, 0); // Uso la primera entidad porque ahí va estar el default en caso de no haber ninguna entidad.
	return mainCharacter;
}

Escenario YAMLParser::generateDefaultStage() { // DEFINIR DEFAULT NOMBRE Y SIZES
	Escenario escenario;
	escenario.vMainCharacters.push_back(generateDefaultMainCharacter());
	return escenario;
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

void YAMLParser::manageEntityCase() {
	if (entities.vAnimatedEntities.size()<=0) { // Verifico que exista al menos una entidad animada.	
		Logger::instance().log("Parser Error: No animated entities found.");
		AnimatedEntity animatedEntity;
		entities.vAnimatedEntities.push_back(animatedEntity);
	}
	if (entities.vEntitiesObject.size()<=0) { // Verifico que exista al menos una entidad no animada.	
		Logger::instance().log("Parser Error: No non-animated entities found.");
		EntityObject entity;
		entities.vEntitiesObject.push_back(entity);
	}
}

void YAMLParser::manageStageCase() {
	for(unsigned int i=0; i<escenarios.vEscenarios.size(); i++) { // Cargo los objetos del vector de personajes y verifico que para cada escenario exista al menos un protagonista.
		for(unsigned int j=0; j<escenarios.vEscenarios[i].vMainCharacters_aux.size(); j++) {
			sMainCharacter mainCharacter_aux = escenarios.vEscenarios[i].vMainCharacters_aux[j];
			AnimatedEntity *animatedEntityType = findAnimatedEntityType(mainCharacter_aux.entityType);
			if (!animatedEntityType)
				Logger::instance().log("Parser Error: Entity type '"+mainCharacter_aux.entityType+"' for main character in stage '"+escenarios.vEscenarios[i].nombre+"' not found.");
			else {
				MainCharacter mainCharacter(animatedEntityType, mainCharacter_aux.x, mainCharacter_aux.y);
				escenarios.vEscenarios[i].vMainCharacters.push_back(mainCharacter);
			}
		}
		if (escenarios.vEscenarios[i].vMainCharacters.size()<=0) {
			Logger::instance().log("Parser Error: Field 'protagonista' is not defined in stage '"+escenarios.vEscenarios[i].nombre+"'.");
			escenarios.vEscenarios[i].vMainCharacters.push_back(generateDefaultMainCharacter());
		}
	}
	if (escenarios.vEscenarios.size()<=0) { // Verifico que exista al menos un escenario.
		Logger::instance().log("Parser Error: No stages found.");
		escenarios.vEscenarios.push_back(generateDefaultStage());
	}
}

void YAMLParser::parse(string inputFilePath) {
	Node doc;
	bool screenFound = false, stageFound = false;
	ifstream inputFile(inputFilePath);
	// Verificar si existe el archivo y si está vacío
	Parser parser(inputFile);
	Logger::instance().setFile("ParserError.log"); // Que el logger limpie el archivo existente.
	try {
		parser.GetNextDocument(doc);
		try {
			doc["pantalla"] >> screen;
			screenFound = true;
		} catch (KeyNotFound) { };
		try {
			doc["configuracion"] >> configuracion; // CARGAR DEFAULT
		} catch (KeyNotFound) { };
		try {
			doc["entidades"] >> entities; // CARGAR DEFAULT
			manageEntityCase();
		} catch (KeyNotFound) { };
		try {
			doc["escenarios"] >> escenarios;
			manageStageCase();
			stageFound = true;
		} catch (KeyNotFound) { };
		
		if (!screenFound) {
			Logger::instance().log("Parser Error: Field 'pantalla' is not defined.");
			screen = generateDefaultScreen();
		}
		if (!stageFound) {
			Logger::instance().log("Parser Error: Field 'escenarios' is not defined.");
			escenarios.vEscenarios.push_back(generateDefaultStage());
		}
	} catch (Exception& parserException) { // SI ES UN ERROR DE SINTAXIS TERMINAR EL PROGRAMA O CARGAR TODO DEFAULT Y LOGGEAR EL ERROR?
		Logger::instance().log(parserException.what());
		cout << parserException.what() << endl;
	};


	// TESTEO RAPIDO
	cout << "Pantalla:\n   Ancho: " << screen.width << " Alto: " << screen.height << endl;
	cout << "Configuracion:\n   Vel_Personaje: " << configuracion.vel_personaje << " Margen_Scroll: " << configuracion.margen_scroll << endl;
	cout << "Entidades:" << endl;
	for(unsigned int i=0; i<entities.vEntitiesObject.size(); i++) {
		cout << "   Nombre: " << entities.vEntitiesObject[i].name() << " Imagen: " << entities.vEntitiesObject[i].imagePath() << endl;
	}
	for(unsigned int i=0; i<entities.vAnimatedEntities.size(); i++) {
		cout << "   Nombre: " << entities.vAnimatedEntities[i].name() << " Imagen: " << entities.vAnimatedEntities[i].imagePath() <<
			" Fps: " << entities.vAnimatedEntities[i].fps() << endl;
	}
	cout << "Escenarios:" << endl;
	for(unsigned int i=0; i<escenarios.vEscenarios.size(); i++) {
		Escenario escenario = escenarios.vEscenarios[i];
		cout << "   Nombre: " << escenario.nombre << " Size_X: " << escenario.size_x << " Size_Y: " << escenario.size_y << endl;
		cout << "   Entidades:" << endl;
		for(unsigned int j=0; j<escenario.vEntidadesDef.size(); j++) {
			EntidadDef entidadDef = escenario.vEntidadesDef[j];
			cout << "      Entidad: " << entidadDef.entidad << " X: " << entidadDef.x << " Y: " << entidadDef.y << endl;
		}
		cout << "   Protagonistas:" << endl;
		for(unsigned int j=0; j<escenario.vMainCharacters.size(); j++) {
			MainCharacter mainCharacter = escenario.vMainCharacters[j];
			cout << "      TipoEntidad: " << (*mainCharacter.entityType()).name() << " X: " << mainCharacter.x() << " Y: " << mainCharacter.y() << endl;
		}
	}
}