#pragma warning(disable: 4355)

#include "ChatUpdater.h"

#include <iostream>

// ----------------------------------- CONSTRUCTOR ---------------------------------------

ChatUpdater::ChatUpdater(Mutex& messagesListMutex, std::list<std::string>& messagesList) : connector(NULL,&(this->getInstructionQueue())), messagesListMutex(messagesListMutex), messagesList(messagesList) {
	this->connected = false;
}

// ----------------------------------- PRIVATE METHODS -----------------------------------

void ChatUpdater::setConnected(bool connected) {
	this->connected = connected;
}

bool ChatUpdater::isForceStop() {
	return this->forceStop;
}

void ChatUpdater::setForceStop(bool forceStop) {
	this->forceStop = forceStop;
}

Connector& ChatUpdater::getConnector() {
	return this->connector;
}

InstructionQueue& ChatUpdater::getInstructionQueue() {
	return this->instructionQueue;
}

Mutex& ChatUpdater::getMessagesListMutex() {
	return this->messagesListMutex;
}

std::list<std::string>& ChatUpdater::getMessagesList() {
	return this->messagesList;
}

void ChatUpdater::updateChatModel() {
//	WSAData ws;
//	WSAStartup(MAKEWORD(2,2),&ws);
	Instruction instructionIn;
//	Instruction instructionOut;
	Socket* newSocket = new Socket(inet_addr("127.0.0.1"),9443,0);

	if (newSocket->connectTo() != -1) {
		this->getConnector().setSocket(newSocket);
		this->getConnector().startConnector();
//		instructionOut.setOpCode(OPCODE_CONNECT_TO_CHAT);
//		instructionOut.insertArgument(INSTRUCTION_ARGUMENT_KEY_USER_ID,"1"); // harcodeo
//		this->addInstruction(instructionOut);
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
		this->getMessagesList().push_back("SERVER UNREACHABLE");
		//std::cout << "SERVER UNREACHABLE" << std::endl;
	}
}

void ChatUpdater::processInstruction(Instruction& instructionIn) {
	Instruction instructionOut;

	instructionOut.clear();
	switch (instructionIn.getOpCode()) {
		case OPCODE_CONNECT_TO_CHAT:
			instructionOut = instructionIn;
			this->getConnector().addInstruction(instructionOut);
		break;
		case OPCODE_CHAT_MESSAGE_OUT:
			instructionOut = instructionIn;
			this->getConnector().addInstruction(instructionOut);
		break;
		case OPCODE_CHAT_MESSAGE_IN:
			this->getConnector().addInstruction(instructionOut);
			this->getMessagesListMutex().lock();
			this->getMessagesList().push_back(instructionIn.getArgument(INSTRUCTION_ARGUMENT_KEY_FROM) + ": " + instructionIn.getArgument(INSTRUCTION_ARGUMENT_KEY_MESSAGE));
			this->getMessagesListMutex().unlock();
		break;
		case OPCODE_CHAT_LOGOUT_REQUEST:
			this->setConnected(false);
			this->setStopping(true);//TEMPORARY
			instructionOut = instructionIn;
			this->getConnector().addInstruction(instructionOut);
		break;
		case OPCODE_CHAT_CONNECTION_ESTABLISHED:
			this->setConnected(true);
			this->getMessagesListMutex().lock();
			this->getMessagesList().push_back(instructionIn.getArgument(INSTRUCTION_ARGUMENT_KEY_GREETING));
			this->getMessagesListMutex().unlock();
		break;
		case OPCODE_CONNECTION_ERROR:
			std::cout << "CONNECTION WITH SERVER LOST" << std::endl;
			this->setConnected(false);
			this->setStopping(true);
			this->getMessagesListMutex().lock();
			this->getMessagesList().push_back("CONNECTION WITH SERVER LOST");
			this->getMessagesListMutex().unlock();
		break;
	}
}

void* ChatUpdater::run() {
	this->updateChatModel();
	return NULL;
}

// ----------------------------------- PUBLIC METHODS ------------------------------------

bool ChatUpdater::isConnected() {
	return this->connected;
}

void ChatUpdater::addInstruction(Instruction instruction) {
	this->getInstructionQueue().addInstruction(instruction);
}

void ChatUpdater::startUpdating() {
	this->start();
}

void ChatUpdater::stopUpdating(bool forceStop) {
	this->setForceStop(forceStop);
	this->setStopping(true);
	this->getInstructionQueue().stopWaiting();
	this->join();
	this->getConnector().stopConnector(forceStop);
	this->setConnected(false);
}

// ----------------------------------- DESTRUCTOR ----------------------------------------

ChatUpdater::~ChatUpdater() {
}