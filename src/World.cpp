#include "../include/World.h"

bool World::loadAssets()
{
	if (!m_backgroundDay.loadFromFile("assets/textures/background-day-merged.png") || !m_backgroundNight.loadFromFile("assets/textures/background-night-merged.png"))
		return false;

	m_background.setTexture(m_backgroundDay);

	return true;
}