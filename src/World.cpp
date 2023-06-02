#include "../include/World.h"

bool World::loadAssets()
{
	if (!m_backgroundTexture.loadFromFile("assets/textures/background-day-merged.png"))
		return false;

	m_background.setTexture(m_backgroundTexture);

	return true;
}