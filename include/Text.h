#ifndef _TEXT_H_
#define _TEXT_H_

#include "Globals.h"

class Text {
public:
	Text(int highscore)
		: i_score{ 0 }, i_highscore{ highscore }, m_scoreMultiplier{ 1 } {}

	bool loadAssets();

	void setup();

	bool incrementScore(sf::Sprite player, std::pair<sf::Sprite, sf::Sprite> pipe, bool canAddToScore);

	sf::Text get_start() const { return m_start; }
	sf::Text get_pause() const { return m_pause; }
	sf::Text get_lost() const { return m_lost; }
	sf::Text get_restartInfo() const { return m_restartInfo; }
	sf::Text get_score() const { return m_score; }
	sf::Text get_highscore() const { return m_highscore; }
	int get_highscoreInt() const { return i_highscore; }

	void set_scoreMultiplier(int multiplier) { m_scoreMultiplier = multiplier; }
	void set_highscore(int highscore);
private:
	sf::Font m_font;
	sf::Font m_scoreFont;

	sf::Text m_start;
	sf::Text m_pause;
	sf::Text m_lost;
	sf::Text m_restartInfo;
	sf::Text m_score, m_highscore;

	int i_score, i_highscore;

	int m_scoreMultiplier;
};

#endif