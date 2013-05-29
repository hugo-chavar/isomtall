#include "ModelUpdater.h"
#pragma warning(disable: 4355)

#include "StringUtilities.h"
#include "Game.h"
#include "GameView.h"
#include "Logger.h"
#include "SDL.h"
#include <iostream>

// ----------------------------------- CONSTRUCTOR ---------------------------------------

ModelUpdater::ModelUpdater() : connector(NULL,&(this->getInstructionQueue())) {
	this->connected = false;
	this->errors = false;
	this->activatedAt = 0;
	this->diffDelay = 0;
	this->lastServerDelay = 0;
	this->startedAt = 0;
}

// ----------------------------------- PRIVATE METHODS -----------------------------------

void ModelUpdater::setConnected(bool connected) {
	this->connected = connected;
}
//
//void ModelUpdater::setError(bool error) {
//	this->errors = error;
//}

void ModelUpdater::setServerReached(bool serverReached) {
	this->serverReached = serverReached;
}

void ModelUpdater::setActivatedAt(unsigned int activatedAt) {
	this->activatedAt = activatedAt;
}


void ModelUpdater::setStartedAt(unsigned int startedAt) {
	this->startedAt = startedAt;
}

bool ModelUpdater::isForceStop() {
	return this->forceStop;
}

void ModelUpdater::setForceStop(bool forceStop) {
	this->forceStop = forceStop;
}

SimulationConnector& ModelUpdater::getConnector() {
	return this->connector;
}

InstructionQueue& ModelUpdater::getInstructionQueue() {
	return this->instructionQueue;
}

void ModelUpdater::updateModel() {
	Instruction instructionIn;
	Instruction instructionOut;
	int port = Game::instance().configuration()->serverPort();
	std::string ipAddress = Game::instance().configuration()->serverIp();
	Socket* newSocket = new Socket(inet_addr(ipAddress.c_str()), port, 0);

	if (newSocket->connectTo() != -1) {
		this->setServerReached(true);
		//GameView::instance().setStatus(STATUS_SIMULATION_CONNECTED);
		this->getConnector().setSocket(newSocket);
		this->getConnector().startConnector();

		do {
			unsigned startTime = static_cast<unsigned>(SDL_GetTicks());
			instructionIn = this->getInstructionQueue().getNextInstruction(true);
			unsigned updateTime = static_cast<unsigned>(SDL_GetTicks()) - startTime;
			std::string upt = " Instruction wait time: "+ stringUtilities::padLeft(stringUtilities::unsignedToString(updateTime),' ',10);
			common::Logger::instance().log(upt);
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
		this->setServerReached(false);

		//std::cout << "SERVER UNREACHABLE" << std::endl;
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
			GameView::instance().setStatus(STATUS_SIMULATION_CONNECTED);
			//std::cout << "CONNECTION WITH SERVER SIMULATION ESTABLISHED" << std::endl;
			instructionOut.setOpCode(OPCODE_SIMULATION_SYNCHRONIZE);
			this->getConnector().addInstruction(instructionOut);
			instructionOut.clear();
			instructionOut.setOpCode(OPCODE_INIT_SYNCHRONIZE);
			//instructionOut.insertArgument(INSTRUCTION_ARGUMENT_KEY_REQUESTED_USER_ID,GameView::instance().getPlayerName());
			instructionOut.insertArgument( INSTRUCTION_ARGUMENT_KEY_CHARACTER, GameView::instance().getPlayerCharacterId());
			this->getConnector().addInstruction(instructionOut);
		break;
		case OPCODE_SIMULATION_SYNCHRONIZE:
			{
				std::string serverStart = instructionIn.getArgument(INSTRUCTION_ARGUMENT_KEY_CONNECTED_AT);
				this->setActivatedAt(stringUtilities::stringToUnsigned(serverStart));
				common::Logger::instance().log("Server start: "+ serverStart);
				unsigned clientStart = static_cast<unsigned>(SDL_GetTicks());
				this->setStartedAt(clientStart);
				common::Logger::instance().log("Client start: "+ stringUtilities::unsignedToString(clientStart));
			}
			break;
		case OPCODE_INIT_SYNCHRONIZE:
			{
				std::string syncData = instructionIn.getArgument(INSTRUCTION_ARGUMENT_KEY_CHARACTER_INIT);
				GameView::instance().getMyPersonaje()->initFromString(syncData);
				GameView::instance().getMyPersonaje()->setActive(true);
				this->requestSynchronize();
			}
			break;
		case OPCODE_CLIENT_COMMAND:
			instructionOut = instructionIn;
			this->getConnector().addInstruction(instructionOut);
		break;
		case OPCODE_SIMULATION_UPDATE:
			this->simulationUpdate(instructionIn);
		break;
		case OPCODE_CONNECTION_ERROR:
			//std::cout << "CONNECTION WITH SERVER LOST" << std::endl;
			GameView::instance().setStatus(STATUS_SIMULATION_CONNECTION_LOST);
			//this->setError(true);
			this->setConnected(false);
			this->setStopping(true);
			break;
		case OPCODE_CHARACTERS_SYNCHRONIZE:
			this->syncAllPlayer(instructionIn);
			break;
	}
}

void* ModelUpdater::run() {
	this->updateModel();
	return NULL;
}

//Ejemplo de recepcion player,Xpath,Ypath tileX, tileY,animacion(0 si no esta animando):player, tileX, tileY,animacion(0 si no esta animando) "

void ModelUpdater::simulationUpdate(Instruction& instructionIn) {
	Instruction instructionOut;
	std::string serializedSimulation = instructionIn.getArgument(INSTRUCTION_ARGUMENT_KEY_SIMULATION_UPDATE);
	std::vector<std::string> player_simulations;

	stringUtilities::splitString(serializedSimulation,player_simulations,':');
	if (player_simulations.size() < 1)
		return;
	std::string stserverTicks = instructionIn.getArgument(INSTRUCTION_ARGUMENT_KEY_CONNECTED_AT);
	unsigned serverTicks = stringUtilities::stringToUnsigned(stserverTicks);
	unsigned clientTicks = static_cast<unsigned>(SDL_GetTicks());
	if ((this->startedAt < clientTicks) && (this->activatedAt < serverTicks)) {
		std::string serTic = "ServerTicks. "+ stringUtilities::padLeft(stserverTicks,' ',10);
		std::string cliTic = " CliTicks. "+ stringUtilities::padLeft(stringUtilities::unsignedToString(clientTicks),' ',10);
		unsigned clientTickMove = clientTicks - this->startedAt;
		std::string climov = " ClientTimeAdvance: "+ stringUtilities::padLeft(stringUtilities::unsignedToString(clientTickMove),' ',10);
		unsigned serverTickMove = serverTicks - this->activatedAt;
		std::string sermov = " ServerTimeAdvance: "+ stringUtilities::padLeft(stringUtilities::unsignedToString(serverTickMove),' ',10);
		common::Logger::instance().log(serTic);
		common::Logger::instance().log(cliTic);
		common::Logger::instance().log(sermov);
		common::Logger::instance().log(climov);
		//std::string res = serTic + cliTic + climov + sermov;
		std::string res = " RTT: " + stringUtilities::unsignedToString(this->calculateRTT(serverTickMove));
		this->setDiffDelay(0);
		if ((serverTickMove + this->calculateRTT(serverTickMove)) <= clientTickMove) {
			this->setDiffDelay(clientTickMove - serverTickMove);
			res.append(" Render?: N, Next Delay Decrease: " + stringUtilities::unsignedToString(this->getDiffDelay()));
			common::Logger::instance().log(res);
			return;
		}
		res.append(" Render?: S");
		common::Logger::instance().log(res);

	}
	//common::Logger::instance().log(serializedSimulation);
	//common::Logger::instance().log("Cliente: "+ stringUtilities::unsignedToString(static_cast<unsigned>(SDL_GetTicks())));
	for(unsigned i = 0; i < player_simulations.size(); i++) {
		this->simulate(player_simulations[i]);
	}
	/*unsigned startTime = static_cast<unsigned>(SDL_GetTicks());
	GameView::instance().update();
	unsigned updateTime = static_cast<unsigned>(SDL_GetTicks()) - startTime;
	startTime = static_cast<unsigned>(SDL_GetTicks());
	GameView::instance().render();
	unsigned renderTime = static_cast<unsigned>(SDL_GetTicks()) - startTime;
	std::string upt = " Update: "+ stringUtilities::padLeft(stringUtilities::unsignedToString(updateTime),' ',10);
	std::string ren = " Render: "+ stringUtilities::padLeft(stringUtilities::unsignedToString(renderTime),' ',10);
	common::Logger::instance().log(upt + ren);*/
}

void ModelUpdater::simulate(std::string simulation_package)
{
	std::vector<std::string> simulation_fields;
	stringUtilities::splitString(simulation_package, simulation_fields, ';');
	Personaje* personaje = GameView::instance().getPersonaje(simulation_fields[0]);
	
	if(personaje) {
		simulation_package.erase(0,simulation_package.find_first_of(';')+1);
		if (simulation_package.size() > 0)
		{
			personaje->updateFromString(simulation_package);
		}
	}
}


void ModelUpdater::syncAllPlayer(Instruction& instructionIn) {
	std::string serializedSimulation = instructionIn.getArgument(INSTRUCTION_ARGUMENT_KEY_CHARACTERS_UPDATE);

	std::vector<std::string> charactersInit;

	stringUtilities::splitString(serializedSimulation,charactersInit,':');

	for (unsigned i = 0; i < charactersInit.size(); i++) {
		this->syncPlayer(charactersInit[i]);
	}
}

void ModelUpdater::syncPlayer(std::string onePlayer) {
	std::vector<std::string> playerFields;
	stringUtilities::splitString(onePlayer, playerFields, ';');
	Personaje* personaje = GameView::instance().getPersonaje(playerFields[0]);
	
	if ( !personaje) {
		GameView::instance().newPersonaje(playerFields[0],playerFields[1]);
		personaje = GameView::instance().getPersonaje(playerFields[0]);
		//std::pair <int, int> pos = stringUtilities::stringToPairInt(playerFields[02]);
		//personaje->personajeModelo()->setPosition(pos);
		personaje->setActive(false);
	}
}

unsigned ModelUpdater::calculateRTT(unsigned lastRTT) {
	unsigned result = lastRTT - this->lastServerDelay;
	this->lastServerDelay = lastRTT;
	return result;
}

void ModelUpdater::requestSynchronize() {
	Instruction instructionOut;
	instructionOut.clear();
	instructionOut.setOpCode(OPCODE_SIMULATION_SYNCHRONIZE);
	this->getConnector().addInstruction(instructionOut);

}



// ----------------------------------- PUBLIC METHODS ------------------------------------

bool ModelUpdater::isConnected() {
	return this->connected;
}

//bool ModelUpdater::thereAreErrors() {
//	return this->errors;
//}

bool ModelUpdater::hasServerBeenReached() {
	return this->serverReached;
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

void ModelUpdater::setDiffDelay(unsigned diff) {
	this->diffDelay = diff;
}

unsigned ModelUpdater::getDiffDelay() {
	return this->diffDelay;
}
// ----------------------------------- DESTRUCTOR ----------------------------------------

ModelUpdater::~ModelUpdater() {
}