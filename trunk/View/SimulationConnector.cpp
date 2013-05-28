#include "SimulationConnector.h"

// ----------------------------------- CONSTRUCTOR ---------------------------------------

SimulationConnector::SimulationConnector(Socket* socket, InstructionQueue* instructionQueue, std::string userID, bool inyectUserIDonReceive) : sender(socket), receiver(socket,instructionQueue,userID,inyectUserIDonReceive) {
}

// ----------------------------------- PRIVATE METHODS -----------------------------------

std::string SimulationConnector::getUserID() {
	return this->getReceiver().getUserID();
}

Socket* SimulationConnector::getSocket() {
	return this->getSender().getSocket();
}

void SimulationConnector::setSocket(Socket* socket) {
	this->getSender().setSocket(socket);
	this->getReceiver().setSocket(socket);
}

void SimulationConnector::setBroadcastConditionVariable(ConditionVariable* broadcastConditionVariable) {
	this->getSender().setBroadcastConditionVariable(broadcastConditionVariable);
}

Sender& SimulationConnector::getSender() {
	return this->sender;
}


SimulationReceiver& SimulationConnector::getReceiver() {
	return this->receiver;
}

// ----------------------------------- PUBLIC METHODS ------------------------------------

bool SimulationConnector::isConnectionOK() {
	return this->getReceiver().isConnectionOK();
}

void SimulationConnector::setUserID(std::string userID) {
	this->getReceiver().setUserID(userID);
}

void SimulationConnector::setInstructionQueue(InstructionQueue* instructionQueue) {
	this->getReceiver().setInstructionQueue(instructionQueue);
}

void SimulationConnector::addInstruction(Instruction& instruction) {
	this->getSender().addInstruction(instruction);
}

void SimulationConnector::addBroadcast(Instruction& instruction) {
	this->getSender().addBroadcast(instruction);
}

void SimulationConnector::startConnector() {
	this->getSender().startSending();
	this->getReceiver().startReceiving();
}

void SimulationConnector::stopConnector(bool forced) {
	this->getSender().stopSending(forced);
	this->getReceiver().stopReceiving();
}

// ----------------------------------- DESTRUCTOR ----------------------------------------

SimulationConnector::~SimulationConnector(){
	delete this->getSocket();
}
