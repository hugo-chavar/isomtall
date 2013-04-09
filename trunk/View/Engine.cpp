#include "Engine.h"

#include "Surface.h"
#include "TimeManager.h"

Engine::Engine() {
	this->running = true;
	//TODO: must be either in the config file or an in-game parameter.
	this->desiredFPS = 50;
}

bool Engine::isRunning() {
	return this->running;
}

unsigned int Engine::getDesiredFPS() {
	return this->desiredFPS;
}

int Engine::execute() {
	double milisecondsTonextFrame = 1000.0/this->getDesiredFPS();
	unsigned int frameStartedAt = 0;
	SDL_Event sdlEvent;

	this->initialize();
 
	model::TimeManager::initializeTime();
	while(this->isRunning()) {
		frameStartedAt = SDL_GetTicks();
		model::TimeManager::updateTime();
		while(SDL_PollEvent(&sdlEvent)) {
			this->onEvent(&sdlEvent);
		}

		this->update();

		this->render();

		if (milisecondsTonextFrame >= SDL_GetTicks() - frameStartedAt)
			SDL_Delay(int(milisecondsTonextFrame) - (SDL_GetTicks() - frameStartedAt));
	}

	this->cleanUp();

    return 0;
}

void Engine::initialize() {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_WM_GrabInput(SDL_GRAB_ON);

	//this->camera.initialize(800,600,32,300,50,(this->worldView.worldModel.tileWidth() * this->worldView.worldModel.width() / 2) - 400,(this->worldView.worldModel.tileHeight() * this->worldView.worldModel.height() / 2) - 300);
	this->camera.initialize(800,600,24,200,50,0,0);

	worldView.initialize();

	this->loadLevel();
}

void Engine::onEvent(SDL_Event* sdlEvent) {

	if(sdlEvent->type == SDL_QUIT) {
		running = false;
	}

	if ( (sdlEvent->type == SDL_KEYDOWN) && (sdlEvent->key.keysym.sym) ) {
		running = false;
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

void Engine::loadLevel() {
	//TODO: Mock harcoded function.
	TileView* tile = NULL;
	SDL_Surface* tileSet = NULL;
	unsigned int tileSetOffsetX = 0;
	unsigned int tileSetOffsetY = 0;
	unsigned int tileCenterX = 0;
	unsigned int tileCenterY = 0;

//	this->getScenario().mapSurface = SDL_CreateRGBSurface(SDL_SWSURFACE,this->getScenario().getDimentions()*this->getScenario().getTileWidth(),this->getScenario().getDimentions()*this->getScenario().getTileHeight(),32,0,0,0,0);

	tileSet = Surface::loadFromBMP("../images/tiles.bmp");

	for (unsigned int i = 0; i < this->worldView.worldModel.width() * this->worldView.worldModel.height(); i++) {
		tile = new TileView(tileSet,tileSetOffsetX,tileSetOffsetY,this->worldView.worldModel.tileHeight(),this->worldView.worldModel.tileWidth(),0,tileCenterX,tileCenterY);
		this->worldView.addTile(tile);
	}

	SDL_FreeSurface(tileSet);
}

Engine::~Engine() {
}
