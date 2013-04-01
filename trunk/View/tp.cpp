#include "Engine.h"
#include "Logger.h"
#include "Constants.h"

using namespace common;

int main(int argc, char *argv[]) {
	Logger::instance().setFile("hola.log");
	Logger::instance().log("Hola mundo");
    Engine engine;

	//engine.initialize();
 
	return engine.execute();
}