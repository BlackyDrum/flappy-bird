#include "../include/Bird.h"

bool Bird::loadAssets()
{
	if (!m_birdBlueTexture.loadFromFile("assets/textures/bluebird-midflap.png") || !m_birdRedTexture.loadFromFile("assets/textures/redbird-midflap.png") ||
		!m_birdYellowTexture.loadFromFile("assets/textures/yellowbird-midflap.png") || !m_birdYellowTextureUp.loadFromFile("assets/textures/yellowbird-upflap.png") ||
		!m_birdBlueTextureUp.loadFromFile("assets/textures/bluebird-upflap.png") || !m_birdRedTextureUp.loadFromFile("assets/textures/redbird-upflap.png"))
		return false;

	m_bird.setTexture(m_birdYellowTexture);

	return true;
}

void Bird::setup()
{
	m_bird.setPosition(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 3);

	m_bird.setScale(1.2, 1.2);

	m_boundingBox.setFillColor(sf::Color::Transparent);
	m_boundingBox.setOutlineColor(m_boundingColor);
	m_boundingBox.setOutlineThickness(3);
	m_boundingBox.setSize(sf::Vector2f(m_bird.getTextureRect().width * m_bird.getScale().x, m_bird.getTextureRect().height * m_bird.getScale().y));
	m_boundingBox.setPosition(m_bird.getPosition());

	m_gravity = c_gravityForce;
	m_jumpForce = c_jumpForce;
	m_gravityForce = c_gravityForce;
}

void Bird::gravity()
{
	if (m_isFalling)
	{
		m_bird.setPosition(m_bird.getPosition().x, m_bird.getPosition().y + m_gravity);
		m_gravity += c_gravityForce;

		m_bird.setRotation(15);

		m_boundingBox.setRotation(15);
	}
	
	else if (m_isJumping)
	{
		m_bird.setPosition(m_bird.getPosition().x, m_bird.getPosition().y - m_jumpForce);
		m_jumpForce -= c_gravityForce;

		m_bird.setRotation(-15);

		m_boundingBox.setRotation(-15);
	}

	if (m_jumpForce <= 0)
	{
		m_isJumping = false;
		m_isFalling = true;

		m_gravityForce = c_gravityForce;
		m_gravity = c_gravity;
		m_jumpForce = c_jumpForce;
	}

	m_boundingBox.setPosition(m_bird.getPosition());
}

void Bird::addForce()
{
	m_isJumping = true;
	m_isFalling = false;

	m_jumpForce = c_jumpForce;
}

void Bird::setBoundingColor(float RGB[])
{
	m_boundingColor.r = round(RGB[0] * 255);
	m_boundingColor.g = round(RGB[1] * 255);
	m_boundingColor.b = round(RGB[2] * 255);

	m_boundingBox.setOutlineColor(m_boundingColor);
}

void Bird::changeColor(int color)
{
	/* This method additionally animates the flap */
	if (m_animationClock.getElapsedTime().asMilliseconds() > 100)
	{
		m_animationClock.restart();

		if (m_currentFlap == up)
		{
			switch(color)
			{
			case 0:
				m_bird.setTexture(m_birdYellowTexture);
				break;
			case 1:
				m_bird.setTexture(m_birdBlueTexture);
				break;
			case 2:
				m_bird.setTexture(m_birdRedTexture);
				break;
			}
			m_currentFlap = mid;
		}	
		else if (m_currentFlap == mid)
		{
			switch (color)
			{
			case 0:
				m_bird.setTexture(m_birdYellowTextureUp);
				break;
			case 1:
				m_bird.setTexture(m_birdBlueTextureUp);
				break;
			case 2:
				m_bird.setTexture(m_birdRedTextureUp);
				break;
			}
			m_currentFlap = up;
		}
	}
}

void Bird::set_scale(float scale)
{
	m_scale = scale;

	m_bird.setScale(sf::Vector2f(scale,scale));

	m_boundingBox.setSize(sf::Vector2f(m_bird.getTextureRect().width * m_bird.getScale().x, m_bird.getTextureRect().height * m_bird.getScale().y));
}
