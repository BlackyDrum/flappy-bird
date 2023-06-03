#include "../include/World.h"

bool World::loadAssets()
{
	if (!m_backgroundDayTexture.loadFromFile("assets/textures/background-day-merged.png") || !m_backgroundNightTexture.loadFromFile("assets/textures/background-night-merged.png") ||
		!m_groundTexture.loadFromFile("assets/textures/base-merged.png"))
		return false;

	m_background.setTexture(m_backgroundDayTexture);

	m_ground.first.setTexture(m_groundTexture);
	m_ground.second.setTexture(m_groundTexture);

	m_ground.first.setPosition(0, SCREEN_HEIGHT - m_groundTexture.getSize().y);
	m_ground.second.setPosition(SCREEN_WIDTH, SCREEN_HEIGHT - m_groundTexture.getSize().y);

	return true;
}

void World::moveGround()
{
	/*
	* Initialize starting position for the two ground sprites in the std::pair
	*/
	m_ground.first.setPosition(m_ground.first.getPosition().x - m_moveSpeed,m_ground.first.getPosition().y);
	m_ground.second.setPosition(sf::Vector2f(m_ground.second.getPosition().x - m_moveSpeed,m_ground.second.getPosition().y));

	/*
	* When one of the two ground sprites reaches the left end of the screen, they are immediately teleported to the right side
	*/
	if (m_ground.first.getPosition().x <= m_groundTexture.getSize().x * -1.0) 
		m_ground.first.setPosition(SCREEN_WIDTH - (int(m_ground.first.getPosition().x) * -1.0 - int(m_groundTexture.getSize().x)), m_ground.first.getPosition().y);	

	if (m_ground.second.getPosition().x <= m_groundTexture.getSize().x * -1.0)
		m_ground.second.setPosition(SCREEN_WIDTH - (int(m_ground.second.getPosition().x) * -1.0 - int(m_groundTexture.getSize().x)), m_ground.second.getPosition().y);
}