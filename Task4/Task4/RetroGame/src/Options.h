#pragma once

#include <fstream>
#include <sstream>

// Compile variable declarations. use extern variables to access from other files.
namespace Options
{
	float g_MasterVolume = 0.5f;

	void ReadOptions();
	void WriteOptions();

}
