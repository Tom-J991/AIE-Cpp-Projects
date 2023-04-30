#include "Options.h"

namespace Options
{
	void ReadOptions()
	{
		std::ifstream optionsFile("./game_options.dat", std::ios::binary);
		if (!optionsFile.is_open())
		{
			WriteOptions();
			return;
		}

		optionsFile.read((char*)&g_MasterVolume, sizeof(float));
		optionsFile.close();
	}
	void WriteOptions()
	{
		std::ofstream optionsFile("./game_options.dat", std::ios::binary);

		optionsFile.write((char *)&g_MasterVolume, sizeof(float));
		optionsFile.close();
	}

}
