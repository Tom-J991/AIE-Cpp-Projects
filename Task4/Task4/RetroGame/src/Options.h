#pragma once

#include <fstream>
#include <sstream>

#include <raylib.h>

// Compile variable declarations. use extern variables to access from other files.
namespace Options
{
	float g_MasterVolume = 0.5f;
	unsigned int g_ScreenWidth = GetScreenWidth();
	unsigned int g_ScreenHeight = GetScreenHeight();

	void ReadOptions();
	void WriteOptions();

}
