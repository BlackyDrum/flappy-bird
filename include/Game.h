#ifndef _GAME_H_
#define _GAME_H_

#include "../imgui/imgui.h"
#include "../imgui/imgui-SFML.h"

#include "World.h"
#include "Pipe.h"
#include "Text.h"
#include "Bird.h"

class Game
{
public:
	static void run();

	static void settings(bool& showSettings, int& moveSpeed, int& background, float& gapBetweenPipes, int& pipeColor, bool& showBoundingBoxes, float RGB[], int& birdColor, float& gravity);
private:
	Game() = default;
};

#endif
