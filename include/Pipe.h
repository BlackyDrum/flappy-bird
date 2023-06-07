#ifndef _PIPE_H_
#define _PIPE_H_

#include "Globals.h"

class Pipe
{
public:
	Pipe(float gapBetweenPipes, sf::Vector2f pos, int moveSpeed)
		: m_gapBetweenPipes{ gapBetweenPipes }, m_pos{ pos }, m_moveSpeed{ moveSpeed } {}

	bool loadAssets();

	void setup();

	void movePipes();

	void changeColor(int color);

	void setBoundingColor(float boundingColor[]);

	std::pair<sf::Sprite, sf::Sprite> get_Pipe() const { return m_pipe; }
	std::pair<sf::RectangleShape, sf::RectangleShape> get_BoundingBox() const { return m_boundingBox; }

	void set_moveSpeed(int moveSpeed) { m_moveSpeed = moveSpeed; }
	void set_gapBetweenPipes(float gap) { m_gapBetweenPipes = gap; }
private:
	sf::Texture m_pipeGreenTexture;
	sf::Texture m_pipeRedTexture;

	/*
	* One Pipe object consists of two sprites, a lower and an upper pipe.
	*/
	std::pair<sf::Sprite, sf::Sprite> m_pipe;
	std::pair<sf::RectangleShape, sf::RectangleShape> m_boundingBox;

	sf::Vector2f m_pos;

	sf::Color m_boundingColor;

	float m_gapBetweenPipes;

	int m_moveSpeed;

	void calculateRandomYPos(float x);
};

#endif
