#pragma once

#include "Receiver.h"

class SimulationReceiver : public Receiver {

private:

	std::string receiveMessageFromSocket();

public:

	~SimulationReceiver();

	SimulationReceiver(Socket* socket, InstructionQueue* instructionQueue, std::string userID, bool inyectUserIDonReceive);
};