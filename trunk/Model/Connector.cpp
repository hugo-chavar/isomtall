#include "Connector.h"

// ----------------------------------- CONSTRUCTOR ---------------------------------------

Connector::Connector(Socket* socket, InstructionQueue* instructionQueue, std::string userID, bool inyectUserIDonReceive) : sender(socket), receiver(socket,instructionQueue,userID,inyectUserIDonReceive) {
}

// ----------------------------------- PRIVATE METHODS -----------------------------------

std::string Connector::getUserID() {
	return this->getReceiver().getUserID();
}

Socket* Connector::getSocket() {
	return this->getSender().getSocket();
}

void Connector::setSocket(Socket* socket) {
	this->getSender().setSocket(socket);
	this->getReceiver().setSocket(socket);
}

Sender& Connector::getSender() {
	return this->sender;
}


Receiver& Connector::getReceiver() {
	return this->receiver;
}

// ----------------------------------- PUBLIC METHODS ------------------------------------

bool Connector::isConnectionOK() {
	return this->getReceiver().isConnectionOK();
}

void Connector::setUserID(std::string userID) {
	this->getReceiver().setUserID(userID);
}

void Connector::setInstructionQueue(InstructionQueue* instructionQueue) {
	this->getReceiver().setInstructionQueue(instructionQueue);
}

void Connector::addInstruction(Instruction& instruction) {
	this->getSender().addInstruction(instruction);
}

void Connector::startConnector() {
	this->getSender().startSending();
	this->getReceiver().startReceiving();
}

void Connector::stopConnector(bool forced) {
	this->getSender().stopSending(forced);
	this->getReceiver().stopReceiving();
}

// ----------------------------------- DESTRUCTOR ----------------------------------------

Connector::~Connector(){
	delete this->getSocket();
}
