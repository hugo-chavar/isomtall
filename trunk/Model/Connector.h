#ifndef _CONECTOR_H_
#define _CONECTOR_H_

#include <string>

#include "Socket.h"
#include "Sender.h"
#include "Receiver.h"

class Connector {
private:
	Sender sender;

	Receiver receiver;

	Sender& getSender();

	Receiver& getReceiver();

public:
	Connector(Socket* socket, InstructionQueue* instructionQueue, std::string userID = "", bool inyectUserIDonReceive =  false);

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

	~Connector();
};

#endif // _CONECTOR_H_