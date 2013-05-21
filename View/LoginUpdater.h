#ifndef _LOGIN_UPDATER_H_
#define _LOGIN_UPDATER_H_

#include <list>

#include "Thread.h"
#include "Connector.h"
#include "InstructionQueue.h"

class LoginUpdater : public Thread {
private:
	bool loggedIn;

	bool forceStop;

	Connector connector;

	InstructionQueue instructionQueue;

	Mutex& messagesListMutex;

	std::list<std::string>& messagesList;

	void setLoggedIn(bool loggedIn);

	bool isForceStop();

	void setForceStop(bool forceStop);

	Connector& getConnector();

	InstructionQueue& getInstructionQueue();

	Mutex& getMessagesListMutex();

	std::list<std::string>& getMessagesList();

	void updateLoginModel();

	void processInstruction(Instruction& instructionIn);

	void* run();

public:
	LoginUpdater(Mutex& messagesListMutex, std::list<std::string>& messagesList);

	bool isLoggedIn();

	void addInstruction(Instruction instruction);

	void startUpdating();

	void stopUpdating(bool forceStop);

	bool initialize();

	~LoginUpdater();
};

#endif // _LOGIN_UPDATER_H_