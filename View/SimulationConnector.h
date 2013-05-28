#pragma once

#include <string>

#include "Socket.h"
#include "Sender.h"
#include "SimulationReceiver.h"

class SimulationConnector {
private:
	Sender sender;

	SimulationReceiver receiver;

	Sender& getSender();

	SimulationReceiver& getReceiver();

public:
	SimulationConnector(Socket* socket, InstructionQueue* instructionQueue, std::string userID = "", bool inyectUserIDonReceive =  false);

	Socket* getSocket();

	void setSocket(Socket* socket);

	void setBroadcastConditionVariable(ConditionVariable* broadcastConditionVariable);

	bool isConnectionOK();

	std::string getUserID();

	void setUserID(std::string userID);

	void setInstructionQueue(InstructionQueue* instructionQueue);

	void addInstruction(Instruction& instruction);

	void addBroadcast(Instruction& instruction);

	void startConnector();

	void stopConnector(bool forced);

	~SimulationConnector();
};