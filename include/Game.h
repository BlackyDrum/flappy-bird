#ifndef _GAME_H_
#define _GAME_H_

#include <SFML/Graphics.hpp>

#include "../imgui/imgui.h"
#include "../imgui/imgui-SFML.h"

#include <string>
#include <iostream>

const int SCREEN_WIDTH = 864, SCREEN_HEIGHT = 510;

class Game
{
public:
	static void run();
public:
    Game() {}
    ~Game() = default;
private:

};


void Game::run()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Flappy Bird!",sf::Style::Close);
    ImGui::SFML::Init(window);

    sf::Clock delta;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();
        }
        ImGui::SFML::Update(window, delta.restart());




        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

}

#endif
