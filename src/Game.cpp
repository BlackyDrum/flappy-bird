#include "../include/Game.h"

void Game::run()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Flappy Bird", sf::Style::Close);
    window.setFramerateLimit(60);

    ImGui::SFML::Init(window);

    sf::Clock delta;

    bool showSettings = false;

    int moveSpeed = 3;

    World world{ moveSpeed };
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

            ImGui::SliderInt("Movement Speed", &moveSpeed, 1, 7);

            ImGui::End();
        }

        world.moveGround();

        world.set_moveSpeed(moveSpeed);

        window.clear();

        window.draw(world.get_background());
        window.draw(world.get_ground().first);
        window.draw(world.get_ground().second);

        ImGui::SFML::Render(window); // Needs to be last thing to draw

        window.display();
    }

    ImGui::SFML::Shutdown();

}