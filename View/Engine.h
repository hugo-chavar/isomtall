#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "SDL.h"
#include "Camera.h"
#include "Stage.h"
#include "Chat.h"


class Engine {
	private:
		bool running;

		unsigned int desiredFPS;

	public:
		Engine();
	
		//TODO: Create getter/setter
		view::Stage worldView;

		//TODO: Create getter/setter
		Camera camera;

		view::Chat chat;
	
		bool isRunning();

		unsigned int getDesiredFPS();

		int execute();

		void initialize();

		void onEvent(SDL_Event* sdlEvent);

		void update();

		void render();

		void cleanUp();

		~Engine();
};

#endif //_ENGINE_H_
