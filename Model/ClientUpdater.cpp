#pragma warning(disable: 4355)
#include "ClientUpdater.h"

#include <iostream>
#include <fstream>

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

void ClientUpdater::crearDirectorios(std::string directorios,std::string path)
{
	std::vector<std::string> directorios_v;
	stringUtilities::splitString(directorios,directorios_v,'~');
	CreateDirectory (path.c_str(), NULL);
	std::string directorioCorriente=path;
	for(int i=0;i<directorios_v.size();i++)
	{
		std::string str=directorios_v[i];
		if(str!="")
		{
			if(str.back()=='>')
			{
				//Creo directorio
				str.erase(str.end()-1);
				directorioCorriente=directorioCorriente+"/"+str;
				CreateDirectory (directorioCorriente.c_str(), NULL);
			}
			else if(str=="..")
			{
				//Borro desde la ultima / al final en el directorio corriente
				int inicial=directorioCorriente.find_last_of('/',directorioCorriente.size()-1);
				directorioCorriente.erase(inicial,directorioCorriente.size()-1);
			}
		}
	}
}

void ClientUpdater::receiveFile(std::ofstream* archivo,Instruction instruction)
{
	if (!(*archivo))
		return;
	std::string serializedFile = instruction.getArgument(INSTRUCTION_ARGUMENT_KEY_SERIALIZED_FILE);
	archivo->write(serializedFile.c_str(),serializedFile.size());
}


// ----------------------------------- PUBLIC METHODS ------------------------------------

void ClientUpdater::updateClient() {
	//Agregado, no se conectaba
//	WSAData ws;
//	WSAStartup(MAKEWORD(2,2),&ws);
	Instruction instructionIn;
	Instruction instructionOut;
	Socket* newSocket = new Socket(inet_addr("127.0.0.1"),9443,0);

	if (newSocket->connectTo() != -1) {
		this->getConnector().setSocket(newSocket);
		this->getConnector().startConnector();
		instructionOut.setOpCode(OPCODE_UPDATE_REQUEST);
		this->getConnector().addInstruction(instructionOut);
		instructionIn = this->getInstructionQueue().getNextInstruction(true);
		std::ofstream archivo;
		std::string path="";
		while (instructionIn.getOpCode() != OPCODE_UPDATE_COMPLETE && this->getConnector().isConnectionOK()) {
			switch (instructionIn.getOpCode()) {
				case OPCODE_UPDATE_FILE:
					receiveFile(&archivo,instructionIn);
				break;
				case OPCODE_UPDATE_FILE_START:
					{
						path = instructionIn.getArgument(INSTRUCTION_ARGUMENT_KEY_SERIALIZED_PATH);
						archivo.open(path,std::ios::binary);
					//ABRO ARCHIVO
					}
				break;
				case OPCODE_UPDATE_FILE_COMPLETE:
					archivo.close();
					//DEBO PARARME EN EL DIRECTORIO DEL NUEVO ARCHIVO A RECIBIR
				break;
				case OPCODE_UPDATE_DIRECTORY:
					{
					std::string directorios = instructionIn.getArgument(INSTRUCTION_ARGUMENT_KEY_SERIALIZED_DIR);
					path = instructionIn.getArgument(INSTRUCTION_ARGUMENT_KEY_SERIALIZED_PATH);
					this->crearDirectorios(directorios,path);
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
	} else {
		//IDEALLY THIS SHOULD SHOW AN ERROR ON THE SCREEN. RIGHT NOW IT WILL JUST LOG THE ERROR.
		std::cout << "SERVER UNREACHABLE" << std::endl;
	}
}

// ----------------------------------- DESTRUCTOR ----------------------------------------

ClientUpdater::~ClientUpdater() {
}