#include "../include/Pipe.h"

bool Pipe::loadAssets()
{
	if (!m_pipeGreenTexture.loadFromFile("assets/textures/pipe-green.png") || !m_pipeRedTexture.loadFromFile("assets/textures/pipe-red.png"))
		return false;

	m_pipe.first.setTexture(m_pipeGreenTexture);
	m_pipe.second.setTexture(m_pipeGreenTexture);

	return true;
}

void Pipe::setup()
{
	m_boundingBox.first.setFillColor(sf::Color::Transparent);
	m_boundingBox.first.setOutlineColor(m_boundingColor);
	m_boundingBox.first.setOutlineThickness(3);
	m_boundingBox.first.setSize(sf::Vector2f(m_pipe.first.getTexture()->getSize().x, m_pipe.first.getTexture()->getSize().y));

	m_boundingBox.second.setFillColor(sf::Color::Transparent);
	m_boundingBox.second.setOutlineColor(m_boundingColor);
	m_boundingBox.second.setOutlineThickness(3);
	m_boundingBox.second.setSize(sf::Vector2f(m_pipe.second.getTexture()->getSize().x, m_pipe.second.getTexture()->getSize().y));

	calculateRandomYPos(m_Xpos);

	/* One pipe being mirrored */
	m_pipe.first.setScale(1.0, -1.0);
	m_boundingBox.first.setScale(1.0, -1.0);
}

void Pipe::movePipes()
{
	m_pipe.first.setPosition(m_pipe.first.getPosition().x - m_moveSpeed, m_pipe.first.getPosition().y);
	m_pipe.second.setPosition(m_pipe.second.getPosition().x - m_moveSpeed, m_pipe.second.getPosition().y);

	m_boundingBox.first.setPosition(m_pipe.first.getPosition());
	m_boundingBox.second.setPosition(m_pipe.second.getPosition());

	/*
	* When both pipes reach the left end of the screen, they are both immediately teleported back to the right side of the screen.
	* Additionally, a new y-position is calculated for the pipes for game variation
	*/
	if (m_pipe.first.getPosition().x + m_pipe.first.getTexture()->getSize().x <= 0)
	{
		m_pipe.first.setPosition(SCREEN_WIDTH, m_pipe.first.getPosition().y);
		m_pipe.second.setPosition(SCREEN_WIDTH, m_pipe.second.getPosition().y);

		m_canAddToScore = true;

		calculateRandomYPos(SCREEN_WIDTH);
	}		
}

void Pipe::calculateRandomYPos(float x)
{
	/* Generate random number */
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(20, SCREEN_HEIGHT / 2);

	float yPos = dist6(rng);

	/*
	* Both Pipes use the same y-position, being seperated by a little offset
	* This is working, because one pipe is mirrored
	*/
	m_pipe.first.setPosition(x, yPos);
	m_pipe.second.setPosition(x, yPos + m_gapBetweenPipes);
}

void Pipe::changeColor(int color)
{
	switch (color)
	{
	case 0:
		m_pipe.first.setTexture(m_pipeGreenTexture);
		m_pipe.second.setTexture(m_pipeGreenTexture);
		break;
	case 1:
		m_pipe.first.setTexture(m_pipeRedTexture);
		m_pipe.second.setTexture(m_pipeRedTexture);
		break;
	default:
		m_pipe.first.setTexture(m_pipeGreenTexture);
		m_pipe.second.setTexture(m_pipeGreenTexture);
	}
}

void Pipe::setBoundingColor(float RGB[])
{
	m_boundingColor.r = round(RGB[0] * 255);
	m_boundingColor.g = round(RGB[1] * 255);
	m_boundingColor.b = round(RGB[2] * 255);

	m_boundingBox.first.setOutlineColor(m_boundingColor);
	m_boundingBox.second.setOutlineColor(m_boundingColor);
}