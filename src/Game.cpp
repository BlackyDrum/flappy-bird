#include "../include/Game.h"

void Game::run()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Flappy Bird", sf::Style::Close);

    ImGui::SFML::Init(window);

    sf::Clock delta;

    bool showSettings = false;

    World world;
    if (!world.loadAssets())
        return;

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter)
                showSettings = !showSettings;
        }

        ImGui::SFML::Update(window, delta.restart());

        if (showSettings)
        {
            ImGui::Begin("Settings", &showSettings);
            ImGui::End();
        }


        window.clear();

        window.draw(world.get_background());
        window.draw(world.get_ground());

        ImGui::SFML::Render(window); // Needs to be last thing to draw

        window.display();
    }

    ImGui::SFML::Shutdown();

}