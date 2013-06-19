#ifndef _GAME_SOUNDS_H_
#define _GAME_SOUNDS_H_

#ifndef soundEffectIndex_t
#define soundEffectIndex_t
enum soundEffectIndex_t {
	SOUND_INDEX_ARROW,
	SOUND_INDEX_ATTACK_ON_SHIELD,
	SOUND_INDEX_ATTACK_ON_WOOD,
	SOUND_INDEX_OPEN_BOTTLE,
	SOUND_INDEX_EAT_ITEM,
	SOUND_INDEX_REGENERATION,
	SOUND_INDEX_EXPLOSION,
	SOUND_INDEX_MAGIC,
	SOUND_INDEX_NO_SOUND
};
#endif//soundEffectIndex_t

#include <vector>
#include "SDL_mixer.h"


class GameSounds {
private:
	Mix_Music* backgroundMusic;

	std::vector<Mix_Chunk*> soundsEffects;

	Mix_Music* getBackgroundMusic();

	void setBackgroundMusic(Mix_Music* backgroundMusic);

	std::vector<Mix_Chunk*>& getSoundEffects();

public:
	GameSounds();

	void initialize();

	void startBackgroundMusic();

	void stopBackgroundMusic();

	void toggleBackgroundMusic();

	void playSoundEffect(unsigned int soundEffectIndex);

	void cleanUp();

	~GameSounds();
};

#endif // _GAME_SOUNDS_H_