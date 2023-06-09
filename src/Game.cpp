#include "../include/Game.h"

void Game::run()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Flappy Bird");
    window.setFramerateLimit(60);

    ImGui::SFML::Init(window);

    sf::Clock delta;

    Settings _settings;

    bool showSettings = false, showBoundingBoxes = false, gameStart = false, gamePause = false, gameLost = false;
    int background = 0, moveSpeed = 3, pipeColor = 0, birdColor = 0, scoreMultiplier = 1, highscore = 0, currentScore = 0;
    float gapBetweenPipes = 150.0;
    float boundingColorRGB[3] = { sf::Color::Red.r / 255, 0, 0 };
    int volume = 100;
    bool invincible = false;
    float gravity = 0.25;
    float scale = 1.0;

    const int MaxMemoryHistory = 100;
    float memoryHistory[MaxMemoryHistory] = {};
    int memoryIndex = 0;

    _settings.deserialize(moveSpeed, gapBetweenPipes, gravity, scoreMultiplier, showBoundingBoxes, background, pipeColor, birdColor, volume, scale, highscore);

    Text text{ highscore };
    if (!text.loadAssets())
        return;
    text.setup();

    Sound sounds;
    if (!sounds.loadAssets())
        return;

    Collision collision;

    World world{ moveSpeed };
    if (!world.loadAssets())
        return;
    world.setup();

    std::vector<Pipe*> pipes;
    for (int i = 1; i < 4; i++)
    {
        Pipe* p = new Pipe{ gapBetweenPipes, float(i * 300 + SCREEN_WIDTH * 0.66), moveSpeed };
        if (!p->loadAssets())
            return;
        p->setup();
        pipes.push_back(p);
    }

    Bird player{ 0.1,gravity,5 };
    if (!player.loadAssets())
        return;
    player.setup();

    while (window.isOpen())
    {
        sf::Event event;

        _settings.serialize(moveSpeed, gapBetweenPipes, gravity, scoreMultiplier, showBoundingBoxes, background, pipeColor, birdColor, volume, scale, text.get_highscoreInt());

        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter)
                showSettings = !showSettings;
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Space && !gameStart)
                    gameStart = true;
                else if (event.key.code == sf::Keyboard::Escape && gameStart && !gameLost)
                    gamePause = !gamePause;
                else if (event.key.code == sf::Keyboard::Space && gameStart && !gameLost && !gamePause)
                {
                    player.addForce();
                    sounds.playWing();
                }

                else if (event.key.code == sf::Keyboard::R && gameLost)
                {
                    gameLost = false;
                    world.setup();
                    text.setup();
                    sounds.setup();
                    player.setup();
                    for (auto& p : pipes)
                        p->setup();
                    currentScore = 0;
                }
            }
        }

        ImGui::SFML::Update(window, delta.restart());

        if (showSettings)
            _settings.settings(showSettings, moveSpeed, background, gapBetweenPipes, pipeColor, showBoundingBoxes, boundingColorRGB, birdColor, gravity, volume, invincible, scoreMultiplier, scale, MaxMemoryHistory, memoryHistory, memoryIndex);

        if (!gamePause && !gameLost)
        {
            world.moveGround();
            if (gameStart)
            {
                for (auto& p : pipes)
                    p->movePipes();
            }
        }

        world.set_moveSpeed(moveSpeed);
        world.changeBackground(background);

        for (auto& p : pipes)
        {
            p->set_moveSpeed(moveSpeed);
            p->changeColor(pipeColor);
            p->set_gapBetweenPipes(gapBetweenPipes);
            p->setBoundingColor(boundingColorRGB);

            if (text.incrementScore(player.get_bird(), p->get_Pipe(), p->get_canAddToScore()))
            {
                sounds.playPoint();

                p->set_canAddtoScore(false);
                currentScore += scoreMultiplier;

                if (currentScore > text.get_highscoreInt())
                {
                    text.set_highscore(currentScore);
                    highscore = currentScore;
                }

            }
        }

        if ((collision.checkGroundCollision(player.get_bird(), world.get_ground()) || collision.checkTopCollision(player.get_bird()) && gameStart) && !invincible)
        {
            gameLost = true;
            sounds.playHit();

            text.set_highscore(highscore);
        }

        for (auto& p : pipes)
        {
            if (collision.checkPipeCollision(player.get_bird(), p->get_Pipe()) && !invincible)
            {
                gameLost = true;
                sounds.playHit();

                text.set_highscore(highscore);
            }

        }

        player.setBoundingColor(boundingColorRGB);
        player.changeColor(birdColor);
        player.set_scale(scale);

        player.set_gravity(gravity);

        if (gameStart && !gameLost && !gamePause)
            player.gravity();

        sounds.set_volume(volume);

        text.set_scoreMultiplier(scoreMultiplier);

        window.clear();

        window.draw(world.get_background());

        for (auto& p : pipes)
        {
            window.draw(p->get_Pipe().first);
            window.draw(p->get_Pipe().second);

            if (gameStart && showBoundingBoxes)
            {
                window.draw(p->get_BoundingBox().first);
                window.draw(p->get_BoundingBox().second);

                window.draw(player.get_boundingBox());
            }
        }

        window.draw(text.get_score());

        window.draw(world.get_ground().first);
        window.draw(world.get_ground().second);

        window.draw(player.get_bird());

        if (!gameStart)
            window.draw(text.get_start());
        if (gameStart && gamePause && !gameLost)
            window.draw(text.get_pause());
        if (gameLost && !gamePause)
        {
            window.draw(text.get_lost());
            window.draw(text.get_restartInfo());
            window.draw(text.get_highscore());
        }


        ImGui::SFML::Render(window); // Needs to be last thing to be drawn

        window.display();
    }

    ImGui::SFML::Shutdown();

    for (auto& p : pipes)
        delete p;

}
