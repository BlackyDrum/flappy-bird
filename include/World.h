#ifndef _WORLD_H_
#define _WORLD_H_

#include "Globals.h"

class World
{
public:
	bool loadAssets();

	sf::Sprite get_background() const { return m_background; }
	sf::Sprite get_ground() const { return m_ground; }

private:
	sf::Texture m_backgroundDayTexture;
	sf::Texture m_backgroundNightTexture;
	sf::Sprite m_background;

	sf::Texture m_groundTexture;
	sf::Sprite m_ground;
};

#endif
