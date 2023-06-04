#ifndef _GAME_H_
#define _GAME_H_

#include "../imgui/imgui.h"
#include "../imgui/imgui-SFML.h"

#include "World.h"

class Game
{
public:
	static void run();

	static void settings(bool& showSettings, int& moveSpeed, int& background);
private:
	Game() = default;
};

#endif
