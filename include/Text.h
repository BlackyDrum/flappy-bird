#ifndef _TEXT_H_
#define _TEXT_H_

#include "Globals.h"

class Text {
public:
	Text()
		: i_score{ 0 }, m_scoreMultiplier{ 1 } {}

	bool loadAssets();

	void setup();

	bool incrementScore(sf::Sprite player, std::pair<sf::Sprite, sf::Sprite> pipe, bool canAddToScore);

	sf::Text get_start() const { return m_start; }
	sf::Text get_pause() const { return m_pause; }
	sf::Text get_lost() const { return m_lost; }
	sf::Text get_restartInfo() const { return m_restartInfo; }
	sf::Text get_score() const { return m_score; }

	void set_scoreMultiplier(int multiplier) { m_scoreMultiplier = multiplier; }
private:
	sf::Font m_font;
	sf::Font m_scoreFont;

	sf::Text m_start;
	sf::Text m_pause;
	sf::Text m_lost;
	sf::Text m_restartInfo;
	sf::Text m_score;

	int i_score;

	int m_scoreMultiplier;
};

#endif