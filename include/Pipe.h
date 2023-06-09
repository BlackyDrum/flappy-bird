#ifndef _PIPE_H_
#define _PIPE_H_

#include "Globals.h"

class Pipe
{
public:
	Pipe(float gapBetweenPipes, float pos, int moveSpeed)
		: m_gapBetweenPipes{ gapBetweenPipes }, m_Xpos{ pos }, m_moveSpeed{ moveSpeed }, m_canAddToScore{ true } {}

	bool loadAssets();

	void setup();

	void movePipes();

	void changeColor(int color);

	void setBoundingColor(float boundingColor[]);

	std::pair<sf::Sprite, sf::Sprite> get_Pipe() const { return m_pipe; }
	std::pair<sf::RectangleShape, sf::RectangleShape> get_BoundingBox() const { return m_boundingBox; }
	bool get_canAddToScore() const { return m_canAddToScore; }

	void set_moveSpeed(int moveSpeed) { m_moveSpeed = moveSpeed; }
	void set_gapBetweenPipes(float gap) { m_gapBetweenPipes = gap; }
	void set_canAddtoScore(bool add) { m_canAddToScore = add; }
private:
	sf::Texture m_pipeGreenTexture;
	sf::Texture m_pipeRedTexture;

	sf::Color m_boundingColor;

	/*
	* One Pipe object consists of two sprites, a lower and an upper pipe.
	*/
	std::pair<sf::Sprite, sf::Sprite> m_pipe;
	std::pair<sf::RectangleShape, sf::RectangleShape> m_boundingBox;

	float m_Xpos;

	float m_gapBetweenPipes;

	int m_moveSpeed;

	bool m_canAddToScore;

	void calculateRandomYPos(float x);
};

#endif
