#include "Sender.h"

Sender::Sender(Socket* socket) {
	this->socket = socket;
	this->keepSending = true;
	this->forceShutdown = false;
}

void Sender::startSending() {
	this->start();
}

void Sender::addInstruction(Instruction& instruction) {
	this->getInstructionQueue().addInstruction(instruction);
}

void Sender::setKeepSending(bool keepSending) {
	this->keepSending = keepSending;
}

bool Sender::getKeepSending() const {
	return this->keepSending;
}

Socket* Sender::getSocket() const {
	return this->socket;
}

bool Sender::getForceShutdown() {
	return this->forceShutdown;
}

void Sender::setForceShutdown(bool forceShutdown) {
	this->forceShutdown = forceShutdown;
}

InstructionQueue& Sender::getInstructionQueue() {
	return this->instructionQueue;
}

void Sender::send(){
	Instruction instruction;
	std::string response;

	instruction = this->getInstructionQueue().getNextInstruction(true);
	while (this->getKeepSending()) {
		response = instruction.serialize();
		this->sendMessage(response);
		instruction.clear();
		instruction = this->getInstructionQueue().getNextInstruction(true);
	}

	if (!this->getForceShutdown()) {
		while (instruction.getOpCode() != OPCODE_NO_OPCODE) {
			response = instruction.serialize();
			this->sendMessage(response);
			instruction.clear();
			instruction = this->getInstructionQueue().getNextInstruction(false);
		}
	}
}

void Sender::sendMessage(std::string message){
	unsigned int bytesSent = 0;
	unsigned int messageSize = 0;
	std::string aux;

	messageSize = message.length();

	aux = "<message>" + message + "</message>";

	do {
		bytesSent += this->getSocket()->sendData(aux.c_str());
		if (bytesSent < messageSize){
			aux = message.substr(bytesSent - 1);
		}
	} while (bytesSent < messageSize);
}

void* Sender::run(){
	this->send();
	return NULL;
}

void Sender::stopSending(bool forceShutdown){
	this->setForceShutdown(forceShutdown);
	this->setKeepSending(false);
	this->getInstructionQueue().stopWaiting();
	this->join();
}

Sender::~Sender(){
}

