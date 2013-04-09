#include "Engine.h"
#include "Logger.h"
#include "Constants.h"
#include "Game.h"

//#include "YAMLParser.h"
//
//using namespace std;
//using namespace YAML;

using namespace common;

int main(int argc, char *argv[]) {

	//Logger::instance().setFile(LOGFILE); // Que el logger limpie el archivo existente.
	//YAMLParser yParser;
	//yParser.parse("test.yaml");
	//system("PAUSE");
	//return 0;

	Logger::instance().setFile(LOGFILE);
	Logger::instance().log("Iniciando el juego..");
    Engine engine;
	Game::instance().initialize();
	
 
	return engine.execute();
}