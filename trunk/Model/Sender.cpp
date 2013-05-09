#include "Sender.h"

// ----------------------------------- CONSTRUCTOR ---------------------------------------

Sender::Sender(Socket* socket) {
	this->socket = socket;
	this->forceStop = false;
}

// ----------------------------------- PRIVATE METHODS -----------------------------------

bool Sender::isForceStop() {
	return this->forceStop;
}

void Sender::setForceStop(bool forceStop) {
	this->forceStop = forceStop;
}

InstructionQueue& Sender::getInstructionQueue() {
	return this->instructionQueue;
}

void Sender::send(){
	Instruction instruction;
	std::string mensaje;

	do {
		instruction = this->getInstructionQueue().getNextInstruction(true);
		if (instruction.getOpCode() != OPCODE_NO_OPCODE) {
			mensaje = instruction.serialize();
			this->sendMessage(mensaje);
		}
	} while (!this->isStopping());
	
	if (!this->isForceStop()) {
		do {
			instruction = this->getInstructionQueue().getNextInstruction(false);
			if (instruction.getOpCode() != OPCODE_NO_OPCODE) {
				mensaje = instruction.serialize();
				this->sendMessage(mensaje);
			}
		} while (instruction.getOpCode() != OPCODE_NO_OPCODE);
	}
}

void Sender::sendMessage(std::string message){
	unsigned int bytesSent = 0;
	unsigned int messageSize = 0;
	std::string aux;

	messageSize = message.length();

	aux = MESSAGE_ENVELOPE_BEGIN_TAG + message + MESSAGE_ENVELOPE_END_TAG;

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

// ----------------------------------- PUBLIC METHODS ------------------------------------

Socket* Sender::getSocket() {
	return this->socket;
}

void Sender::setSocket(Socket* socket) {
	this->socket = socket;
}

void Sender::startSending() {
	this->start();
}

void Sender::addInstruction(Instruction& instruction) {
	this->getInstructionQueue().addInstruction(instruction);
}

void Sender::stopSending(bool forceStop){
	this->setForceStop(forceStop);
	this->setStopping(true);
	this->getInstructionQueue().stopWaiting();
	this->join();
}

// ----------------------------------- DESTRUCTOR ----------------------------------------

Sender::~Sender(){
}

