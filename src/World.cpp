#include "../include/World.h"

bool World::loadAssets()
{
	if (!m_backgroundDayTexture.loadFromFile("assets/textures/background-day-merged.png") || !m_backgroundNightTexture.loadFromFile("assets/textures/background-night-merged.png") ||
		!m_groundTexture.loadFromFile("assets/textures/base-merged.png"))
		return false;

	m_background.setTexture(m_backgroundDayTexture);

	m_ground.setTexture(m_groundTexture);
	m_ground.setPosition(sf::Vector2f(0, SCREEN_HEIGHT - m_groundTexture.getSize().y));

	return true;
}