#include "../include/Game.h"

void Game::run()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Flappy Bird", sf::Style::Close);
    window.setFramerateLimit(60);

#if defined(NDEBUG) && defined(_WIN32)
    ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif

    ImGui::SFML::Init(window);

    sf::Clock delta;

    bool showSettings = false, gameStart = false;
    int background = 0, moveSpeed = 1, pipeColor = 0;
    float gapBetweenPipes = 100.0;

    Text text;
    if (!text.loadAssets())
        return;

    World world{ moveSpeed };
    if (!world.loadAssets())
        return;

    std::vector<Pipe*> pipes;
    for (int i = 1; i < 4; i++)
    {
        Pipe* p = new Pipe{ gapBetweenPipes,sf::Vector2f(i * 300 + SCREEN_WIDTH * 0.66,0), moveSpeed };
        if (!p->loadAssets())
            return;
        pipes.push_back(p);
    }

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
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Mouse::Left || event.key.code == sf::Keyboard::Space)
                    gameStart = true;
            }
        }

        ImGui::SFML::Update(window, delta.restart());

        if (showSettings)
            settings(showSettings, moveSpeed, background, gapBetweenPipes, pipeColor);

        /* Move pipes and ground in sync */
        world.moveGround();
        if (gameStart)
        {
            for (auto& p : pipes)
                p->movePipes();
        } 

        world.set_moveSpeed(moveSpeed);
        for (auto& p : pipes)
            p->set_moveSpeed(moveSpeed);

        world.changeBackground(background);
        for (auto& p : pipes)
            p->changeColor(pipeColor);

        for (auto& p : pipes)
            p->set_gapBetweenPipes(gapBetweenPipes);

        window.clear();

        window.draw(world.get_background());

        for (auto& p : pipes)
        {
            window.draw(p->get_Pipe().first);
            window.draw(p->get_Pipe().second);
        }
            
        window.draw(world.get_ground().first);
        window.draw(world.get_ground().second);

        if (!gameStart)
            window.draw(text.get_start());

        ImGui::SFML::Render(window); // Needs to be last thing to be drawn

        window.display();
    }

    ImGui::SFML::Shutdown();

    for (auto& p : pipes)
        delete p;

}

void Game::settings(bool& showSettings, int& moveSpeed, int& background, float& gapBetweenPipes, int& pipeColor)
{
    ImGui::Begin("Settings", &showSettings);

    ImGui::SliderInt("Flying Speed", &moveSpeed, 1, 7);

    ImGui::SliderFloat("Gap between Pipes", &gapBetweenPipes, 50.0, 140.0);

    ImGui::NewLine();

    if (ImGui::CollapsingHeader("Update Assets"))
    {
        ImGui::RadioButton("Day Theme", &background, 0);
        ImGui::SameLine();
        ImGui::RadioButton("Night Theme", &background, 1);

        ImGui::RadioButton("Green Pipe", &pipeColor, 0);
        ImGui::SameLine();
        ImGui::RadioButton("Red Pipe", &pipeColor, 1);
    }

    ImGui::End();
}