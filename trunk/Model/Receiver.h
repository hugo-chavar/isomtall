#ifndef _RECEIVER_H_
#define _RECEIVER_H_

#include "Thread.h"
#include "Socket.h"
#include "InstructionQueue.h"

class Receiver : public Thread {
private:
	Socket* socket;

	std::string userID;

	bool connectionOK;

	bool inyectUserIDonReceive;

	std::string reminder;

	InstructionQueue* instructionQueue;

	void setConnectionOK(bool connectionOK);

	bool isInyectUserIDonReceive();

	std::string getReminder();

	void setReminder(std::string reminder);

	InstructionQueue* getInstructionQueue();

	void receive();

	std::string receiveMessageFromSocket();

	void* run();

public:
	Receiver(Socket* socket, InstructionQueue* instructionQueue, std::string userID, bool inyectUserIDonReceive);

	Socket* getSocket();

	void setSocket(Socket* socket);

	std::string getUserID();

	void setUserID(std::string userID);

	bool isConnectionOK();

	void setInstructionQueue(InstructionQueue* instructionQueue);

	void startReceiving();

	void stopReceiving();

	~Receiver();
};

#endif // _RECEIVER_H_
