#ifndef _MODEL_UPDATER_H_
#define _MODEL_UPDATER_H_

#include "Thread.h"
#include "Connector.h"
#include "InstructionQueue.h"

class ModelUpdater : public Thread {
private:
	bool connected;

	bool errors;

	bool serverReached;

	unsigned int activatedAt;

	bool forceStop;

	Connector connector;

	InstructionQueue instructionQueue;

	void setConnected(bool connected);

	void setError(bool error);
	
	void setServerReached(bool serverReached);

	void setActivatedAt(unsigned int activatedAt);

	bool isForceStop();

	void setForceStop(bool forceStop);

	Connector& getConnector();

	InstructionQueue& getInstructionQueue();

	void updateModel();

	void processInstruction(Instruction& instructionIn);

	void* run();

	void simulationUpdate(Instruction& instructionIn);

	void simulate(std::string simulation_package);

	void syncAllPlayer(Instruction& instructionIn);

	void syncPlayer(std::string onePlayer);

public:
	ModelUpdater();

	bool isConnected();

	bool thereAreErrors();

	bool hasServerBeenReached();

	unsigned int getActivatedAt();

	void addInstruction(Instruction instruction);

	void startUpdating();

	void stopUpdating(bool forceStop);

	~ModelUpdater();
};

#endif // _CHAT_UPDATER_H_