#ifndef _SENDER_H_
#define _SENDER_H_

#include "Thread.h"
#include "Socket.h"
#include "InstructionQueue.h"

class Sender : public Thread {
private:
	Socket* socket;

	bool forceStop;

	InstructionQueue instructionQueue;

	ConditionVariable* broadcastConditionVariable;

	bool isForceStop();

	void setForceStop(bool forceStop);

	InstructionQueue& getInstructionQueue();

	ConditionVariable* getBroadcastConditionVariable();

	void send();

	void sendMessage(std::string message);

	void* run();

public:
	Sender(Socket* socket);

	Socket* getSocket();

	void setSocket(Socket* socket);

	void setBroadcastConditionVariable(ConditionVariable* broadcastConditionVariable);

	void startSending();

	void addInstruction(Instruction& instruction);

	void addBroadcast(Instruction& instruction);

	void stopSending(bool forceStop);

	~Sender();
};

#endif // _SENDER_H_