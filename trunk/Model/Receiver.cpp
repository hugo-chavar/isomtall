#include "Receiver.h"

#include <iostream>

#include "StringUtilities.h"

// ----------------------------------- CONSTRUCTOR ---------------------------------------

Receiver::Receiver(Socket* socket, InstructionQueue* instructionQueue, std::string userID, bool inyectUserIDonReceive) {
	this->socket = socket;
	this->userID = userID;
	this->connectionOK = true;
	this->inyectUserIDonReceive = inyectUserIDonReceive;
	this->instructionQueue = instructionQueue;
}

// ----------------------------------- PRIVATE METHODS -----------------------------------

void Receiver::setConnectionOK(bool connectionOK) {
	this->connectionOK = connectionOK;
}

bool Receiver::isInyectUserIDonReceive() {
	return this->inyectUserIDonReceive;
}

InstructionQueue* Receiver::getInstructionQueue() {
	return this->instructionQueue;
}

void Receiver::receive() {
	Instruction instruction;
	std::string request;
	std::string messageBeginTag = MESSAGE_ENVELOPE_BEGIN_TAG;

	request = this->receiveMessageFromSocket();
	while (!this->isStopping() && this->isConnectionOK()){
		instruction.clear();

		if (request != "") {
			request = request.substr(messageBeginTag.length(),(request.find(MESSAGE_ENVELOPE_END_TAG) - messageBeginTag.length()));
			instruction.deserialize(request);
		} else {
			instruction.setOpCode(OPCODE_CONNECTION_ERROR);
			this->setConnectionOK(false);
		}
		
		if (this->isInyectUserIDonReceive())
			instruction.insertArgument(INSTRUCTION_ARGUMENT_KEY_USER_ID,this->getUserID());

		this->getInstructionQueue()->addInstruction(instruction);

		request = this->receiveMessageFromSocket();
	}
}

std::string Receiver::receiveMessageFromSocket() {
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
				this->setStopping(true);
		} else {
			aux.append(buffer,bytesReceived);
		}
	} while ( (aux.find(MESSAGE_ENVELOPE_END_TAG) == std::string::npos) && (validRead) );

	if (validRead){
		message = aux;
	}

	return message;
}

void* Receiver::run(){
	this->receive();
	return NULL;
}

// ----------------------------------- PUBLIC METHODS ------------------------------------

Socket* Receiver::getSocket() {
	return this->socket;
}

void Receiver::setSocket(Socket* socket) {
	this->socket = socket;
}

std::string Receiver::getUserID() {
	return this->userID;
}

bool Receiver::isConnectionOK() {
	return this->connectionOK;
}

void Receiver::setInstructionQueue(InstructionQueue* instructionQueue) {
	this->instructionQueue = instructionQueue;
}

void Receiver::setUserID(std::string userID) {
	this->userID = userID;
}

void Receiver::startReceiving() {
	this->start();
}

void Receiver::stopReceiving(){
	this->setStopping(true);
	this->getSocket()->disconect();
	this->join();
}

// ----------------------------------- DESTRUCTOR ----------------------------------------

Receiver::~Receiver(){
}