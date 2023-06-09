#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include "../imgui/imgui.h"
#include "../imgui/imgui-SFML.h"

#include "Globals.h"

class Settings
{
public:
	Settings() = default;

	void settings(bool&, int&, int&, float&, int&, bool&, float[], int&, float&, int&, bool&, int&, float&, int, float[], int&);

	void deserialize(int&, float&, float&, int&, bool&, int&, int&, int&, int&, float&, int&);

	void serialize(int, float, float, int, bool, int, int, int, int, float, int);

#ifdef _WIN32
	float getMemoryUse();
#else
	std::string readStatus(const std::string& key, std::string fileName);
#endif
private:
	sf::Clock frameClock;
};

#endif