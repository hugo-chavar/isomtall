#include "ClientUpdater.h"

#include <iostream>

// ----------------------------------- CONSTRUCTOR ---------------------------------------

ClientUpdater::ClientUpdater() : connector(NULL,&(this->getInstructionQueue())) {
	//THIS SHOUD BE RETRIEVED FROM A FILE.
	this->version = "";
}

// ----------------------------------- PRIVATE METHODS -----------------------------------

std::string& ClientUpdater::getVersion() {
	return this->version;
}

Connector& ClientUpdater::getConnector() {
	return this->connector;
}

InstructionQueue& ClientUpdater::getInstructionQueue() {
	return this->instructionQueue;
}

// ----------------------------------- PUBLIC METHODS ------------------------------------

void ClientUpdater::updateClient() {
	Instruction instructionIn;
	Instruction instructionOut;
	Socket* newSocket = new Socket(inet_addr("127.0.0.1"),9443,0);

	if (newSocket->connectTo() != -1) {
		this->getConnector().setSocket(newSocket);
		this->getConnector().startConnector();
		instructionOut.setOpCode(OPCODE_UPDATE_REQUEST);
		this->getConnector().addInstruction(instructionOut);
		instructionIn = this->getInstructionQueue().getNextInstruction(true);
		while (instructionIn.getOpCode() != OPCODE_UPDATE_COMPLETE && this->getConnector().isConnectionOK()) {
			switch (instructionIn.getOpCode()) {
				case OPCODE_UPDATE_FILE:

					//ACA SE OBTIENEN LOS ARCHIVOS DEL SERVIDOR Y SE GUARDAN

				break;
			}
			instructionIn = this->getInstructionQueue().getNextInstruction(true);
		}
		instructionOut.clear();
		instructionOut.setOpCode(OPCODE_DISCONNECT);
		this->getConnector().addInstruction(instructionOut);
		this->getConnector().stopConnector(false);
	} else {
		//IDEALLY THIS SHOULD SHOW AN ERROR ON THE SCREEN. RIGHT NOW IT WILL JUST LOG THE ERROR.
		std::cout << "SERVER UNREACHABLE" << std::endl;
	}
}

// ----------------------------------- DESTRUCTOR ----------------------------------------

ClientUpdater::~ClientUpdater() {
}