#ifndef _GAME_H_
#define _GAME_H_

#include <SFML/Graphics.hpp>

#include "../imgui/imgui.h"
#include "../imgui/imgui-SFML.h"

#include <string>
#include <iostream>

const unsigned int SCREEN_WIDTH = 864, SCREEN_HEIGHT = 510;

class Game
{
public:
	static void run();
};

#endif
