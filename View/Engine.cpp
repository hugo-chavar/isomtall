#include "Engine.h"

#include "Surface.h"
#include "Game.h"
#include "GameView.h"
#include "SDL_ttf.h"
#include "Instruction.h"
#include "../Common/StringUtilities.h"
#include "../Model/OpcionesJuego.h"
#include "Logger.h"


Engine::Engine() {
	//this->running = true;
	//TODO: must be either in the config file or an in-game parameter.
	//this->desiredFPS = 20;
	this->desiredFPS = 60;
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

}
//
//bool Engine::isRunning() {
//	return this->running;
//}

Uint32 Engine::getDesiredFPS() {
	return this->desiredFPS;
}

int Engine::execute() {
	Uint32 milisecondsTonextFrame = 1000/this->getDesiredFPS();
	Uint32 frameStartedAt = 0;
	SDL_Event sdlEvent;

	this->initialize();

	while(GameView::instance().getStatus() != STATUS_EXIT) {
		frameStartedAt = SDL_GetTicks();
		(Game::instance().getTimer())->updateTime();
		while(SDL_PollEvent(&sdlEvent)) {
			if (GameView::instance().isSinglePlayerGame()) {
				this->onSingleplayerEvent(&sdlEvent);
			} else {
				this->onMultiplayerEvent(&sdlEvent);
			}
		}
		this->update();
		this->render();

		if (milisecondsTonextFrame >= SDL_GetTicks() - (frameStartedAt /* - _modelUpdater.getDiffDelay()*/)) {
			//common::Logger::instance().log("---- WAITING FOR " + stringUtilities::unsignedToString(milisecondsTonextFrame - (SDL_GetTicks() - frameStartedAt)) + "MILISECONDS AT: "+ stringUtilities::unsignedToString(SDL_GetTicks()));
			SDL_Delay(milisecondsTonextFrame - (SDL_GetTicks() - frameStartedAt));
			//common::Logger::instance().log("---- FINISHED WAITING AT: "+ stringUtilities::unsignedToString(SDL_GetTicks()));
		}
	}
	Logger::instance().log("Exiting..");
	this->cleanUp();

    return 0;
}

void Engine::initialize() {
	GameView::instance().setStatus(STATUS_START_SCREEN);
}

void Engine::onMultiplayerEvent(SDL_Event* sdlEvent) {

	if (GameView::instance().showingMenu()) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		GameView::instance().getGameMenu()->updateMouse(x, y);
	}
		

	Instruction instruction;
	
	if (GameView::instance().getChat()->isTyping()) {
		GameView::instance().getChat()->type(sdlEvent);
		if ((sdlEvent->type == SDL_KEYDOWN) && (sdlEvent->key.keysym.sym == SDLK_RETURN)) {
			GameView::instance().getChat()->sendMessage();
		}
	}

	switch(sdlEvent->type) {
		case SDL_QUIT: {
			//running = false;
			GameView::instance().setStatus(STATUS_EXIT);
			break;
		}
		case SDL_KEYDOWN: {
			switch(sdlEvent->key.keysym.sym)
			{
			case SDLK_ESCAPE: 
				{
					if (GameView::instance().showingMenu() && GameView::instance().getGameMenu()->displayingNotification()) {
						if (GameView::instance().isGameOver()) {
							instruction.setOpCode(OPCODE_CLIENT_COMMAND);
							instruction.insertArgument(INSTRUCTION_ARGUMENT_KEY_COMMAND_RESTART_GAME,"1");
							GameView::instance().getModelUpdater()->addInstruction(instruction);
							GameView::instance().setStatus(STATUS_RESTART_GAME);
							GameView::instance().getGameMenu()->setDisplayNotification(false);
							GameView::instance().getGameMenu()->setDisplayBackground(true);
							GameView::instance().getGameMenu()->showButtons();
						} else {
							GameView::instance().setStatus(STATUS_START_SCREEN);
							GameView::instance().getGameMenu()->setDisplayNotification(false);
						}
					} else {
						//running = false;
						GameView::instance().setStatus(STATUS_EXIT);
					}
					break;
				}
			case SDLK_a:
				{
					if (!GameView::instance().getChat()->isTyping())
					{
						GameView::instance().getCamera()->setVibrating();
						//instruction.clear();
						//instruction.setOpCode(OPCODE_CLIENT_COMMAND);
						////TODO: Create an option header
						//string opcion_caracter;
						//opcion_caracter.push_back(OPCION_ATACAR);
						//instruction.insertArgument(INSTRUCTION_ARGUMENT_KEY_COMMAND_STATE,opcion_caracter);
						//GameView::instance().getModelUpdater()->addInstruction(instruction);
					}
					break;
				}
			case SDLK_u:
				{
					if (!GameView::instance().getChat()->isTyping())
					{
						instruction.clear();
						instruction.setOpCode(OPCODE_CLIENT_COMMAND);
						//TODO: Create an option header
						string opcion_caracter;
						opcion_caracter.push_back(OPCION_MAGIA);
						instruction.insertArgument(INSTRUCTION_ARGUMENT_KEY_COMMAND_STATE,opcion_caracter);
						GameView::instance().getModelUpdater()->addInstruction(instruction);
					}
					break;
				}
				case SDLK_i:
				{
					if (!GameView::instance().getChat()->isTyping())
					{
						instruction.clear();
						instruction.setOpCode(OPCODE_CLIENT_COMMAND);
						//TODO: Create an option header
						string opcion_caracter;
						opcion_caracter.push_back(OPCION_TERMINAR_MAGIA);
						instruction.insertArgument(INSTRUCTION_ARGUMENT_KEY_COMMAND_STATE,opcion_caracter);
						GameView::instance().getModelUpdater()->addInstruction(instruction);
					}
					break;
				}
				case SDLK_w:
				{
					if (!GameView::instance().getChat()->isTyping())
					{
						instruction.clear();
						instruction.setOpCode(OPCODE_CLIENT_COMMAND);
						//TODO: Create an option header
						string opcion_caracter;
						opcion_caracter.push_back(OPCION_CAMBIAR_ARMA);
						instruction.insertArgument(INSTRUCTION_ARGUMENT_KEY_COMMAND_STATE,opcion_caracter);
						GameView::instance().getModelUpdater()->addInstruction(instruction);
					}
					break;
				}
			case SDLK_m:
				{
					if (!GameView::instance().getChat()->isTyping())
					{
						GameView::instance().getGameSounds().toggleBackgroundMusic();
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
					if (GameView::instance().getStatus() == STATUS_START_SCREEN) {
						unsigned value = GameView::instance().getGameMenu()->select(sdlEvent->button.x, sdlEvent->button.y);
						if (value != STATUS_BAD_CLICK)
							GameView::instance().setStatus(value);
						break;
					}
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
						GameView::instance().getModelUpdater()->addInstruction(instruction);
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

void Engine::onSingleplayerEvent(SDL_Event* sdlEvent) {

	if (GameView::instance().showingMenu()) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		GameView::instance().getGameMenu()->updateMouse(x, y);
	}
		

	/*Instruction instruction;
	
	if (GameView::instance().getChat()->isTyping()) {
		GameView::instance().getChat()->type(sdlEvent);
		if ((sdlEvent->type == SDL_KEYDOWN) && (sdlEvent->key.keysym.sym == SDLK_RETURN)) {
			GameView::instance().getChat()->sendMessage();
		}
	}*/

	switch(sdlEvent->type) {
		case SDL_QUIT: {
			//running = false;
			GameView::instance().setStatus(STATUS_EXIT);
			break;
		}
		case SDL_KEYDOWN: {
			switch(sdlEvent->key.keysym.sym)
			{
			case SDLK_ESCAPE: 
				{
					if (GameView::instance().showingMenu() && GameView::instance().getGameMenu()->displayingNotification()) {
						if (GameView::instance().isGameOver()) {
							int stageNumber = Game::instance().getStageNumber() + 1;
							if (static_cast<unsigned>(stageNumber) >= Game::instance().yParser.vStages().size())
								stageNumber = 0;
							Game::instance().setStageNumber(stageNumber);
							Game::instance().restart();
							GameView::instance().restart();
							GameView::instance().setStatus(STATUS_SIMULATION_PLAYING_SINGLEPLAYER);
						} else {
							GameView::instance().setStatus(STATUS_START_SCREEN);
							GameView::instance().getGameMenu()->setDisplayNotification(false);
						}
					} else {
						//running = false;
						GameView::instance().setStatus(STATUS_EXIT);
					}
					break;
				}
			case SDLK_a:
				{
					/*if (!GameView::instance().getChat()->isTyping())
					{*/
						GameView::instance().getCamera()->setVibrating();
						//instruction.clear();
						//instruction.setOpCode(OPCODE_CLIENT_COMMAND);
						////TODO: Create an option header
						//string opcion_caracter;
						//opcion_caracter.push_back(OPCION_ATACAR);
						//instruction.insertArgument(INSTRUCTION_ARGUMENT_KEY_COMMAND_STATE,opcion_caracter);
						//GameView::instance().getModelUpdater()->addInstruction(instruction);
					/*}*/
					break;
				}
				case SDLK_u:
				{
					if (!GameView::instance().getChat()->isTyping())
					{
						GameView::instance().getMyPersonaje()->processKeyCommand(OPCION_MAGIA);
					}
					break;
				}
				case SDLK_i:
				{
					if (!GameView::instance().getChat()->isTyping())
					{
						GameView::instance().getMyPersonaje()->processKeyCommand(OPCION_TERMINAR_MAGIA);
					}
					break;
				}
				case SDLK_w:
				{
					if (!GameView::instance().getChat()->isTyping())
					{
						GameView::instance().getMyPersonaje()->processKeyCommand(OPCION_CAMBIAR_ARMA);
					}
					break;
				}
			case SDLK_m:
				{
					/*if (!GameView::instance().getChat()->isTyping())
					{*/
						GameView::instance().getGameSounds().toggleBackgroundMusic();
					//}
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
					if (GameView::instance().getStatus() == STATUS_START_SCREEN) {
						unsigned value = GameView::instance().getGameMenu()->select(sdlEvent->button.x, sdlEvent->button.y);
						if (value != STATUS_BAD_CLICK)
							GameView::instance().setStatus(value);
						break;
					}
					//if (GameView::instance().getChat()->isClosing(sdlEvent->button.x+GameView::instance().getCamera()->getOffsetX(), sdlEvent->button.y+GameView::instance().getCamera()->getOffsetY()))
						//GameView::instance().getChat()->setIsTyping(false);
					else {
						//instruction.clear();
						std::pair<int, int> tileDestino = Game::instance().world()->destination(sdlEvent->button.x,sdlEvent->button.y,GameView::instance().getCamera()->getOffsetX(),GameView::instance().getCamera()->getOffsetY());
						if (!(Game::instance().world())->isInsideWorld(tileDestino)) {
							break; 
						}
						GameView::instance().getMyPersonaje()->setDestino(tileDestino.first, tileDestino.second);
						/*std::string tileDestinoStr = stringUtilities::pairIntToString(tileDestino);
						instruction.setOpCode(OPCODE_CLIENT_COMMAND);
						instruction.insertArgument(INSTRUCTION_ARGUMENT_KEY_COMMAND_DESTINATION,tileDestinoStr);
						GameView::instance().getModelUpdater()->addInstruction(instruction);*/
					}
					break;
				}
				/*case SDL_BUTTON_RIGHT: {
					string To="";
					if(GameView::instance().isThereAChar(To,sdlEvent->button.x,sdlEvent->button.y,GameView::instance().getCamera()->getOffsetX(),GameView::instance().getCamera()->getOffsetY()))
					{
						GameView::instance().getChat()->setTo(To);
						GameView::instance().getChat()->setIsTyping(true);
					}
					break;
				}*/
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
	Logger::instance().log("Engine::cleanUp()");
	//Instruction instructionOut;

	GameView::instance().cleanUp();
	Logger::instance().log("GameView::instance().cleanUp();");

	//this->_login.cleanUp();


	//if (this->getModelUpdater()->isConnected()) {
	//	instructionOut.setOpCode(OPCODE_DISCONNECT_FROM_SIMULATION);
	//	this->getModelUpdater()->addInstruction(instructionOut);
	//	this->getModelUpdater()->stopUpdating(false);
	//}

}

Engine::~Engine() {
	Logger::instance().log("Engine::~Engine()");
	WSACleanup();
	Logger::instance().log("WSACleanup()");
	TTF_Quit();
	Logger::instance().log("TTF_Quit()");
	SDL_Quit();
	Logger::instance().log("SDL_Quit()");
}
//
//ModelUpdater* Engine::getModelUpdater() {
//	return &this->_modelUpdater;
//}
//
//model::Login* Engine::getLogin() {
//	return &_login;
//}