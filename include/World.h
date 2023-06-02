#ifndef _WORLD_H_
#define _WORLD_H_

#include <SFML/Graphics.hpp>

#include <iostream>

class World
{
public:
	bool loadAssets();

	sf::Sprite get_background() const { return m_background; }

private:
	sf::Texture m_backgroundTexture;
	sf::Sprite m_background;
};

#endif
