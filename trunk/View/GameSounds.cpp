#include "GameSounds.h"

GameSounds::GameSounds() {
	this->backgroundMusic = NULL;
}

Mix_Music* GameSounds::getBackgroundMusic() {
	return this->backgroundMusic;
}

void GameSounds::setBackgroundMusic(Mix_Music* backgroundMusic) {
	this->backgroundMusic = backgroundMusic;
}

std::vector<Mix_Chunk*>& GameSounds::getSoundEffects() {
	return this->soundsEffects;
}

void GameSounds::initialize() {
	//SDL_Mixer Initialization
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,4096);

	//Load background music
	this->setBackgroundMusic(Mix_LoadMUS("../Music/music.ogg"));

	//Load sound effects
	this->getSoundEffects().push_back(Mix_LoadWAV("../Sounds/arrow.wav"));
	this->getSoundEffects().push_back(Mix_LoadWAV("../Sounds/attackOnshield.wav"));
	this->getSoundEffects().push_back(Mix_LoadWAV("../Sounds/attackOnWood.wav"));
	this->getSoundEffects().push_back(Mix_LoadWAV("../Sounds/openBottle.wav"));
	this->getSoundEffects().push_back(Mix_LoadWAV("../Sounds/eatItem.wav"));
	this->getSoundEffects().push_back(Mix_LoadWAV("../Sounds/regeneracion.wav"));
	this->getSoundEffects().push_back(Mix_LoadWAV("../Sounds/explosion.wav"));
	this->getSoundEffects().push_back(Mix_LoadWAV("../Sounds/magic2.wav"));
	this->getSoundEffects().push_back(Mix_LoadWAV("../Sounds/zbeep.wav"));
}

void GameSounds::startBackgroundMusic() {
	Mix_PlayMusic(this->getBackgroundMusic(),-1);
}

void GameSounds::stopBackgroundMusic() {
	Mix_HaltMusic();
}

void GameSounds::toggleBackgroundMusic() {
	if(Mix_PausedMusic() == 1)
		Mix_ResumeMusic();
	else
		Mix_PauseMusic();
}

void GameSounds::playSoundEffect(unsigned int soundEffectIndex) {
	if (soundEffectIndex < SOUND_INDEX_NO_SOUND)
		Mix_PlayChannel(-1,this->getSoundEffects()[soundEffectIndex],0);
}

void GameSounds::cleanUp() {
	//Free background music.
	Mix_FreeMusic(this->getBackgroundMusic());

	//Free sounds.
	for (unsigned int i = 0; i < this->getSoundEffects().size(); i++) {
		Mix_FreeChunk(this->getSoundEffects()[i]);
	}

	//Free SDL_mixer.
	Mix_CloseAudio();
}

GameSounds::~GameSounds() {
}