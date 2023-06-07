#ifndef _SOUND_H_
#define _SOUND_H_

#include "Globals.h"

class Sound
{
public:
	Sound() :
		m_isPlayingSound{ false }, m_volume{ 100 } {}

	bool loadAssets();

	void setup();

	void playHit();

	void playWing();

	void set_volume(int volume) { m_volume = volume; }
private:
	sf::SoundBuffer m_hitBuffer;
	sf::Sound m_hit;

	sf::SoundBuffer m_wingBuffer;
	sf::Sound m_wing;

	bool m_isPlayingSound;

	int m_volume;
};

#endif