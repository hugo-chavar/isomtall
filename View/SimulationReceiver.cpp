#include "SimulationReceiver.h"

#include "Logger.h"
#include "stringUtilities.h"
#include "SDL.h"

SimulationReceiver::SimulationReceiver(Socket* socket, InstructionQueue* instructionQueue, std::string userID, bool inyectUserIDonReceive) : Receiver(socket,instructionQueue,userID,inyectUserIDonReceive) {
//No hago nada. Creo esta clase unicamente para redefinir el receiveFromSocket
}

SimulationReceiver::~SimulationReceiver()
{
}

std::string SimulationReceiver::receiveMessageFromSocket()
{
	bool validRead = true;
	char buffer[512] = "";
	int bytesReceived = 0;
	std::string aux = this->getReminder();
	std::string message = "";
	std::string messageEndTag = MESSAGE_ENVELOPE_END_TAG;
	unsigned int messageEndPosition = 0;

	messageEndPosition = this->getReminder().find(messageEndTag);
	if (messageEndPosition != this->getReminder().npos) {
		messageEndPosition += messageEndTag.length();
		message = this->getReminder().substr(0,messageEndPosition);
		this->setReminder(this->getReminder().substr(messageEndPosition));
		//common::Logger::instance().log("			Returning message: " + message +  " from remainder - at: " + stringUtilities::longToString(SDL_GetTicks()));
		//Sleep(20);//Parche
		return message;
	}

	do {
		bytesReceived = this->getSocket()->receiveData(buffer,512);
		if (bytesReceived <= 0) {
			validRead = false;
			if (bytesReceived == 0)
				this->setStopping(true);
		} else {
			aux.append(buffer,bytesReceived);
		}
	} while ( (aux.find(messageEndTag) == std::string::npos) && (validRead) );

	if (validRead) {
		messageEndPosition = aux.find(messageEndTag) + messageEndTag.length();
		message = aux.substr(0,messageEndPosition);
		this->setReminder(aux.substr(messageEndPosition));
	}

	//common::Logger::instance().log("			Returning message: " + message +  " from socket - at: " + stringUtilities::longToString(SDL_GetTicks()));
	return message;
}