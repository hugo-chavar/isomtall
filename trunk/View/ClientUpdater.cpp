#pragma warning(disable: 4355)
#include "ClientUpdater.h"

#include <iostream>
#include <fstream>
#include "Logger.h"

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

void ClientUpdater::crearDirectorios(std::string directorios, std::string path) {
	std::vector<std::string> directorios_v;
	stringUtilities::splitString(directorios, directorios_v, '~');
	CreateDirectory (path.c_str(), NULL);
	std::string directorioCorriente = path;
	for(unsigned i = 0; i < directorios_v.size(); i++) {
		std::string str = directorios_v[i];
		if(str != "") {
			if(str.back() == '>') {
				//Creo directorio
				str.erase(str.end()-1);
				directorioCorriente = directorioCorriente + "/" + str;
				CreateDirectory (directorioCorriente.c_str(), NULL);
			}
			else if (str == "..") {
				//Borro desde la ultima / al final en el directorio corriente
				int inicial = directorioCorriente.find_last_of('/',directorioCorriente.size() - 1);
				directorioCorriente.erase(inicial,directorioCorriente.size() - 1);
			}
		}
	}
}

void ClientUpdater::receiveFile(std::ofstream* archivo, Instruction instruction) {
	if (!(*archivo))
		return;
	char buffer[TAMBUFFER];
	std::string serializedFile = instruction.getArgument(INSTRUCTION_ARGUMENT_KEY_SERIALIZED_FILE);
	int recibidos = stringUtilities::replaceStringForChar('\0', buffer, "<BARRACERO>", serializedFile);
	archivo->write(buffer, recibidos);
}

void ClientUpdater::sendConfirmation() {
	Instruction instructionOut;
	instructionOut.clear();
	instructionOut.setOpCode(OPCODE_UPDATE_RECV);
	this->getConnector().addInstruction(instructionOut);
}


// ----------------------------------- PUBLIC METHODS ------------------------------------

void ClientUpdater::updateClient() {
	Instruction instructionIn;
	Instruction instructionOut;
	Socket* newSocket = new Socket(inet_addr(this->getServerIp().c_str()),this->getServerPort(),0);

	if (newSocket->connectTo() != -1) {
		this->getConnector().setSocket(newSocket);
		this->getConnector().startConnector();
		instructionOut.setOpCode(OPCODE_UPDATE_REQUEST);
		this->getConnector().addInstruction(instructionOut);
		instructionIn = this->getInstructionQueue().getNextInstruction(true);
		std::ofstream archivo;
		std::string path = "";
		while (instructionIn.getOpCode() != OPCODE_UPDATE_COMPLETE && this->getConnector().isConnectionOK()) {
			switch (instructionIn.getOpCode()) {
				case OPCODE_UPDATE_FILE:
					{
					receiveFile(&archivo,instructionIn);
					//this->sendConfirmation();
					}
				break;
				case OPCODE_UPDATE_FILE_START:
					{
						path = instructionIn.getArgument(INSTRUCTION_ARGUMENT_KEY_SERIALIZED_PATH);
						archivo.open(path,std::ios::binary);
						//this->sendConfirmation();
					//ABRO ARCHIVO
					}
				break;
				case OPCODE_UPDATE_FILE_COMPLETE:
					archivo.close();
					//this->sendConfirmation();
					//DEBO PARARME EN EL DIRECTORIO DEL NUEVO ARCHIVO A RECIBIR
				break;
				case OPCODE_UPDATE_DIRECTORY:
					{
						std::string directorios = instructionIn.getArgument(INSTRUCTION_ARGUMENT_KEY_SERIALIZED_DIR);
						path = instructionIn.getArgument(INSTRUCTION_ARGUMENT_KEY_SERIALIZED_PATH);
						this->crearDirectorios(directorios,path);
						//this->sendConfirmation();
						//DEBO RECIBIR ARBOL DE DIRECTORIOS A PROCESAR
					}
				break;
			}
			instructionIn = this->getInstructionQueue().getNextInstruction(true);
		}
		instructionOut.clear();
		instructionOut.setOpCode(OPCODE_DISCONNECT);
		this->getConnector().addInstruction(instructionOut);
		this->getConnector().stopConnector(false);
		if(archivo.is_open())
			{archivo.close();}
	} else {
		//IDEALLY THIS SHOULD SHOW AN ERROR ON THE SCREEN. RIGHT NOW IT WILL JUST LOG THE ERROR.
		//TODO: YAMILA
		std::cout << "SERVER UNREACHABLE" << std::endl;
	}
}

void ClientUpdater::setServerPort(int port) {
	this->serverPort = port;
}

void ClientUpdater::setServerIp(std::string ip) {
	this->serverIp = ip;
}

int ClientUpdater::getServerPort() {
	return this->serverPort;
}

std::string ClientUpdater::getServerIp() {
	return this->serverIp;
}

// ----------------------------------- DESTRUCTOR ----------------------------------------

ClientUpdater::~ClientUpdater() {
}