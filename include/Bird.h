#ifndef _BIRD_H_
#define _BIRD_H_

#include "Globals.h"

class Bird
{
public:
	Bird(float gravity, float gravityForce, float jumpForce) :
		c_gravity{ gravity }, c_gravityForce{ gravityForce }, c_jumpForce{ jumpForce }, m_isFalling{ true }, m_isJumping{ false },
		m_gravity{ gravity }, m_gravityForce{ gravityForce }, m_jumpForce{ jumpForce }, m_currentFlap{ mid }, m_scale{ 1.0 } {}

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
	void set_scale(float scale);
private:
	sf::Texture m_birdBlueTexture, m_birdBlueTextureUp;
	sf::Texture m_birdRedTexture, m_birdRedTextureUp;
	sf::Texture m_birdYellowTexture, m_birdYellowTextureUp;

	sf::Sprite m_bird;

	sf::Color m_boundingColor;

	sf::RectangleShape m_boundingBox;

	sf::Clock m_animationClock;

	enum CurrentFlap { mid, up };
	CurrentFlap m_currentFlap;

	float m_gravity, m_gravityForce, m_jumpForce;

	float c_gravity, c_gravityForce, c_jumpForce;

	float m_scale;

	bool m_isFalling, m_isJumping;
};

#endif