#include "Options.h"

namespace Options
{
	void ReadOptions()
	{
		std::ifstream optionsFile("./game_options.dat", std::ios::binary);
		if (!optionsFile.is_open())
		{
			// Set and Write Defaults
			g_GeneralKeys.insert(std::pair<eGeneralKeys, KeyboardKey>(eGeneralKeys::MENU_UP, KEY_UP));
			g_GeneralKeys.insert(std::pair<eGeneralKeys, KeyboardKey>(eGeneralKeys::MENU_DOWN, KEY_DOWN));
			g_GeneralKeys.insert(std::pair<eGeneralKeys, KeyboardKey>(eGeneralKeys::MENU_LEFT, KEY_LEFT));
			g_GeneralKeys.insert(std::pair<eGeneralKeys, KeyboardKey>(eGeneralKeys::MENU_RIGHT, KEY_RIGHT));
			g_GeneralKeys.insert(std::pair<eGeneralKeys, KeyboardKey>(eGeneralKeys::MENU_ACCEPT, KEY_ENTER));
			g_GeneralKeys.insert(std::pair<eGeneralKeys, KeyboardKey>(eGeneralKeys::MENU_BACK, KEY_ESCAPE));

			g_PongKeys.insert(std::pair<ePongKeys, KeyboardKey>(ePongKeys::FIRSTPLAYER_UP, KEY_W));
			g_PongKeys.insert(std::pair<ePongKeys, KeyboardKey>(ePongKeys::FIRSTPLAYER_DOWN, KEY_S));
			g_PongKeys.insert(std::pair<ePongKeys, KeyboardKey>(ePongKeys::SECONDPLAYER_UP, KEY_UP));
			g_PongKeys.insert(std::pair<ePongKeys, KeyboardKey>(ePongKeys::SECONDPLAYER_DOWN, KEY_DOWN));
			g_PongKeys.insert(std::pair<ePongKeys, KeyboardKey>(ePongKeys::QUITGAME, KEY_ESCAPE));

			// TODO

			WriteOptions();
			return;
		}
		// Read from File.
		optionsFile.read((char*)&g_MasterVolume, sizeof(float));
		optionsFile.read((char*)&g_ScreenWidth, sizeof(unsigned int));
		optionsFile.read((char*)&g_ScreenHeight, sizeof(unsigned int));
		optionsFile.close();
	}
	void WriteOptions()
	{
		std::ofstream optionsFile("./game_options.dat", std::ios::binary);

		optionsFile.write((char*)&g_MasterVolume, sizeof(float));
		optionsFile.write((char*)&g_ScreenWidth, sizeof(unsigned int));
		optionsFile.write((char*)&g_ScreenHeight, sizeof(unsigned int));
		optionsFile.close();
	}

}
