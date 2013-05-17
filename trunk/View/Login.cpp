#pragma warning(disable: 4355)

#include "Login.h"

#include <iostream>

// ----------------------------------- CONSTRUCTOR ---------------------------------------

model::Login::Login() : loginUpdater(this->getMessagesListMutex(),this->getMessagesList()) {
}

// ----------------------------------- PRIVATE METHODS -----------------------------------

LoginUpdater& model::Login::getLoginUpdater() {
	return this->loginUpdater;
}

// ----------------------------------- PUBLIC METHODS ------------------------------------

bool model::Login::isLoggedIn() {
	return this->getLoginUpdater().isLoggedIn();
}

Mutex& model::Login::getMessagesListMutex() {
	return this->messagesListMutex;
}

std::list<std::string>& model::Login::getMessagesList() {
	return this->messagesList;
}

void model::Login::initialize() {
	this->getLoginUpdater().startUpdating();
}

void model::Login::update() {
	//NOTHING TO DO HERE FOR NOW;
}

void model::Login::cleanUp() {
	Instruction instructionOut;

	if (this->isLoggedIn()) {
		instructionOut.setOpCode(OPCODE_LOGOUT_REQUEST);
		this->getLoginUpdater().addInstruction(instructionOut);
		this->getLoginUpdater().stopUpdating(false);
	}
}

// ----------------------------------- DESTRUCTOR ----------------------------------------

model::Login::~Login() {
}