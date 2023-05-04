#pragma once

#include <fstream>
#include <sstream>

// Compile variable declarations. use extern variables to access from other files.
namespace Options
{
	float g_MasterVolume = 0.5f;
	unsigned int g_ScreenWidth = 800;
	unsigned int g_ScreenHeight = 600;

	void ReadOptions();
	void WriteOptions();

}
