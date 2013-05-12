#include "ModelUpdater.h"

#include "StringUtilities.h"

#include <iostream>

// ----------------------------------- CONSTRUCTOR ---------------------------------------

ModelUpdater::ModelUpdater() : connector(NULL,&(this->getInstructionQueue())) {
	this->connected = false;
	this->activatedAt = 0;
}

// ----------------------------------- PRIVATE METHODS -----------------------------------

void ModelUpdater::setConnected(bool connected) {
	this->connected = connected;
}


void ModelUpdater::setActivatedAt(unsigned int activatedAt) {
	this->activatedAt = activatedAt;
}

bool ModelUpdater::isForceStop() {
	return this->forceStop;
}

void ModelUpdater::setForceStop(bool forceStop) {
	this->forceStop = forceStop;
}

Connector& ModelUpdater::getConnector() {
	return this->connector;
}

InstructionQueue& ModelUpdater::getInstructionQueue() {
	return this->instructionQueue;
}

void ModelUpdater::updateModel() {
	Instruction instructionIn;
	Socket* newSocket = new Socket(inet_addr("127.0.0.1"),9443,0);

	if (newSocket->connectTo() != -1) {
		this->getConnector().setSocket(newSocket);
		this->getConnector().startConnector();

		do {
			instructionIn = this->getInstructionQueue().getNextInstruction(true);
			if (instructionIn.getOpCode() != OPCODE_NO_OPCODE) {
				this->processInstruction(instructionIn);
			}
		} while (!this->isStopping());

		if (!this->isForceStop()) {
			do {
				instructionIn = this->getInstructionQueue().getNextInstruction(false);
				if (instructionIn.getOpCode() != OPCODE_NO_OPCODE) {
					this->processInstruction(instructionIn);
				}
			} while (instructionIn.getOpCode() != OPCODE_NO_OPCODE);
		}
	} else {
		//IDEALLY THIS SHOULD SHOW AN ERROR ON THE SCREEN. RIGHT NOW IT WILL JUST LOG THE ERROR.
		std::cout << "SERVER UNREACHABLE" << std::endl;
	}
}

void ModelUpdater::processInstruction(Instruction& instructionIn) {
	Instruction instructionOut;

	instructionOut.clear();
	switch (instructionIn.getOpCode()) {
		case OPCODE_CONNECT_TO_SIMULATION:
			instructionOut = instructionIn;
			this->getConnector().addInstruction(instructionOut);
		break;
		case OPCODE_DISCONNECT_FROM_SIMULATION:
			this->setConnected(false);
			this->setStopping(true);
			instructionOut = instructionIn;
			this->getConnector().addInstruction(instructionOut);
		break;
		case OPCODE_SIMULATION_CONNECTION_ESTABLISHED:
			this->setConnected(true);
			std::cout << "CONNECTION WITH SERVER SIMULATION ESTABLISHED" << std::endl;
			instructionOut.setOpCode(OPCODE_SIMULATION_SYNCHRONIZE);
			this->getConnector().addInstruction(instructionOut);
		break;
		case OPCODE_SIMULATION_SYNCHRONIZE:
			this->setActivatedAt(stringUtilities::stringToInt(instructionIn.getArgument(INSTRUCTION_ARGUMENT_KEY_CONNECTED_AT)));
		break;
		case OPCODE_CLIENT_COMMAND:
			instructionOut = instructionIn;
			this->getConnector().addInstruction(instructionOut);
		break;
		case OPCODE_SIMULATION_UPDATE:
			std::cout << instructionIn.serialize() << std::endl;
		break;
		case OPCODE_CONNECTION_ERROR:
			std::cout << "CONNECTION WITH SERVER LOST" << std::endl;
			this->setConnected(false);
			this->setStopping(true);
		break;
	}
}

void* ModelUpdater::run() {
	this->updateModel();
	return NULL;
}

// ----------------------------------- PUBLIC METHODS ------------------------------------

bool ModelUpdater::isConnected() {
	return this->connected;
}

unsigned int ModelUpdater::getActivatedAt() {
	return this->activatedAt;
}

void ModelUpdater::addInstruction(Instruction instruction) {
	this->getInstructionQueue().addInstruction(instruction);
}

void ModelUpdater::startUpdating() {
	this->start();
}

void ModelUpdater::stopUpdating(bool forceStop) {
	this->setForceStop(forceStop);
	this->setStopping(true);
	this->getInstructionQueue().stopWaiting();
	this->join();
	this->getConnector().stopConnector(forceStop);
	this->setConnected(false);
}

// ----------------------------------- DESTRUCTOR ----------------------------------------

ModelUpdater::~ModelUpdater() {
}