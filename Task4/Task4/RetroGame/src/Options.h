#pragma once

#include <fstream>
#include <sstream>

#include <raylib.h>

#include "KeyMaps.h"

namespace Options
{
	inline float g_MasterVolume;

	inline bool g_Fullscreen;
	inline unsigned int g_ScreenWidth;
	inline unsigned int g_ScreenHeight;

	inline std::unordered_map<eGeneralKeys, KeyboardKey> g_GeneralKeys;
	inline std::unordered_map<ePongKeys, KeyboardKey> g_PongKeys;
	inline std::unordered_map<eSnakeKeys, KeyboardKey> g_SnakeKeys;

	void ReadOptions();
	void WriteOptions();

}
