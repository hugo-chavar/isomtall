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
	this->desiredFPS = 100;

	//WSAData ws;
	//WSAStartup(MAKEWORD(2,2),&ws);
}

bool Engine::isRunning() {
	return this->running;
}

unsigned int Engine::getDesiredFPS() {
	return this->desiredFPS;
}

int Engine::execute() {
	float milisecondsTonextFrame = static_cast<float>(1000/this->getDesiredFPS());
	unsigned int frameStartedAt = 0;
	SDL_Event sdlEvent;

	this->initialize();

	if (!this->getLogin()->isLoggedIn())
		return EXIT_FAILURE;

	Instruction instruction;
	instruction.setOpCode(OPCODE_CONNECT_TO_CHAT);
	instruction.insertArgument(INSTRUCTION_ARGUMENT_KEY_REQUESTED_USER_ID, GameView::instance().getPlayerName());
	GameView::instance().getChat()->modelChat->getMessagesList().push_back("Connecting to chat");
	GameView::instance().getChat()->modelChat->getChatUpdater().addInstruction(instruction);

	instruction.clear();
	instruction.setOpCode(OPCODE_CONNECT_TO_SIMULATION);
	instruction.insertArgument(INSTRUCTION_ARGUMENT_KEY_REQUESTED_USER_ID, GameView::instance().getPlayerName());
	this->getModelUpdater()->addInstruction(instruction);

	while(this->isRunning()) {
		frameStartedAt = SDL_GetTicks();
		(Game::instance().time())->updateTime();
		while(SDL_PollEvent(&sdlEvent)) {
			this->onEvent(&sdlEvent);
		}
		
		GameView::instance().setConnected(_modelUpdater.isConnected());

		GameView::instance().setLoggedIn(_login.isLoggedIn());

		this->update();

		this->render();

		if (milisecondsTonextFrame >= SDL_GetTicks() - frameStartedAt)
			SDL_Delay(static_cast<unsigned int>(milisecondsTonextFrame - (SDL_GetTicks() - frameStartedAt)));
	}

	this->cleanUp();

    return 0;
}

void Engine::initialize() {
	SDL_Init(SDL_INIT_EVERYTHING);
	//SDL_WM_GrabInput(SDL_GRAB_ON);

	//descarga de archivos
	YAMLParser connectionParser;
	connectionParser.parse(CONNECTION_DIRECTORY, true);
	int serverPortNumber = connectionParser.getConfigPort();
	std::string serverIpAddress = connectionParser.getConfigIp();
	ClientUpdater clientUpdater;
	clientUpdater.setServerIp(serverIpAddress);
	clientUpdater.setServerPort(serverPortNumber);
	//clientUpdater.updateClient();

	Game::instance().configuration()->serverPort(serverPortNumber);
	Game::instance().configuration()->serverIp(serverIpAddress);

	Instruction instruction;
	instruction.setOpCode(OPCODE_LOGIN_REQUEST);
	instruction.insertArgument(INSTRUCTION_ARGUMENT_KEY_REQUESTED_USER_ID,GameView::instance().getPlayerName());
	instruction.insertArgument( INSTRUCTION_ARGUMENT_KEY_CHARACTER, GameView::instance().getPlayerCharacterId());
	this->getLogin()->getLoginUpdater().addInstruction(instruction);
	this->_login.initialize();

	Game::instance().initialize();

	this->running = GameView::instance().initialize();
	this->getModelUpdater()->startUpdating();

	//bool cameraInitialized = this->camera.initialize();
	//bool mapInitialized = false;
	//bool textInitialized = true;
	//bool chatInitialized = false;

	////Initialize SDL_ttf
	//if (TTF_Init()==-1)
	//	textInitialized = false;

	//if (cameraInitialized){
	//	mapInitialized = worldView.initialize();
	//	chatInitialized = chat.initialize(camera);
	//	worldView.setTilesInCamera(this->camera.getWidth(), this->camera.getHeight());
	//}

	////si hubo errores de inicializacion salgo
	//running = mapInitialized & cameraInitialized & textInitialized; 

	//if (running) {
	//	std::pair<int,int> posPersonaje=worldView.personaje()->posicion();
	//	this->camera.setOffsetX(static_cast<float>(posPersonaje.first-332));
	//	this->camera.setOffsetY(static_cast<float>(posPersonaje.second-204));
	//}
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
			case SDLK_f:
				{
					if (!GameView::instance().getChat()->isTyping())
						//Game::instance().personaje()->setIsActivo();
						instruction.clear();
						instruction.setOpCode(OPCODE_CLIENT_COMMAND);
						//TODO: Create an option header
						instruction.insertArgument(INSTRUCTION_ARGUMENT_KEY_COMMAND_STATE,"f");
						this->getModelUpdater()->addInstruction(instruction);
						//Game::instance().personaje()->setIsActivo(false);
					break;
				}
			case SDLK_w:
				{
					if (!GameView::instance().getChat()->isTyping())
						//Game::instance().personaje()->setIsActivo();
						instruction.clear();
						instruction.setOpCode(OPCODE_CLIENT_COMMAND);
						//TODO: Create an option header
						instruction.insertArgument(INSTRUCTION_ARGUMENT_KEY_COMMAND_STATE,"w");
						this->getModelUpdater()->addInstruction(instruction);
						//Game::instance().personaje()->setIsActivo(true);
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
						//Game::instance().personaje()->animar('a');
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
						//Game::instance().personaje()->animar('s');
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
					else
						instruction.clear();
						std::pair<int, int> tileDestino = Game::instance().world()->destination(sdlEvent->button.x,sdlEvent->button.y,GameView::instance().getCamera()->getOffsetX(),GameView::instance().getCamera()->getOffsetY());
						if ((tileDestino.first < 0)||(tileDestino.second < 0)) {
							break; }
						std::string tileDestinoStr = stringUtilities::pairIntToString(tileDestino);
						instruction.setOpCode(OPCODE_CLIENT_COMMAND);
						instruction.insertArgument(INSTRUCTION_ARGUMENT_KEY_COMMAND_DESTINATION,tileDestinoStr.c_str());
						this->getModelUpdater()->addInstruction(instruction);
						//Game::instance().world()->destino(sdlEvent->button.x,sdlEvent->button.y,this->camera.getOffsetX(),camera.getOffsetY());
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
	/*this->camera.update();
	this->worldView.update();
	this->chat.update(camera);*/
	GameView::instance().update();
}

void Engine::render() {

	GameView::instance().render();
}

void Engine::cleanUp() {
	Instruction instructionOut;

	//this->camera.cleanUp();

	GameView::instance().cleanUp();

	this->_login.cleanUp();

	//GameView::instance().getChat()->modelChat->cleanUp();

	
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