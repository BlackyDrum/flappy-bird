#include "../include/Sound.h"

bool Sound::loadAssets()
{
	if (!m_hitBuffer.loadFromFile("assets/sounds/hit.wav") || !m_wingBuffer.loadFromFile("assets/sounds/wing.wav"))
		return false;

	m_hit.setBuffer(m_hitBuffer);
	m_wing.setBuffer(m_wingBuffer);

	return true;
}

void Sound::playHit()
{
	if (!m_isPlayingSound)
	{
		m_hit.setVolume(m_volume);
		m_hit.play();
		m_isPlayingSound = true;
	}
}

void Sound::playWing()
{
	m_wing.setVolume(m_volume);
	m_wing.play();
}

void Sound::setup()
{
	m_isPlayingSound = false;
}