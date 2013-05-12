#include "Engine.h"
#include "Logger.h"
#include "Constants.h"
#include "Game.h"
#include "ClientUpdater.h"

using namespace common;

int main(int argc, char *argv[]) {

//	string nombreJugador="1";
	//WSAData ws;
	//WSAStartup(MAKEWORD(2,2),&ws);
	ClientUpdater clientUpdater;
	clientUpdater.updateClient();
	//debe ir arriba, lo pongo aca para dejar el repo funcionando. Hay un problema por ahora con el envio de archivos
	WSAData ws;
	WSAStartup(MAKEWORD(2,2),&ws);
	Logger::instance().setFile(LOGFILE);
	Logger::instance().log("Iniciando el juego..");
    Engine engine;
//	if (!Game::instance().initialize(nombreJugador))
//		return 1;
 
	return engine.execute();
}