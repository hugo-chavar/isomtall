#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "SDL.h"
#include "Camera.h"
#include "World.h"
//#include "Stage.h"

using namespace view;
using namespace model;

class Engine {
	private:
		bool running;

		unsigned int desiredFPS;

	public:
		Engine();
	
		//TODO: Create getter/setter
		view::World worldView;

		//TODO: Create getter/setter
		model::Camera camera;


		bool isRunning();

		unsigned int getDesiredFPS();

		int execute();

		void initialize();

		void onEvent(SDL_Event* sdlEvent);

		void update();

		void render();

		void cleanUp();

		void loadLevel();

		~Engine();
};

#endif //_ENGINE_H_
