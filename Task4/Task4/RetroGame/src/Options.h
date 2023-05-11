#pragma once

#include <fstream>
#include <sstream>

#include <raylib.h>

#include "KeyMaps.h"

// Compile variable declarations. use extern variables to access from other files.
namespace Options
{
	float g_MasterVolume;

	bool g_Fullscreen;
	unsigned int g_ScreenWidth;
	unsigned int g_ScreenHeight;

	std::unordered_map<eGeneralKeys, KeyboardKey> g_GeneralKeys;
	std::unordered_map<ePongKeys, KeyboardKey> g_PongKeys;
	std::unordered_map<eSnakeKeys, KeyboardKey> g_SnakeKeys;

	void ReadOptions();
	void WriteOptions();

}
