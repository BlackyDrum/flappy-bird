#include "../include/Text.h"

bool Text::loadAssets()
{
	if (!m_font.loadFromFile("assets/fonts/FlappyBirdy.ttf"))
		return false;

	return true;
}

void Text::setup()
{
	m_start.setFont(m_font);
	m_start.setString("Press Space to start");
	m_start.setCharacterSize(100);

	m_pause.setFont(m_font);
	m_pause.setString("Game Paused");
	m_pause.setCharacterSize(100);

	/* position the text in the middle of the screen */
	m_start.setOrigin(m_start.getLocalBounds().left + m_start.getLocalBounds().width / 2.0f,
		m_start.getLocalBounds().top + m_start.getLocalBounds().height / 2.0f);
	m_start.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));

	m_pause.setOrigin(m_pause.getLocalBounds().left + m_pause.getLocalBounds().width / 2.0f,
		m_pause.getLocalBounds().top + m_pause.getLocalBounds().height / 2.0f);
	m_pause.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));
}