#include "../include/Sound.h"

bool Sound::loadAssets()
{
	if (!m_hitBuffer.loadFromFile("assets/sounds/hit.wav") || !m_wingBuffer.loadFromFile("assets/sounds/wing.wav") || 
		!m_pointBuffer.loadFromFile("assets/sounds/point.wav"))
		return false;

	m_hit.setBuffer(m_hitBuffer);
	m_wing.setBuffer(m_wingBuffer);
	m_point.setBuffer(m_pointBuffer);

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

void Sound::playPoint()
{
	m_point.setVolume(m_volume);
	m_point.play();
}

void Sound::setup()
{
	m_isPlayingSound = false;
}