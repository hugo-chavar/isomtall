#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "SDL.h"
#include "Camera.h"
#include "Stage.h"
#include "Chat.h"
#include "ModelUpdater.h"
#include "Login.h"

class Engine {
	private:
		bool running;

		Uint32 desiredFPS;

		ModelUpdater _modelUpdater;

		model::Login _login;

	public:
		Engine();
	
		bool isRunning();

		Uint32 getDesiredFPS();

		int execute();

		void initialize();

		void onEvent(SDL_Event* sdlEvent);

		void update();

		void render();

		void cleanUp();

		~Engine();

		ModelUpdater* getModelUpdater();

		model::Login* getLogin();
};

#endif //_ENGINE_H_
