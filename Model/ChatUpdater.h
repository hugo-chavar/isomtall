#ifndef _CHAT_UPDATER_H_
#define _CHAT_UPDATER_H_

#pragma warning(disable: 4512)

#include <list>

#include "Thread.h"
#include "Connector.h"
#include "InstructionQueue.h"

class ChatUpdater : public Thread {
private:
	bool connected;

	bool forceStop;

	Connector connector;

	InstructionQueue instructionQueue;

	Mutex& messagesListMutex;

	std::list<std::string>& messagesList;

	void setConnected(bool connected);

	bool isForceStop();

	void setForceStop(bool forceStop);

	Connector& getConnector();

	InstructionQueue& getInstructionQueue();

	Mutex& getMessagesListMutex();

	std::list<std::string>& getMessagesList();

	void updateChatModel();

	void processInstruction(Instruction& instructionIn);

	void* run();

public:
	ChatUpdater(Mutex& messagesListMutex, std::list<std::string>& messagesList);

	bool isConnected();

	void addInstruction(Instruction instruction);

	void startUpdating();

	void stopUpdating(bool forceStop);

	~ChatUpdater();
};

#endif // _CHAT_UPDATER_H_