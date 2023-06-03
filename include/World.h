#ifndef _WORLD_H_
#define _WORLD_H_

#include "Globals.h"

class World
{
public:
	bool loadAssets();

	sf::Sprite get_background() const { return m_background; }

private:
	sf::Texture m_backgroundDay;
	sf::Texture m_backgroundNight;
	sf::Sprite m_background;
};

#endif
