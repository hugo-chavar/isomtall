#include "StatsTable.h"
#include "../Libraries/SDL-1.2.15/include/SDL_image.h"
#include <string.h>
#include <string>
#include "../Common/stringUtilities.h"
#include "PersonajeConstantes.h"

using namespace view;

StatsTable::StatsTable() {
	this->shield = NULL;
	this->sword = NULL;
	this->bomb = NULL;
	this->bow = NULL;
	this->handGrenade = NULL;
	this->wand = NULL;
	this->ammunition = 0;
	this->shieldEndurance = 0;
	this->ammo = NULL;
	this->shieldDur = NULL;
	this->spell = NULL;
	this->spellName = NULL;
	this->spellId = "";
	this->setWeaponFalse();
}

void StatsTable::setWeaponFalse() {
	this->weapons[0] = false;
	this->weapons[1] = false;
	this->weapons[2] = false;
	this->weapons[3] = false;
}

//TODO: Mover esto a un lugar general, ver ChatView.h
SDL_Surface *loadSurface(std::string filename)
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load(filename.c_str());

    //If the image loaded
    if(loadedImage!=NULL)
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormat(loadedImage);

        //Free the old image
        SDL_FreeSurface(loadedImage);

        //If the image was optimized just fine
        if(optimizedImage!=NULL)
        {
            //Map the color key
            Uint32 colorkey = SDL_MapRGB(optimizedImage->format, 0xFF, 0, 0xFF);

            //Set all pixels of color R 0, G 0xFF, B 0xFF to be transparent
            SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorkey);
        }
    }

    //Return the optimized image
    return optimizedImage;
}

bool StatsTable::initialize() {
	sword = loadSurface("../Images/sword.png");
	bow = loadSurface("../Images/BowIcon.png");
	handGrenade = loadSurface("../Images/granada/01N.png");
	bomb = loadSurface("../Images/bombIcon.png");
	wand = loadSurface("../Images/sword.png");
	shield = loadSurface("../Images/Shield.png");
	spell = loadSurface("../Images/Spell.png");
	if ((sword == NULL) || (bow == NULL) || (handGrenade == NULL) || (wand == NULL) || (bomb == NULL) || (shield == NULL) || (spell == NULL)) {
		return false;
	}
	weaponBox.w = static_cast<Uint16>(sword->w);
	weaponBox.h = static_cast<Uint16>(sword->h);
	shieldBox.h = static_cast<Uint16>(shield->h);
	shieldBox.w = static_cast<Uint16>(shield->w);
	spellBox.h = static_cast<Uint16>(spell->h);
	spellBox.w = static_cast<Uint16>(spell->w);
	return true;
}

bool StatsTable::canGenerateWeaponInfo() {
	return (weapons[1] || weapons[3]);
}

void StatsTable::update(Personaje* personaje) {
	shieldEndurance = (int) (personaje->getShieldResistance());
	spellId = personaje->getSpellActual();
	this->setWeaponFalse();
	switch (personaje->getSelectedWeapon()) {
	case WEAPON_SWORD: {
						weapons[0] = true;
						break;
					   }
	case WEAPON_BOW: {
						weapons[1] = true;
						this->ammunition = personaje->getWeapons()[WEAPON_BOW]->getAmmo();
						break;
					 }
	case WEAPON_ICE_INCANTATOR: {
									weapons[2] = true;
									break;
								}
	case WEAPON_HAND_GRENADE: {
								weapons[3] = true;
								this->ammunition = personaje->getWeapons()[WEAPON_HAND_GRENADE]->getAmmo();
								break;
							  }
	default: break;
	}
}

SDL_Rect StatsTable::generateInfo(std::string info, SDL_Surface* &surface) {
	SDL_Rect retValue;
	
	if (surface != NULL) {
		SDL_FreeSurface(surface);
		surface = NULL;
	}
	surface = TTF_RenderText_Blended(this->font, info.c_str(), Camera::WHITE_COLOR);
	retValue.h = (Uint16) surface->h;
	retValue.w = (Uint16) surface->w;
	return retValue;
}

void StatsTable::setFont(TTF_Font* font) {
	this->font = font;
}

SDL_Surface* StatsTable::getWeapon() {
	if (weapons[1] == true) {
		return bow;
	}
	if (weapons[2] == true) {
		return wand;
	}
	if (weapons[3] == true) {
		return handGrenade;
	}
	return sword;
}

void StatsTable::render(Camera &camera) {
	SDL_Rect shieldInfoBox;
	SDL_Rect weaponInfoBox;
	SDL_Rect spellInfoBox;

	//TODO: ver de optimizar esto
	weaponBox.x = static_cast<Uint16>(camera.getOffsetX() + 10);
	weaponBox.y = static_cast<Uint16>(camera.getOffsetY() + 50);
	shieldBox.x = weaponBox.x;
	shieldBox.y = weaponBox.y + weaponBox.h;
	spellBox.x = weaponBox.x;
	spellBox.y = shieldBox.y + shieldBox.h;
	camera.render (weaponBox, getWeapon());
	if (this->canGenerateWeaponInfo()) {
		weaponInfoBox = this->generateInfo(stringUtilities::intToString(this->ammunition), this->ammo);
		weaponInfoBox.y = weaponBox.y;
		weaponInfoBox.x = weaponBox.x + weaponBox.w;
		camera.render(weaponInfoBox, ammo);
	}
	if (shieldEndurance > 0) {
		camera.render (shieldBox, shield);
		shieldInfoBox = this->generateInfo(stringUtilities::intToString(shieldEndurance), shieldDur);
		shieldInfoBox.y = shieldBox.y;
		shieldInfoBox.x = shieldBox.x + shieldBox.w;
		camera.render(shieldInfoBox, shieldDur);
	}
	if (spellId != "") {
		camera.render (spellBox, spell);
		spellInfoBox = this->generateInfo(spellId, spellName);
		spellInfoBox.y = spellBox.y;
		spellInfoBox.x = spellBox.x + spellBox.w;
		camera.render(spellInfoBox, spellName);
	}
}

StatsTable::~StatsTable() {
	if (shield != NULL) {
		SDL_FreeSurface(shield);
		shield = NULL;
	}
	if (sword != NULL) {
		SDL_FreeSurface(sword);
		sword = NULL;
	}
	if (bomb != NULL) {
		SDL_FreeSurface(bomb);
		bomb = NULL;
	}
	if (handGrenade != NULL) {
		SDL_FreeSurface(handGrenade);
		handGrenade = NULL;
	}
	if (bow != NULL) {
		SDL_FreeSurface(bow);
		bow = NULL;
	}
	if (wand != NULL) {
		SDL_FreeSurface(wand);
		wand = NULL;
	}
	if (shieldDur != NULL) {
		SDL_FreeSurface(shieldDur);
		shieldDur = NULL;
	}
	if (ammo != NULL) {
		SDL_FreeSurface(ammo);
		ammo = NULL;
	}
	if (spell != NULL) {
		SDL_FreeSurface(spell);
		spell = NULL;
	}
	if (spellName != NULL) {
		SDL_FreeSurface(spellName);
		spellName = NULL;
	}
}