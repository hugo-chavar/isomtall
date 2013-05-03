#include "Engine.h"
#include "Logger.h"
#include "Constants.h"
#include "Game.h"

using namespace common;

int main(int argc, char *argv[]) {

	string nombreJugador="Andres";
	Logger::instance().setFile(LOGFILE);
	Logger::instance().log("Iniciando el juego..");
    Engine engine;
	if (!Game::instance().initialize())
		return 1;
 
	return engine.execute();
}