#include "Engine.h"
#include "Logger.h"
#include "Constants.h"
#include "Game.h"

using namespace common;

int main(int argc, char *argv[]) {

//	string nombreJugador="1";
	Logger::instance().setFile(LOGFILE);
	Logger::instance().log("Iniciando el juego..");
    Engine engine;
//	if (!Game::instance().initialize(nombreJugador))
//		return 1;
 
	return engine.execute();
}