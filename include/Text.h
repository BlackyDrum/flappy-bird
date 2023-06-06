#ifndef _TEXT_H_
#define _TEXT_H_

#include "Globals.h"

class Text {
public:
	Text() = default;

	bool loadAssets();

	sf::Text get_start() const { return m_start; }
private:
	sf::Font m_font;

	sf::Text m_start;
};

#endif