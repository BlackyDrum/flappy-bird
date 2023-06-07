#include "../include/Collision.h"

bool Collision::checkGroundCollision(sf::Sprite player, std::pair<sf::Sprite, sf::Sprite> ground)
{
	if (player.getGlobalBounds().intersects(ground.first.getGlobalBounds()) || player.getGlobalBounds().intersects(ground.second.getGlobalBounds()))
		return true;

	return false;
}

bool Collision::checkPipeCollision(sf::Sprite player, std::pair<sf::Sprite, sf::Sprite> pipe)
{
	if (player.getGlobalBounds().intersects(pipe.first.getGlobalBounds()) || player.getGlobalBounds().intersects(pipe.second.getGlobalBounds()))
		return true;

	return false;
}