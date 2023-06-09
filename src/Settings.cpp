#include "../include/Settings.h"

void Settings::settings(bool& showSettings, int& moveSpeed, int& background, float& gapBetweenPipes, int& pipeColor, bool& showBoundingBoxes, float RGB[], int& birdColor, float& gravity, int& volume, bool& invincible, int& scoreMultiplier, float& scale, int MaxMemoryHistory, float memoryHistory[], int& memoryIndex)
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
        // Get used memory
        std::string useMemory = readStatus("VmRSS", "/proc/self/status");
        // Get total memory
        std::string totalMemory = readStatus("MemFree", "/proc/meminfo");
        ImGui::Text("Total Memory: %i MB", std::stoi(totalMemory) / 1024);
        ImGui::Text("Memory usage: %i MB", std::stoi(useMemory) / 1024);

#endif
    }

    ImGui::End();
}

#ifdef _WIN32
float Settings::getMemoryUse()
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
std::string Settings::readStatus(const std::string& key, std::string fileName)
{
    std::ifstream file(fileName);
    std::string line;

    while (std::getline(file, line)) {
        if (line.find(key) != std::string::npos) {
            std::string value = line.substr(line.find(':') + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            return value;
        }
    }

    return "";
}
#endif

void Settings::deserialize(int& moveSpeed, float& gap, float& gravity, int& scoreMultiplier, bool& box, int& theme, int& pipe, int& bird, int& volume, float& scale, int& highscore)
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

void Settings::serialize(int moveSpeed, float gap, float gravity, int scoreMultiplier, bool box, int theme, int pipe, int bird, int volume, float scale, int highscore)
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