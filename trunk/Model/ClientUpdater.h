#ifndef _CLIENT_UPDATER_H_
#define _CLIENT_UPDATER_H_

#include "Connector.h"
#include "InstructionQueue.h"

class ClientUpdater {
private:
	std::string version;

	Connector connector;

	InstructionQueue instructionQueue;

	std::string& getVersion();

	Connector& getConnector();

	InstructionQueue& getInstructionQueue();

public:
	ClientUpdater();

	void updateClient();

	~ClientUpdater();
};

#endif // _CLIENT_UPDATER_H_