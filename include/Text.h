#ifndef _TEXT_H_
#define _TEXT_H_

#include "Globals.h"

class Text {
public:
	Text() = default;

	bool loadAssets();

	void setup();

	sf::Text get_start() const { return m_start; }
	sf::Text get_pause() const { return m_pause; }
	sf::Text get_lost() const { return m_lost; }
	sf::Text get_restartInfo() const { return m_restartInfo; }
private:
	sf::Font m_font;

	sf::Text m_start;
	sf::Text m_pause;
	sf::Text m_lost;
	sf::Text m_restartInfo;
};

#endif