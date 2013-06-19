#ifndef STATSTABLE_H
#define STATSTABLE_H

#include "Camera.h"
#include "Personaje.h"

namespace view {

	class StatsTable {

	public:
		StatsTable();
		~StatsTable();
		void update(Personaje* personaje);
		bool initialize();
		void render(Camera& camera);
		void setFont(TTF_Font* font);
	private:
		SDL_Surface* getWeapon();
		SDL_Rect generateInfo(std::string info, SDL_Surface* &surface);
		void setWeaponFalse();
		bool canGenerateWeaponInfo();

		bool weapons [5];
		SDL_Surface* sword;
		SDL_Surface* bow;
		SDL_Surface* bomb;
		SDL_Surface* handGrenade;
		SDL_Surface* wand;
		SDL_Surface* shield;
		int shieldEndurance;
		SDL_Surface* ammo;
		int ammunition;
		SDL_Surface* shieldDur;
		SDL_Surface* spell;
		SDL_Surface* spellName;
		std::string spellId;
		SDL_Rect weaponBox;
		SDL_Rect shieldBox;
		SDL_Rect spellBox;
		TTF_Font* font;
	};

}



#endif