#include "../include/Pipe.h"

bool Pipe::loadAssets()
{
	if (!m_pipeGreenTexture.loadFromFile("assets/textures/pipe-green.png") || !m_pipeRedTexture.loadFromFile("assets/textures/pipe-red.png"))
		return false;

	m_pipe.first.setTexture(m_pipeGreenTexture);
	m_pipe.second.setTexture(m_pipeGreenTexture);

	calculateRandomYPos(m_pos.x);

	/* One pipe being mirrored */
	m_pipe.first.setScale(1.0, -1.0);

	return true;
}

void Pipe::movePipes()
{
	m_pipe.first.setPosition(m_pipe.first.getPosition().x - m_moveSpeed, m_pipe.first.getPosition().y);
	m_pipe.second.setPosition(m_pipe.second.getPosition().x - m_moveSpeed, m_pipe.second.getPosition().y);

	/*
	* When both pipes reach the left end of the screen, they are both immediately teleported back to the right side of the screen.
	* Additionally, a new y-position is calculated for the pipes
	*/
	if (m_pipe.first.getPosition().x + m_pipe.first.getTexture()->getSize().x <= 0)
	{
		m_pipe.first.setPosition(SCREEN_WIDTH, m_pipe.first.getPosition().y);
		m_pipe.second.setPosition(SCREEN_WIDTH, m_pipe.second.getPosition().y);

		calculateRandomYPos(SCREEN_WIDTH);
	}
		
}

void Pipe::calculateRandomYPos(float x)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(10, SCREEN_HEIGHT / 2);

	float yPos = dist6(rng);

	/*
	* Both Pipes use the same y-position, being seperated by a little offset the player is able to adjust
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