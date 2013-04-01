#include "Engine.h"
#include "Logger.h"
#include "Constants.h"

using namespace common;

int main(int argc, char *argv[]) {
	Logger::instance().setFile(LOGFILE);
	Logger::instance().log("Iniciando el juego..");
    Engine engine;
 
	return engine.execute();
}