#include <SFML/Graphics.hpp>

#include "../imgui/imgui.h"
#include "../imgui/imgui-SFML.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
    ImGui::SFML::Init(window);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Clock delta;

    const char* buf = "test";

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

        ImGui::Begin("Console");
        ImGui::Text("Hello");


        ImGui::End();

        window.clear();
        window.draw(shape);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}