#pragma once

#include <unordered_map>
#include <utility>

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
