#ifndef _MODEL_UPDATER_H_
#define _MODEL_UPDATER_H_

#include "Thread.h"
#include "SimulationConnector.h"
#include "InstructionQueue.h"
#include <vector>

class ModelUpdater : public Thread {
private:
	bool connected;

	bool errors;

	bool serverReached;

	unsigned int activatedAt;

	unsigned int startedAt;

	unsigned int diffDelay;

	unsigned int lastServerDelay;

	unsigned int latency;

	int clientServerDeltaTime;

	bool forceStop;

	SimulationConnector connector;

	InstructionQueue instructionQueue;

	std::vector<std::pair<unsigned, int> > transmissionTimes;

	void setConnected(bool connected);
	
	void setServerReached(bool serverReached);

	void setActivatedAt(unsigned int activatedAt);

	void setStartedAt(unsigned int startedAt);

	bool isForceStop();

	void setForceStop(bool forceStop);

	SimulationConnector& getConnector();

	InstructionQueue& getInstructionQueue();

	void updateModel();

	void processInstruction(Instruction& instructionIn);

	void* run();

	void simulationUpdate(Instruction& instructionIn);

	void simulate(std::string simulation_package);

	void syncAllPlayer(Instruction& instructionIn);

	void syncPlayer(std::string onePlayer);

	void requestSynchronizeClock();

	void synchronizeClock(Instruction& instructionIn);

	void requestSynchronize();

public:
	ModelUpdater();

	bool isConnected();

	//bool thereAreErrors();

	bool hasServerBeenReached();

	unsigned int getActivatedAt();

	void addInstruction(Instruction instruction);

	void startUpdating();

	void stopUpdating(bool forceStop);

	unsigned calculateRTT(unsigned lastRTT);

	void setDiffDelay(unsigned diff);

	unsigned getDiffDelay();

	~ModelUpdater();
};

#endif // _CHAT_UPDATER_H_