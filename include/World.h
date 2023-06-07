#ifndef _WORLD_H_
#define _WORLD_H_

#include "Globals.h"

class World
{
public:
	World(int moveSpeed)
		: m_moveSpeed{ moveSpeed } {}

	bool loadAssets();

	void setup();

	void changeBackground(int);

	void moveGround();

	sf::Sprite get_background() const { return m_background; }
	std::pair<sf::Sprite, sf::Sprite> get_ground() const { return m_ground; }

	void set_moveSpeed(int moveSpeed) { m_moveSpeed = moveSpeed; }

private:
	sf::Texture m_backgroundDayTexture;
	sf::Texture m_backgroundNightTexture;
	sf::Sprite m_background;

	sf::Texture m_groundTexture;
	std::pair<sf::Sprite, sf::Sprite> m_ground;

	int m_moveSpeed;
};

#endif
