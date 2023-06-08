#include "../include/Game.h"

void Game::run()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Flappy Bird");
    window.setFramerateLimit(60);

    ImGui::SFML::Init(window);

    sf::Clock delta;

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

    deserialize(moveSpeed, gapBetweenPipes, gravity, scoreMultiplier, showBoundingBoxes, background, pipeColor, birdColor, volume, scale, highscore);

    Text text{highscore};
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

        serialize(moveSpeed, gapBetweenPipes, gravity, scoreMultiplier, showBoundingBoxes, background, pipeColor, birdColor, volume, scale, text.get_highscoreInt());

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
            settings(showSettings, moveSpeed, background, gapBetweenPipes, pipeColor, showBoundingBoxes, boundingColorRGB, birdColor, gravity, volume, invincible, scoreMultiplier, scale, MaxMemoryHistory, memoryHistory, memoryIndex);

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
#ifdef _WIN32
float Game::getMemoryUse()
{
    PROCESS_MEMORY_COUNTERS_EX pmc;
    if (!GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {
        // Error handling
        DWORD errorCode = GetLastError();
        LPSTR messageBuffer = nullptr;
        size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
        if (messageBuffer) {
            std::cout << "Failed to retrieve memory usage: " << messageBuffer << std::endl;
            LocalFree(messageBuffer);
        }
        return 0.0f;
    }

    SIZE_T physicalMemory = pmc.WorkingSetSize;
    float memoryUsage = static_cast<float>(physicalMemory) / (1024.0f * 1024.0f); // Convert to MB

    return memoryUsage;
}
#else
std::string Game::readMeminfoValue(const std::string& key)
{
    std::ifstream file("/proc/meminfo");
    std::string line;

    while (std::getline(file, line)) {
        if (line.find(key) != std::string::npos) {
            std::string value = line.substr(line.find(':') + 1);
            // Remove leading whitespace
            value.erase(0, value.find_first_not_of(" \t"));
            // Remove trailing newline character
            value.pop_back();
            return value;
        }
    }

    return "";
}
#endif

sf::Clock frameClock;

void Game::settings(bool& showSettings, int& moveSpeed, int& background, float& gapBetweenPipes, int& pipeColor, bool& showBoundingBoxes, float RGB[], int& birdColor, float& gravity, int& volume, bool& invincible, int& scoreMultiplier, float& scale, int MaxMemoryHistory, float memoryHistory[], int& memoryIndex)
{
    ImGui::Begin("Settings", &showSettings);

    ImGui::SliderInt("Flying Speed", &moveSpeed, 1, 7);

    ImGui::SliderFloat("Player Scale", &scale, 1, 2);

    ImGui::SliderFloat("Gap between Pipes", &gapBetweenPipes, 60.0, 140.0);

    ImGui::SliderFloat("Gravity", &gravity, 0.01, 1);

    ImGui::SliderInt("Score Multiplier", &scoreMultiplier, 1, 10);
    
    ImGui::NewLine();

    ImGui::Checkbox("Show Bounding Boxes", &showBoundingBoxes);
    ImGui::SameLine();
    ImGui::ColorEdit3("Box Color", RGB);

    ImGui::NewLine();

    ImGui::Checkbox("Invincible", &invincible);

    ImGui::NewLine();

    if (ImGui::Button("Reset Settings"))
    {
        moveSpeed = 3;
        background = 0;
        gapBetweenPipes = 150.0;
        pipeColor = 0;
        showBoundingBoxes = false;
        birdColor = 0;
        gravity = 0.25;
        invincible = false;
        scoreMultiplier = 1;
        scale = 1.0;
        RGB[0] = 1;
        RGB[1] = 0;
        RGB[2] = 0;
    }
        
    ImGui::NewLine();

    if (ImGui::CollapsingHeader("Assets"))
    {
        ImGui::RadioButton("Day Theme", &background, 0);
        ImGui::SameLine();
        ImGui::RadioButton("Night Theme", &background, 1);

        ImGui::RadioButton("Green Pipe", &pipeColor, 0);
        ImGui::SameLine();
        ImGui::RadioButton("Red Pipe", &pipeColor, 1);

        ImGui::RadioButton("Yellow Bird", &birdColor, 0);
        ImGui::SameLine();
        ImGui::RadioButton("Blue Bird", &birdColor, 1);
        ImGui::SameLine();
        ImGui::RadioButton("Red Bird", &birdColor, 2);

        ImGui::NewLine();

        ImGui::SliderInt("Volume", &volume, 0, 100);
    }

    if (ImGui::CollapsingHeader("Statistics"))
    {
        sf::Time elapsedTime = frameClock.restart();

        float deltaTime = elapsedTime.asSeconds();
        int fps = static_cast<int>(1.0f / deltaTime);

        ImGui::Text("FPS: %d", fps);

#ifdef _WIN32
        float currentMemoryUse = getMemoryUse();
        memoryHistory[memoryIndex] = static_cast<float>(currentMemoryUse);
        memoryIndex = (memoryIndex + 1) % MaxMemoryHistory;

        ImGui::Text("Current Memory usage: %.2f MB", currentMemoryUse);
        ImGui::PlotLines("", memoryHistory, MaxMemoryHistory, memoryIndex, "Memory Use", 0.0f, 100.0f, ImVec2(0, 80));
#else
        // Get total memory
        std::string totalMemory = readMeminfoValue("MemTotal");
        ImGui::Text("Total Memory %i MB", std::stoi(totalMemory) / 1024);

        // Get free memory
        std::string freeMemory = readMeminfoValue("MemFree");
        ImGui::Text("Free Memory %i MB", std::stoi(freeMemory) / 1024);

        // Get available memory
        std::string usedMemory = readMeminfoValue("MemAvailable");
        ImGui::Text("Available Memory %i MB", std::stoi(usedMemory) / 1024);

#endif
    }

    ImGui::End();
}

void Game::serialize(int moveSpeed, float gap, float gravity, int scoreMultiplier, bool box, int theme, int pipe, int bird, int volume, float scale, int highscore)
{
    std::ofstream settings("game/settings.json");

    Json::StyledWriter writer;

    Json::Value assets, data, root;
    data["speed"] = moveSpeed;
    data["gap"] = gap;
    data["gravity"] = gravity;
    data["scoreMultiplier"] = scoreMultiplier;
    data["showBoundingBox"] = box;
    data["scale"] = scale;

    assets["theme"] = theme;
    assets["pipe"] = pipe;
    assets["bird"] = bird;
    assets["volume"] = volume;
    assets["highscore"] = highscore;

    root["Settings"] = data;
    root["Assets"] = assets;

    settings << writer.write(root);

    settings.close();
}

void Game::deserialize(int& moveSpeed, float& gap, float& gravity, int& scoreMultiplier, bool& box, int& theme, int& pipe, int& bird, int& volume, float& scale, int& highscore)
{
    std::ifstream settings("game/settings.json");

    Json::Reader reader;

    Json::Value completeJsonData;

    reader.parse(settings, completeJsonData);

    moveSpeed = completeJsonData["Settings"]["speed"].asInt();
    gap = completeJsonData["Settings"]["gap"].asFloat();
    gravity = completeJsonData["Settings"]["gravity"].asFloat();
    scoreMultiplier = completeJsonData["Settings"]["scoreMultiplier"].asInt();
    box = completeJsonData["Settings"]["showBoundingBox"].asBool();
    scale = completeJsonData["Settings"]["scale"].asFloat();

    theme = completeJsonData["Assets"]["theme"].asInt();
    pipe = completeJsonData["Assets"]["pipe"].asInt();
    bird = completeJsonData["Assets"]["bird"].asInt();
    volume = completeJsonData["Assets"]["volume"].asInt();
    highscore = completeJsonData["Assets"]["highscore"].asInt();
}