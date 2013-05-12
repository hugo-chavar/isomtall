#include "Engine.h"

#include "Surface.h"
#include "Game.h"
#include "SDL_ttf.h"

Engine::Engine() {
	this->running = true;
	//TODO: must be either in the config file or an in-game parameter.
	this->desiredFPS = 100;
	this->chat.setIsTyping(false);

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
 
	Instruction instruction;
	instruction.setOpCode(OPCODE_LOGIN_REQUEST);
	instruction.insertArgument(INSTRUCTION_ARGUMENT_KEY_REQUESTED_USER_ID,"harcoded");
	Game::instance().getLogin()->getLoginUpdater().addInstruction(instruction);
	Sleep(2000);
	if (!Game::instance().getLogin()->isLoggedIn())
		return EXIT_FAILURE;

	instruction.setOpCode(OPCODE_CONNECT_TO_CHAT);
	instruction.insertArgument(INSTRUCTION_ARGUMENT_KEY_REQUESTED_USER_ID,"harcoded");
	this->chat.modelChat->getMessagesList().push_back("Connecting to chat");
	this->chat.modelChat->getChatUpdater().addInstruction(instruction);

	while(this->isRunning()) {
		frameStartedAt = SDL_GetTicks();
		(Game::instance().time())->updateTime();
		while(SDL_PollEvent(&sdlEvent)) {
			this->onEvent(&sdlEvent);
		}

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

	string nombreJugador="1";
	Game::instance().initialize(nombreJugador);

	bool cameraInitialized = this->camera.initialize();
	bool mapInitialized = false;
	bool textInitialized = true;
	bool chatInitialized = false;

	//Initialize SDL_ttf
	if (TTF_Init()==-1)
		textInitialized = false;

	if (cameraInitialized){
		mapInitialized = worldView.initialize();
		chatInitialized = chat.initialize(camera);
		worldView.setTilesInCamera(this->camera.getWidth(), this->camera.getHeight());
	}

	//si hubo errores de inicializacion salgo
	running = mapInitialized & cameraInitialized & textInitialized; 

	if (running) {
		std::pair<int,int> posPersonaje=worldView.personaje()->posicion();
		this->camera.setOffsetX(static_cast<float>(posPersonaje.first-332));
		this->camera.setOffsetY(static_cast<float>(posPersonaje.second-204));
	}
}

void Engine::onEvent(SDL_Event* sdlEvent) {
	if (chat.isTyping()) {
		chat.type(sdlEvent);
		if ((sdlEvent->type==SDL_KEYDOWN) && (sdlEvent->key.keysym.sym==SDLK_RETURN)) {
			// ENVIAR MENSAJE...
			chat.sendMessage();
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
			case SDLK_w:
				{
					if (!chat.isTyping())
						Game::instance().personaje()->setIsActivo();
					break;
				}
				case SDLK_a:
				{
					if (!chat.isTyping())
						Game::instance().personaje()->animar('a');
					break;
				}
			default:
				break;
			}
		}
		case SDL_MOUSEBUTTONDOWN: {
			switch(sdlEvent->button.button) {
				case SDL_BUTTON_LEFT: {
					if (chat.isClosing(sdlEvent->button.x+camera.getOffsetX(), sdlEvent->button.y+camera.getOffsetY()))
						chat.setIsTyping(false);
					else
						(Game::instance().world())->
							destino(sdlEvent->button.x,sdlEvent->button.y,this->camera.getOffsetX(),camera.getOffsetY());
					//TODO: add event handling;
					//sdlEvent->button.x;
					//sdlEvent->button.y;
					break;
				}
				case SDL_BUTTON_RIGHT: {
					string To="";
					if(Game::instance().world()->isThereAChar(To,sdlEvent->button.x,sdlEvent->button.y,this->camera.getOffsetX(),camera.getOffsetY()))
					{
					chat.setTo(To);
					chat.setIsTyping(true);
					}
					break;
				}
			}
			break;
		}
	}
	
}

void Engine::update() {
	this->camera.update();
	this->worldView.update();
	this->chat.update(camera);
}

void Engine::render() {
	SDL_FillRect(this->camera.cameraSurface,NULL,0);

	this->worldView.render(this->camera);

	if (chat.isTyping())
		this->chat.render(this->camera);

	SDL_Flip(this->camera.cameraSurface);
}

void Engine::cleanUp() {
	this->camera.cleanUp();

	Game::instance().getLogin()->cleanUp();

	this->chat.modelChat->cleanUp();

	SDL_Quit();
}

Engine::~Engine() {
	WSACleanup();
}
