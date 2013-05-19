#include "Engine.h"
#include "Logger.h"
#include "Constants.h"
#include "GameView.h"
//#include "ClientUpdater.h"

using namespace common;

int main(int argc, char *argv[]) {
	std::string playerName;
	std::string playerCharacterId;
	if (argc < 2){
		std::cout << "Nombre jugador no ingresado"<<std::endl;
		playerName = "Default Name";
	} else {
		//poner if playername largo
		playerName = argv[1];
	}
	if (argc < 3){
		std::cout << "Personaje no elegido"<<std::endl;
		playerCharacterId = "0";
	} else {
		playerCharacterId = argv[2];
	}

	WSAData ws;
	WSAStartup(MAKEWORD(2,2),&ws);

	Logger::instance().setFile(LOGFILE);
	Logger::instance().log("Iniciando el juego..");
	GameView::instance().setPlayerName(playerName);
	GameView::instance().setPlayerCharacterId(playerCharacterId);
    Engine engine;
//	if (!Game::instance().initialize(nombreJugador))
//		return 1;
 
	return engine.execute();
}