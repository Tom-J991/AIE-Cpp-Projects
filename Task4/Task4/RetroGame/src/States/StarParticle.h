#pragma once

#include <raylib.h>

struct Star
{
	Vector2 position = { -1, -1 };
	float speed = 128;
	float radius = 12;
	float brightness = 1;

	void Init();
};
