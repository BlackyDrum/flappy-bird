#ifndef _PIPE_H_
#define _PIPE_H_

#include "Globals.h"

class Pipe
{
public:
	Pipe(float gapBetweenPipes, sf::Vector2f pos, int moveSpeed)
		: m_gapBetweenPipes{ gapBetweenPipes }, m_pos{ pos }, m_moveSpeed{ moveSpeed } {}

	bool loadAssets();

	void movePipes();

	void changeColor(int color);

	std::pair<sf::Sprite, sf::Sprite> get_Pipe() const { return m_pipe; }

	void set_moveSpeed(int moveSpeed) { m_moveSpeed = moveSpeed; }
	void set_gapBetweenPipes(float gap) { m_gapBetweenPipes = gap; }
private:
	sf::Texture m_pipeGreenTexture;
	sf::Texture m_pipeRedTexture;
	std::pair<sf::Sprite, sf::Sprite> m_pipe;

	sf::Vector2f m_pos;

	float m_gapBetweenPipes;
	int m_moveSpeed;

	void calculateRandomYPos(float x);
};

#endif
