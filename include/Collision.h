#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "Globals.h"

class Collision
{
public:
	Collision() {}

	bool checkGroundCollision(sf::Sprite player, std::pair<sf::Sprite, sf::Sprite> ground);

	bool checkPipeCollision(sf::Sprite player, std::pair<sf::Sprite, sf::Sprite> ground);

	bool checkTopCollision(sf::Sprite player);
};

#endif