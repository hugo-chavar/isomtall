#include "Engine.h"

#include "Surface.h"
#include "Game.h"
#include "GameView.h"
#include "SDL_ttf.h"
#include "Instruction.h"
#include "../Common/stringUtilities.h"
#include "../Model/OpcionesJuego.h"

Engine::Engine() {
	this->running = true;
	//TODO: must be either in the config file or an in-game parameter.
	this->desiredFPS = 20;

}

bool Engine::isRunning() {
	return this->running;
}

Uint32 Engine::getDesiredFPS() {
	return this->desiredFPS;
}

int Engine::execute() {
	Uint32 milisecondsTonextFrame = 1000/this->getDesiredFPS();
	Uint32 frameStartedAt = 0;
	SDL_Event sdlEvent;

	this->initialize();

	if ((GameView::instance().getStatus() != STATUS_LOGIN_FAILED)&&(GameView::instance().getStatus() != STATUS_SIMULATION_CONNECTION_LOST)&&(GameView::instance().getStatus() != STATUS_SERVER_UNREACHEABLE)) {
		Instruction instruction;
		instruction.setOpCode(OPCODE_CONNECT_TO_CHAT);
		instruction.insertArgument(INSTRUCTION_ARGUMENT_KEY_REQUESTED_USER_ID, GameView::instance().getPlayerName());
		GameView::instance().getChat()->modelChat->getMessagesList().push_back("Connecting to chat");
		GameView::instance().getChat()->modelChat->getChatUpdater().addInstruction(instruction);

		instruction.clear();
		instruction.setOpCode(OPCODE_CONNECT_TO_SIMULATION);
		instruction.insertArgument(INSTRUCTION_ARGUMENT_KEY_REQUESTED_USER_ID, GameView::instance().getPlayerName());
		this->getModelUpdater()->addInstruction(instruction);
		
	}
	while(this->isRunning()) {
		frameStartedAt = SDL_GetTicks();
		(Game::instance().time())->updateTime();
		while(SDL_PollEvent(&sdlEvent)) {
			this->onEvent(&sdlEvent);
		}
		
		//if ( !_modelUpdater.isConnected()) {
		//	/*	GameView::instance().setStatus(STATUS_SIMULATION_CONNECTED);
		//	} else */
		//	if ((GameView::instance().getStatus() == STATUS_SIMULATION_CONNECTED)&&(_modelUpdater.thereAreErrors())) {
		//		GameView::instance().setStatus(STATUS_SIMULATION_CONNECTION_LOST);
		//	}
		//}

		this->update();

		this->render();

		if (milisecondsTonextFrame >= SDL_GetTicks() - (frameStartedAt - _modelUpdater.getDiffDelay()))
			SDL_Delay(milisecondsTonextFrame - (SDL_GetTicks() - frameStartedAt));
	}

	this->cleanUp();

    return 0;
}

void Engine::initialize() {
	SDL_Init(SDL_INIT_EVERYTHING);
	//SDL_WM_GrabInput(SDL_GRAB_ON);
	GameView::instance().setStatus(STATUS_UPDATING_FILES);
	//descarga de archivos
	YAMLParser connectionParser;
	connectionParser.parse(CONNECTION_DIRECTORY, true);
	int serverPortNumber = connectionParser.getConfigPort();
	std::string serverIpAddress = connectionParser.getConfigIp();
	ClientUpdater clientUpdater;
	clientUpdater.setServerIp(serverIpAddress);
	clientUpdater.setServerPort(serverPortNumber);
	clientUpdater.updateClient();

	if (GameView::instance().getStatus() == STATUS_FILES_UPDATED_OK) {

		Game::instance().configuration()->serverPort(serverPortNumber);
		Game::instance().configuration()->serverIp(serverIpAddress);

		Instruction instruction;
		instruction.setOpCode(OPCODE_LOGIN_REQUEST);
		instruction.insertArgument(INSTRUCTION_ARGUMENT_KEY_REQUESTED_USER_ID,GameView::instance().getPlayerName());
		instruction.insertArgument( INSTRUCTION_ARGUMENT_KEY_CHARACTER, GameView::instance().getPlayerCharacterId());
		this->getLogin()->getLoginUpdater().addInstruction(instruction);
		this->_login.initialize();
		this->getModelUpdater()->startUpdating();
		Game::instance().initialize();
	}

	GameView::instance().initialize();

}

void Engine::onEvent(SDL_Event* sdlEvent) {
	Instruction instruction;
	
	if (GameView::instance().getChat()->isTyping()) {
		GameView::instance().getChat()->type(sdlEvent);
		if ((sdlEvent->type==SDL_KEYDOWN) && (sdlEvent->key.keysym.sym==SDLK_RETURN)) {
			// ENVIAR MENSAJE...
			GameView::instance().getChat()->sendMessage();
		}
	}

	if(sdlEvent->type == SDL_QUIT) {
		running = false;
	}

	if ( (sdlEvent->type == SDL_KEYDOWN) && (sdlEvent->key.keysym.sym == SDLK_ESCAPE) ) {
		running = false;
	}

	switch(sdlEvent->type) {
		case SDL_QUIT: {
			running = false;
			break;
		}
		case SDL_KEYDOWN: {
			switch(sdlEvent->key.keysym.sym)
			{
			case SDLK_ESCAPE: 
				{
					running = false;
					break;
				}
			case SDLK_a:
				{
					if (!GameView::instance().getChat()->isTyping())
					{
						instruction.clear();
						instruction.setOpCode(OPCODE_CLIENT_COMMAND);
						//TODO: Create an option header
						string opcion_caracter;
						opcion_caracter.push_back(OPCION_ATACAR);
						instruction.insertArgument(INSTRUCTION_ARGUMENT_KEY_COMMAND_STATE,opcion_caracter);
						this->getModelUpdater()->addInstruction(instruction);
					}
					break;
				}
			case SDLK_s:
				{
					if (!GameView::instance().getChat()->isTyping())
					{
						instruction.clear();
						instruction.setOpCode(OPCODE_CLIENT_COMMAND);
						//TODO: Create an option header
						string opcion_caracter;
						opcion_caracter.push_back(OPCION_DEFENDER);
						instruction.insertArgument(INSTRUCTION_ARGUMENT_KEY_COMMAND_STATE,opcion_caracter);
						this->getModelUpdater()->addInstruction(instruction);
					}
					break;
				}
			default:
				break;
			}
			break;
		}
		case SDL_MOUSEBUTTONDOWN: {
			switch(sdlEvent->button.button) {
				case SDL_BUTTON_LEFT: {
					if (GameView::instance().getChat()->isClosing(sdlEvent->button.x+GameView::instance().getCamera()->getOffsetX(), sdlEvent->button.y+GameView::instance().getCamera()->getOffsetY()))
						GameView::instance().getChat()->setIsTyping(false);
					else {
						instruction.clear();
						std::pair<int, int> tileDestino = Game::instance().world()->destination(sdlEvent->button.x,sdlEvent->button.y,GameView::instance().getCamera()->getOffsetX(),GameView::instance().getCamera()->getOffsetY());
						if (!(Game::instance().world())->isInsideWorld(tileDestino)) {
							break; 
						}
						std::string tileDestinoStr = stringUtilities::pairIntToString(tileDestino);
						instruction.setOpCode(OPCODE_CLIENT_COMMAND);
						instruction.insertArgument(INSTRUCTION_ARGUMENT_KEY_COMMAND_DESTINATION,tileDestinoStr);
						this->getModelUpdater()->addInstruction(instruction);
					}
					break;
				}
				case SDL_BUTTON_RIGHT: {
					string To="";
					if(GameView::instance().isThereAChar(To,sdlEvent->button.x,sdlEvent->button.y,GameView::instance().getCamera()->getOffsetX(),GameView::instance().getCamera()->getOffsetY()))
					{
						GameView::instance().getChat()->setTo(To);
						GameView::instance().getChat()->setIsTyping(true);
					}
					break;
				}
			}
			break;
		}
	}
	
}

void Engine::update() {
	GameView::instance().update();
}

void Engine::render() {

	GameView::instance().render();
}

void Engine::cleanUp() {
	Instruction instructionOut;

	GameView::instance().cleanUp();

	this->_login.cleanUp();


	if (this->getModelUpdater()->isConnected()) {
		instructionOut.setOpCode(OPCODE_DISCONNECT_FROM_SIMULATION);
		this->getModelUpdater()->addInstruction(instructionOut);
		this->getModelUpdater()->stopUpdating(false);
	}

	SDL_Quit();
}

Engine::~Engine() {
	WSACleanup();
}

ModelUpdater* Engine::getModelUpdater() {
	return &this->_modelUpdater;
}

model::Login* Engine::getLogin() {
	return &_login;
}