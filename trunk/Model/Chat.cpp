#include "Chat.h"

// ----------------------------------- CONSTRUCTOR ---------------------------------------

model::Chat::Chat() : chatUpdater(this->getMessagesListMutex(), this->getMessagesList()) {
//	this->socket = NULL;
//	this->loggedIn = false;
	this->inputBuffer = "";
	to = "";
}

// ----------------------------------- PRIVATE METHODS -----------------------------------

ChatUpdater& model::Chat::getChatUpdater() {
	return this->chatUpdater;
}

std::string model::Chat::getTo() {
	return this->to;
}

// ----------------------------------- PUBLIC METHODS ------------------------------------

bool model::Chat::isConnected() {
	return this->getChatUpdater().isConnected();
}

/*
void model::Chat::setLoggedIn(bool loggedIn) {
	this->loggedIn = loggedIn;
}
*/

std::string model::Chat::getInputBuffer() {
	return this->inputBuffer;
}

void model::Chat::setInputBuffer(std::string inputBuffer) {
	this->inputBuffer = inputBuffer;
}

Mutex& model::Chat::getMessagesListMutex() {
	return this->messagesListMutex;
}

std::list<std::string>& model::Chat::getMessagesList() {
	return this ->messagesList;
}

/*
Socket* model::Chat::getSocket() {
	return this->socket;
}

void model::Chat::setSocket(Socket* socket) {
	this->socket = socket;
}

Sender* model::Chat::getSender() {
	return this->sender;
}

void model::Chat::setSender(Sender* sender) {
	this->sender = sender;
}

Receiver* model::Chat::getReceiver() {
	return this->receiver;
}

void model::Chat::setReceiver(Receiver* receiver) {
	this->receiver = receiver;
}
*/


void model::Chat::setTo(std::string to) {
	this->to = to;
}

void model::Chat::sendMessage() {
	Instruction instruction;

	if (this->isConnected()) {
		instruction.setOpCode(OPCODE_CHAT_MESSAGE_OUT);
		instruction.insertArgument(INSTRUCTION_ARGUMENT_KEY_MESSAGE,this->getInputBuffer());
		instruction.insertArgument(INSTRUCTION_ARGUMENT_KEY_TO,this->getTo());
		this->getChatUpdater().addInstruction(instruction);
		this->inputBuffer = "";
	}
}

void model::Chat::initialize() {
	Instruction instruction;
	this->getChatUpdater().startUpdating();

/*	WSAData ws;
	WSAStartup(MAKEWORD(2,2),&ws);

	Socket* newSocket = new Socket(inet_addr("127.0.0.1"),9443,0);
	if (newSocket->connectTo() != -1) {
		this->getMessagesList().push_back("user name?");

		this->setSocket(newSocket);

		Sender* newSender = new Sender(this->getSocket());
		Receiver* newReceiver = new Receiver(this->getSocket(),this->getMessagesListMutex(),this->getMessagesList(),this->isLoggedIn());

		this->setSender(newSender);
		this->getSender()->startSending();
	
		this->setReceiver(newReceiver);
		this->getReceiver()->startReceiving();


	} else {
		this->getMessagesList().push_back("SERVER UNREACHABLE");
	}*/
}

void model::Chat::update() {
	//NOTHING TO DO HERE FOR NOW;
}

void model::Chat::cleanUp() {
	Instruction instructionOut;

	if (this->isConnected()) {
		instructionOut.setOpCode(OPCODE_CHAT_LOGOUT_REQUEST);
		this->getChatUpdater().addInstruction(instructionOut);
		this->getChatUpdater().stopUpdating(false);
	}

	WSACleanup();
}

model::Chat::~Chat() {
}