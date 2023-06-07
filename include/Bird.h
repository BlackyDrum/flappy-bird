#ifndef _BIRD_H_
#define _BIRD_H_

#include "Globals.h"

class Bird
{
public:
	Bird(float gravity, float gravityForce, float jumpForce) :
		c_gravity{ gravity }, c_gravityForce{ gravityForce }, c_jumpForce{ jumpForce }, m_isFalling{ true }, m_isJumping{ false },
		m_gravity{ gravity }, m_gravityForce{ gravityForce }, m_jumpForce{ jumpForce } {}

	bool loadAssets();

	void setup();

	void gravity();

	void addForce();

	void changeColor(int color);

	void setBoundingColor(float RGB[]);

	sf::Sprite get_bird() const { return m_bird; }
	sf::RectangleShape get_boundingBox() const { return m_boundingBox; }

	void set_gravity(float gravity) { c_gravityForce = gravity; m_gravityForce = gravity; }
	void set_jumpforce(float jumpForce) { c_jumpForce = jumpForce; m_jumpForce = jumpForce; }
private:
	sf::Texture m_birdBlueTexture;
	sf::Texture m_birdRedTexture;
	sf::Texture m_birdYellowTexture;

	sf::Sprite m_bird;

	sf::Color m_boundingColor;

	sf::RectangleShape m_boundingBox;

	float m_gravity, m_gravityForce, m_jumpForce;

	float c_gravity, c_gravityForce, c_jumpForce;

	bool m_isFalling, m_isJumping;
};

#endif