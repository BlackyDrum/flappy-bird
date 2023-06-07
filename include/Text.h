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
private:
	sf::Font m_font;

	sf::Text m_start;
	sf::Text m_pause;
};

#endif