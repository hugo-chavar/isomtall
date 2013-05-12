#pragma warning(disable: 4355)
#pragma warning(disable: 4512)
#include "LoginUpdater.h"

#include <iostream>

// ----------------------------------- CONSTRUCTOR ---------------------------------------

LoginUpdater::LoginUpdater(Mutex& messagesListMutex, std::list<std::string>& messagesList) : connector(NULL,&(this->getInstructionQueue())), messagesListMutex(messagesListMutex), messagesList(messagesList) {
	this->loggedIn = false;
}

// ----------------------------------- PRIVATE METHODS -----------------------------------

void LoginUpdater::setLoggedIn(bool loggedIn) {
	this->loggedIn = loggedIn;
}

bool LoginUpdater::isForceStop() {
	return this->forceStop;
}

void LoginUpdater::setForceStop(bool forceStop) {
	this->forceStop = forceStop;
}

Connector& LoginUpdater::getConnector() {
	return this->connector;
}

InstructionQueue& LoginUpdater::getInstructionQueue() {
	return this->instructionQueue;
}

Mutex& LoginUpdater::getMessagesListMutex() {
	return this->messagesListMutex;
}

std::list<std::string>& LoginUpdater::getMessagesList() {
	return this->messagesList;
}

void LoginUpdater::updateLoginModel() {
	// Agregado para que funcione.
//	WSAData ws;
//	WSAStartup(MAKEWORD(2,2),&ws);
	Instruction instructionIn;
	Socket* newSocket = new Socket(inet_addr("127.0.0.1"),9443,0);

	if (newSocket->connectTo() != -1) {
		this->getConnector().setSocket(newSocket);
		this->getConnector().startConnector();
		// Agregado para que funcione.
//		Instruction instructionOut;
//		instructionOut.setOpCode(OPCODE_LOGIN_REQUEST);
//		instructionOut.insertArgument(INSTRUCTION_ARGUMENT_KEY_REQUESTED_USER_ID,"Andres"); // harcodeo
		
//		this->getConnector().addInstruction(instructionOut);
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
		/*
		instructionIn = this->getInstructionQueue().getNextInstruction(true);
		while(!this->isStopping()) {
			this->processInstruction(instructionIn);
			instructionIn = this->getInstructionQueue().getNextInstruction(true);
		}

		if (!this->isForceStop()) {
			while (instructionIn.getOpCode() != OPCODE_NO_OPCODE) {
				this->processInstruction(instructionIn);
				instructionIn = this->getInstructionQueue().getNextInstruction(false);
			}
		}
		*/
	} else {
		//IDEALLY THIS SHOULD SHOW AN ERROR ON THE SCREEN. RIGHT NOW IT WILL JUST LOG THE ERROR.
		std::cout << "SERVER UNREACHABLE" << std::endl;
	}
}

void LoginUpdater::processInstruction(Instruction& instructionIn) {
	Instruction instructionOut;

	instructionOut.clear();
	switch (instructionIn.getOpCode()) {
		case OPCODE_LOGIN_REQUEST:
			instructionOut = instructionIn;
			this->getConnector().addInstruction(instructionOut);
		break;
		case OPCODE_USERID_NOT_AVAILABLE:
			this->setStopping(true);//TEMPORARY
			this->getMessagesListMutex().lock();
			this->getMessagesList().push_back(instructionIn.getArgument(INSTRUCTION_ARGUMENT_KEY_ERROR));
			this->getMessagesListMutex().unlock();
		break;
		case OPCODE_LOGIN_OK:
			this->setLoggedIn(true);
			this->getMessagesListMutex().lock();
			this->getMessagesList().push_back(instructionIn.getArgument(INSTRUCTION_ARGUMENT_KEY_GREETING));
			this->getMessagesListMutex().unlock();
		break;
		case OPCODE_LOGOUT_REQUEST:
			this->setStopping(true);
			instructionOut = instructionIn;
			this->getConnector().addInstruction(instructionOut);
		break;
		case OPCODE_CONNECTION_ERROR:
			std::cout << "CONNECTION WITH SERVER LOST" << std::endl;
			this->setStopping(true);
			this->getMessagesListMutex().lock();
			this->getMessagesList().push_back("CONNECTION WITH SERVER LOST");
			this->getMessagesListMutex().unlock();
		break;
	}
}

void* LoginUpdater::run() {
	this->updateLoginModel();
	return NULL;
}

// ----------------------------------- PUBLIC METHODS ------------------------------------

bool LoginUpdater::isLoggedIn() {
	return this->loggedIn;
}

void LoginUpdater::addInstruction(Instruction instruction) {
	this->getInstructionQueue().addInstruction(instruction);
}

void LoginUpdater::startUpdating() {
	this->start();
}

void LoginUpdater::stopUpdating(bool forceStop) {
	this->setForceStop(forceStop);
	this->setStopping(true);
	this->getInstructionQueue().stopWaiting();
	this->join();
	this->getConnector().stopConnector(forceStop);
	this->setLoggedIn(false);
}

// ----------------------------------- DESTRUCTOR ----------------------------------------

LoginUpdater::~LoginUpdater() {
}