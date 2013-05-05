#include "Chat.h"

model::Chat::Chat() {
	this->socket = NULL;
	this->loggedIn = false;
	to = "";
}

bool& model::Chat::isLoggedIn() {
	return this->loggedIn;
}

void model::Chat::setLoggedIn(bool loggedIn) {
	this->loggedIn = loggedIn;
}

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

std::string model::Chat::getTo() {
	return this->to;
}

void model::Chat::setTo(std::string to) {
	this->to = to;
}

void model::Chat::sendMessage() {
	if(connected)
	{
	Instruction instruction;
	if (!this->isLoggedIn()) {
		instruction.setOpCode(OPCODE_LOGIN_REQUEST);
		instruction.insertArgument("requestedUserID",inputBuffer);
	} else {
		instruction.setOpCode(OPCODE_CHAT_MESSAGE);
		instruction.insertArgument("message",inputBuffer);
		instruction.insertArgument("to",this->getTo());
	}

	this->getSender()->addInstruction(instruction);
	this->inputBuffer = "";
	}
}

void model::Chat::initialize() {
	WSAData ws;
	WSAStartup(MAKEWORD(2,2),&ws);

	Socket* newSocket = new Socket(inet_addr("127.0.0.1"),9443,0);
	if (newSocket->connectTo() != -1) {
		//this->getMessagesList().push_back("user name?");
		connected=true;
		this->setSocket(newSocket);

		Sender* newSender = new Sender(this->getSocket());
		Receiver* newReceiver = new Receiver(this->getSocket(),this->getMessagesListMutex(),this->getMessagesList(),this->isLoggedIn());

		this->setSender(newSender);
		this->getSender()->startSending();
		this->setReceiver(newReceiver);
		this->getReceiver()->startReceiving();
		this->setInputBuffer(Game::instance().personaje()->getName());
		this->sendMessage();


	} else {
		connected=false;
		this->getMessagesList().push_back("SERVER UNREACHABLE");
	}
}

void model::Chat::update() {
}

void model::Chat::cleanUp() {
	Instruction instruction;

	if (this->isLoggedIn()) {
		instruction.setOpCode(OPCODE_LOGOUT_REQUEST);
		this->getSender()->addInstruction(instruction);
		this->getSender()->stopSending(false);
		this->getReceiver()->stopReceiving();
	}

	WSACleanup();
}

model::Chat::~Chat() {
	if(connected)
	{
	delete this->getSender();
	delete this->getReceiver();
	}
	delete this->getSocket();
}