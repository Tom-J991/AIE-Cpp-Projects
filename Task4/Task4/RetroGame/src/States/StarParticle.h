#pragma once

#include <raylib.h>

// Star particle object for menu background.
struct Star
{
	Vector2 position = { -1, -1 };
	float speed = 128;
	float radius = 12;
	float brightness = 1;

	inline void Init()
	{
		position.x = (float)GetRandomValue(-GetScreenWidth(), -1);
		position.y = (float)GetRandomValue(0, GetScreenHeight());
		radius = (float)GetRandomValue(1, 4);
		brightness = radius / 6;
		speed = radius * 16;
	}
};
