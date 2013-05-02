#ifndef _SENDER_H_
#define _SENDER_H_

#include "Thread.h"
#include "Socket.h"
#include "InstructionQueue.h"

class Sender : public Thread {
private:
	bool keepSending;

	bool forceShutdown;

	Socket* socket;

	InstructionQueue instructionQueue;

	void setKeepSending(bool keepSending);

	bool getKeepSending() const;

	bool getForceShutdown();

	void setForceShutdown(bool forceShutdown);

	Socket* getSocket() const;

	InstructionQueue& getInstructionQueue();

	void send();

	void sendMessage(std::string message);

	void* run();

public:
	Sender(Socket* socket);

	void startSending();

	void addInstruction(Instruction& instruction);

	void stopSending(bool forceShutdown);

	~Sender();
};

#endif // _SENDER_H_