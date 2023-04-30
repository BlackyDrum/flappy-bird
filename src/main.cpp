#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

#include "../imgui/imgui.h"
#include "../imgui/imgui-SFML.h"

#include "../include/Game.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Flappy Bird!");
    ImGui::SFML::Init(window);

    sf::Clock delta;

    bool show = false;

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


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            show = true;
        }
        
        if (show)
        {
            ImGui::Begin("My First Tool", &show);
            ImGui::End();
        }

        

        window.clear();


        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}