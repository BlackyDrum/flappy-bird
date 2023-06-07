#include "../include/Text.h"

bool Text::loadAssets()
{
	if (!m_font.loadFromFile("assets/fonts/FlappyBirdy.ttf") || !m_scoreFont.loadFromFile("assets/fonts/04B_19__.ttf"))
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

	m_lost.setFont(m_font);
	m_lost.setString("You Lost");
	m_lost.setCharacterSize(150);
	m_lost.setFillColor(sf::Color::Black);

	m_restartInfo.setFont(m_font);
	m_restartInfo.setString("Press R to restart");
	m_restartInfo.setCharacterSize(75);
	m_restartInfo.setFillColor(sf::Color::Black);

	m_score.setFont(m_scoreFont);
	m_score.setString("0");
	m_score.setCharacterSize(50);

	/* position the text in the middle of the screen */
	m_start.setOrigin(m_start.getLocalBounds().left + m_start.getLocalBounds().width / 2.0f,
		m_start.getLocalBounds().top + m_start.getLocalBounds().height / 2.0f);
	m_start.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));

	m_pause.setOrigin(m_pause.getLocalBounds().left + m_pause.getLocalBounds().width / 2.0f,
		m_pause.getLocalBounds().top + m_pause.getLocalBounds().height / 2.0f);
	m_pause.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));

	m_lost.setOrigin(m_lost.getLocalBounds().left + m_lost.getLocalBounds().width / 2.0f,
		m_lost.getLocalBounds().top + m_lost.getLocalBounds().height / 2.0f);
	m_lost.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 3.0f));

	m_restartInfo.setOrigin(m_restartInfo.getLocalBounds().left + m_restartInfo.getLocalBounds().width / 2.0f,
		m_restartInfo.getLocalBounds().top + m_restartInfo.getLocalBounds().height / 2.0f);
	m_restartInfo.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f));

	m_score.setOrigin(m_score.getLocalBounds().left + m_score.getLocalBounds().width / 2.0f,
		m_score.getLocalBounds().top + m_score.getLocalBounds().height / 2.0f);
	m_score.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 6.0f));

	i_score = 0;
}

bool Text::incrementScore(sf::Sprite player, std::pair<sf::Sprite, sf::Sprite> pipe, bool canAddToScore)
{
	if (pipe.first.getPosition().x < player.getPosition().x && canAddToScore)
	{
		m_score.setString(std::to_string(++i_score * m_scoreMultiplier));
		return true;
	}
	
	return false;
}