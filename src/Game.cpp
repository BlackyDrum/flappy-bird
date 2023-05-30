#include "../include/Game.h"

void Game::run()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Flappy Bird", sf::Style::Close);

    ImGui::SFML::Init(window);

    sf::Clock delta;

    bool showSettings = false;

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Enter)
                {
                    showSettings = !showSettings;
                }
            }
        }

        ImGui::SFML::Update(window, delta.restart());

        if (showSettings)
        {
            ImGui::Begin("Settings", &showSettings);
            ImGui::End();
        }


        window.clear();

        ImGui::SFML::Render(window);

        window.display();
    }

    ImGui::SFML::Shutdown();

}