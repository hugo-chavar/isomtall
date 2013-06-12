#ifndef STATSTABLE_H
#define STATSTABLE_H

#include "Camera.h"

namespace view {

	class StatsTable {

	public:
		StatsTable();
		~StatsTable();
		bool initialize();
		void render(Camera& camera);
	private:
		SDL_Surface* getWeapon();

		SDL_Surface* sword;
		SDL_Surface* bow;
		int arrows;
		SDL_Surface* bomb;
		int bombs;
		SDL_Surface* grenade;
		int grenades;
		SDL_Surface* wand;
		SDL_Surface* shield;
		int shieldEndurance;
		SDL_Rect weaponBox;
		SDL_Rect shieldBox;
	};

}



#endif