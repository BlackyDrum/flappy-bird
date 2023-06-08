#ifndef _GAME_H_
#define _GAME_H_

#include "../imgui/imgui.h"
#include "../imgui/imgui-SFML.h"

#include "World.h"
#include "Pipe.h"
#include "Text.h"
#include "Bird.h"
#include "Collision.h"
#include "Sound.h"

class Game
{
public:
	static void run();

	static void settings(bool& showSettings, int& moveSpeed, int& background, float& gapBetweenPipes, int& pipeColor, bool& showBoundingBoxes, float RGB[], int& birdColor, float& gravity, int& volume, bool& invincible, int& scoreMultiplier, float& scale, int, float[], int&);

	static void serialize(int, float, float, int, bool, int, int, int, int, float, int);

	static void deserialize(int&, float&, float&, int&, bool&, int&, int&, int&, int&, float&, int&);

#ifdef _WIN32
	static float getMemoryUse();
#else
	static std::string readMeminfoValue(const std::string& key);
#endif
private:
	Game() = default;
};

#endif