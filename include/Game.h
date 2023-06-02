#ifndef _GAME_H_
#define _GAME_H_

#include "../imgui/imgui.h"
#include "../imgui/imgui-SFML.h"

#include "World.h"

class Game
{
public:
	static void run();
private:
	Game() = default;
};

#endif
