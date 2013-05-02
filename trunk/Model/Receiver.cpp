#include "Receiver.h"

#include <iostream>

#include "StringUtilities.h"
#include "Instruction.h"

Receiver::Receiver(Socket* socket, Mutex& messagesListMutex, std::list<std::string>& messagesList, bool& loggedIn) : messagesListMutex(messagesListMutex), messagesList(messagesList), loggedIn(loggedIn) {
	this->socket = socket;
	this->keepReceiving = true;
}

void Receiver::startReceiving(){
	this->start();
}

void Receiver::setKeepReceiving(bool keepReceiving){
	this->keepReceiving = keepReceiving;
}

bool Receiver::getKeepReceiving() const{
	return this->keepReceiving;
}

Socket* Receiver::getSocket() const{
	return this->socket;
}

Mutex& Receiver::getMessagesListMutex() {
	return this->messagesListMutex;
}

std::list<std::string>& Receiver::getMessagesList() {
	return this->messagesList;
}

bool Receiver::isLoggedIn() {
	return this->loggedIn;
}

void Receiver::setLoggedIn(bool loggedIn) {
	this->loggedIn = loggedIn;
}

void Receiver::receive() {
	std::string request = "";
	std::string message = "";
	Instruction instruction;

	request = this->receiveMessage();
	while (this->getKeepReceiving()) {
		instruction.clear();

		if (request != "") {
			request = request.substr(9,(request.find("</message>") - 9));
			instruction.deserialize(request);
		} else {
			message = "CONNECTION ERROR - SERVER UNREACHABLE";
			this->keepReceiving = false;
		}

		if (!isLoggedIn()) {
			switch (instruction.getOpCode()) {
				case OPCODE_LOGIN_OK: {
					message = "LOGIN SUCCESSFULL - Server greeting: " + instruction.getArgument("greeting");
					this->setLoggedIn(true);
					break;
				}
				case OPCODE_USERID_ALREADY_USED: {
					message = "USERNAME ALREADY IN USE. TRY AGAIN";
					break;
				}
			}
		} else {
			switch (instruction.getOpCode()) {
				case OPCODE_CHAT_MESSAGE: {
					message = instruction.getArgument("from") + ": " + instruction.getArgument("message");
					break;
				}
			}
		}

		this->getMessagesListMutex().lock();
		this->getMessagesList().push_back(message);
		if (this->getMessagesList().size() > 10)
			this->getMessagesList().pop_front();
		this->getMessagesListMutex().unlock();

		request = this->receiveMessage();
	}
}

std::string Receiver::receiveMessage() {
	bool validRead = true;
	char buffer[512] = "";
	int bytesReceived = 0;
	std::string aux = "";
	std::string message = "";

	do {
		bytesReceived = this->getSocket()->receiveData(buffer,512);

		if (bytesReceived <= 0) {
			validRead = false;
			if (bytesReceived == 0)
				this->setKeepReceiving(false);
			std::cout << "receiver from chat: " << StringUtilities::intToString(bytesReceived) << std::endl;
		} else {
			aux.append(buffer,bytesReceived);
		}
	} while ( (aux.find("</message>") == std::string::npos) && (validRead) );

	if (validRead){
		message = aux;
	}

	return message;
}

void* Receiver::run(){
	this->receive();
	return NULL;
}

void Receiver::stopReceiving(){
	this->setKeepReceiving(false);
	this->getSocket()->disconect();
	this->join();
}

Receiver::~Receiver(){
}