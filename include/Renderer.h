#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "Globals.h"

#include "World.h"
#include "Pipe.h"
#include "Text.h"
#include "Bird.h"

class Renderer
{
public:
	Renderer() = default;

	void draw(sf::RenderWindow&, World, std::vector<Pipe*>, Bird, Text, bool, bool, bool, bool);
};

#endif