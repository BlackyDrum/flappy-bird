#include "../include/Text.h"

bool Text::loadAssets()
{
	if (!m_font.loadFromFile("assets/fonts/FlappyBirdy.ttf"))
		return false;

	m_start.setFont(m_font);
	m_start.setString("Press Space to start");
	m_start.setCharacterSize(100);

	sf::FloatRect textRect = m_start.getLocalBounds();
	m_start.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	m_start.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));

	return true;
}