#pragma once

#include <fstream>
#include <sstream>

#include <unordered_map>
#include <utility>

#include <raylib.h>

// Compile variable declarations. use extern variables to access from other files.
namespace Options
{
	enum class eGeneralKeys
	{
		MENU_UP = 0,
		MENU_DOWN,
		MENU_LEFT,
		MENU_RIGHT,
		MENU_ACCEPT,
		MENU_BACK,
		KEYS_MAX
	};
	enum class ePongKeys
	{
		FIRSTPLAYER_UP = 0,
		FIRSTPLAYER_DOWN,
		SECONDPLAYER_UP,
		SECONDPLAYER_DOWN,
		QUITGAME,
		KEYS_MAX
	};
	enum class eSnakeKeys
	{
		MOVE_UP = 0,
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT,
		QUITGAME,
		KEYS_MAX
	};

	float g_MasterVolume = 0.5f;
	unsigned int g_ScreenWidth = GetScreenWidth();
	unsigned int g_ScreenHeight = GetScreenHeight();

	std::unordered_map<eGeneralKeys, KeyboardKey> g_GeneralKeys;
	std::unordered_map<ePongKeys, KeyboardKey> g_PongKeys;
	std::unordered_map<eSnakeKeys, KeyboardKey> g_SnakeKeys;

	void ReadOptions();
	void WriteOptions();

}
