#include "Engine.h"
#include "Logger.h"
#include "Constants.h"
#include "Game.h"
#include "ClientUpdater.h"

using namespace common;

int main(int argc, char *argv[]) {
	std::string playerName;
	if (argc < 2){
		std::cout << "Nombre jugador no ingresado"<<std::endl;
		playerName = "Default Name";
	} else {
		//porner if playername largo
		playerName = argv[1];
	}
	int serverPort = 9443; // obtener desde otro archivo de config
	std::string serverIp = "127.0.0.1"; // obtener desde otro archivo de config
	WSAData ws;
	WSAStartup(MAKEWORD(2,2),&ws);
	ClientUpdater clientUpdater;
	clientUpdater.setServerIp(serverIp);
	clientUpdater.setServerPort(serverPort);
	//clientUpdater.updateClient();
	Logger::instance().setFile(LOGFILE);
	Logger::instance().log("Iniciando el juego..");
	Game::instance().setPlayerName(playerName);
    Engine engine;
//	if (!Game::instance().initialize(nombreJugador))
//		return 1;
 
	return engine.execute();
}