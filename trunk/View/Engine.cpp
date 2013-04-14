#include "Engine.h"

#include "Surface.h"
#include "Game.h"

Engine::Engine() {
	this->running = true;
	//TODO: must be either in the config file or an in-game parameter.
	this->desiredFPS = 100;
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
 
	Game::instance().time().initializeTime();
	while(this->isRunning()) {
		frameStartedAt = SDL_GetTicks();
		Game::instance().time().updateTime();
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
	SDL_WM_GrabInput(SDL_GRAB_ON);

	//TODO: center camera on player or default tile.

	
	this->camera.initialize(800,600,32,200,60);

	worldView.initialize();

	std:pair<int,int> posPersonaje=worldView.personaje()->posicion();
	this->camera.setOffsetX(posPersonaje.first-332);
	this->camera.setOffsetY(posPersonaje.second-204);
}

void Engine::onEvent(SDL_Event* sdlEvent) {

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
			switch(sdlEvent->key.keysym.sym) {
				case SDLK_ESCAPE: {
					running = false;
					break;
				}
			}
			break;
		}
		case SDL_MOUSEBUTTONDOWN: {
            switch(sdlEvent->button.button) {
                case SDL_BUTTON_LEFT: {

					Game::instance().world().
						destino(sdlEvent->button.x,sdlEvent->button.y,this->camera.getOffsetX(),camera.getOffsetY());
                    //TODO: add event handling;
					//sdlEvent->button.x;
					//sdlEvent->button.y;
                    break;
                }
                case SDL_BUTTON_RIGHT: {
                    //TODO: add event handling;
					//sdlEvent->button.x;
					//sdlEvent->button.y;
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
}

void Engine::render() {
	SDL_FillRect(this->camera.cameraSurface,NULL,0);

	this->worldView.render(this->camera);

	SDL_Flip(this->camera.cameraSurface);
}

void Engine::cleanUp() {
	this->camera.cleanUp();

	SDL_Quit();
}

Engine::~Engine() {
}
