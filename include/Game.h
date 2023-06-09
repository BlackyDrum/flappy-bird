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
#include "Settings.h"
#include "Renderer.h"

class Game
{
public:
	static void run();
private:
	Game() = default;
};

#endif