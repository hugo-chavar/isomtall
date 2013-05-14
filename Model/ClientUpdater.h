#ifndef _CLIENT_UPDATER_H_
#define _CLIENT_UPDATER_H_

#include "Connector.h"
#include "InstructionQueue.h"
#include "stringUtilities.h"

#define TAMBUFFER 10240

class ClientUpdater {
private:
	std::string version;

	Connector connector;

	InstructionQueue instructionQueue;

	std::string& getVersion();

	Connector& getConnector();

	InstructionQueue& getInstructionQueue();

	void crearDirectorios(std::string directorios,std::string path);

	void ClientUpdater::receiveFile(std::ofstream* archivo,Instruction instructionIn);

	void sendConfirmation();

public:
	ClientUpdater();

	void updateClient();

	~ClientUpdater();
};

#endif // _CLIENT_UPDATER_H_