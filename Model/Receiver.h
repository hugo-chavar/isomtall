#ifndef _RECEIVER_H_
#define _RECEIVER_H_

#include <list>
#include <string>

#include "Thread.h"
#include "Socket.h"
#include "Mutex.h"

class Receiver : public Thread {
private:
	bool keepReceiving;

	Socket* socket;

	Mutex& messagesListMutex;

	std::list<std::string>& messagesList;

	bool& loggedIn;

	bool isLoggedIn();

	void setLoggedIn(bool loggedIn);

	void setKeepReceiving(bool keepReceiving);

	bool getKeepReceiving() const;

	Socket* getSocket() const;

	Mutex& getMessagesListMutex();

	std::list<std::string>& getMessagesList();

	void receive();

	std::string receiveMessage();

	void* run();

public:
	Receiver(Socket* socket, Mutex& messagesListMutex, std::list<std::string>& messagesList, bool& loggedIn);

	void startReceiving();

	void stopReceiving();

	~Receiver();
};

#endif // _RECEIVER_H_
