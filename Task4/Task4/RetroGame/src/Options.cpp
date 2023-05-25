#include "Options.h"

namespace Options
{
	void ReadOptions()
	{
		std::ifstream optionsFile("./game_options.dat", std::ios::binary);
		if (!optionsFile.is_open()) // Can't read file, and/or file doesn't exist.
		{
			optionsFile.close();
			// Set and Write Defaults

			// Settings
			g_MasterVolume = 0.5f;

			g_Fullscreen = false;
			g_ScreenWidth = GetScreenWidth();
			g_ScreenHeight = GetScreenHeight();

			// Key-Mapping
			g_GeneralKeys.insert(std::pair<eGeneralKeys, KeyboardKey>(eGeneralKeys::MENU_UP, KEY_UP));
			g_GeneralKeys.insert(std::pair<eGeneralKeys, KeyboardKey>(eGeneralKeys::MENU_DOWN, KEY_DOWN));
			g_GeneralKeys.insert(std::pair<eGeneralKeys, KeyboardKey>(eGeneralKeys::MENU_LEFT, KEY_LEFT));
			g_GeneralKeys.insert(std::pair<eGeneralKeys, KeyboardKey>(eGeneralKeys::MENU_RIGHT, KEY_RIGHT));
			g_GeneralKeys.insert(std::pair<eGeneralKeys, KeyboardKey>(eGeneralKeys::MENU_ACCEPT, KEY_ENTER));
			g_GeneralKeys.insert(std::pair<eGeneralKeys, KeyboardKey>(eGeneralKeys::MENU_BACK, KEY_ESCAPE));
			// Pong
			g_PongKeys.insert(std::pair<ePongKeys, KeyboardKey>(ePongKeys::FIRSTPLAYER_UP, KEY_W));
			g_PongKeys.insert(std::pair<ePongKeys, KeyboardKey>(ePongKeys::FIRSTPLAYER_DOWN, KEY_S));
			g_PongKeys.insert(std::pair<ePongKeys, KeyboardKey>(ePongKeys::SECONDPLAYER_UP, KEY_UP));
			g_PongKeys.insert(std::pair<ePongKeys, KeyboardKey>(ePongKeys::SECONDPLAYER_DOWN, KEY_DOWN));
			g_PongKeys.insert(std::pair<ePongKeys, KeyboardKey>(ePongKeys::QUITGAME, KEY_ESCAPE));
			// Snake
			g_SnakeKeys.insert(std::pair<eSnakeKeys, KeyboardKey>(eSnakeKeys::MOVE_UP, KEY_UP));
			g_SnakeKeys.insert(std::pair<eSnakeKeys, KeyboardKey>(eSnakeKeys::MOVE_LEFT, KEY_LEFT));
			g_SnakeKeys.insert(std::pair<eSnakeKeys, KeyboardKey>(eSnakeKeys::MOVE_RIGHT, KEY_RIGHT));
			g_SnakeKeys.insert(std::pair<eSnakeKeys, KeyboardKey>(eSnakeKeys::MOVE_DOWN, KEY_DOWN));
			g_SnakeKeys.insert(std::pair<eSnakeKeys, KeyboardKey>(eSnakeKeys::QUITGAME, KEY_ESCAPE));
			g_SnakeKeys.insert(std::pair<eSnakeKeys, KeyboardKey>(eSnakeKeys::NEWGAME, KEY_ENTER));

			WriteOptions();
			return;
		}

		// Read from File.
		// 
		// 0x00-0x03	: 4 Bytes			: Master Volume		: Float
		// 0x04			: 1 Byte			: Fullscreen		: Boolean
		// 0x05-0x08	: 4 Bytes			: Screen Width		: Unsigned Integer
		// 0x09-0x0C	: 4 Bytes			: Screen Height		: Unsigned Integer
		// 0x0D-EOF		: 4 Bytes (per key)	: Key-Map			: KeyboardKey (rayLib enum)
		// 
		// Settings
		optionsFile.read((char*)&g_MasterVolume, sizeof(float));

		optionsFile.read((char*)&g_Fullscreen, sizeof(bool));
		optionsFile.read((char*)&g_ScreenWidth, sizeof(unsigned int));
		optionsFile.read((char*)&g_ScreenHeight, sizeof(unsigned int));

		// Key-Mapping
		optionsFile.read((char*)&g_GeneralKeys[eGeneralKeys::MENU_UP], sizeof(KeyboardKey));
		optionsFile.read((char*)&g_GeneralKeys[eGeneralKeys::MENU_DOWN], sizeof(KeyboardKey));
		optionsFile.read((char*)&g_GeneralKeys[eGeneralKeys::MENU_LEFT], sizeof(KeyboardKey));
		optionsFile.read((char*)&g_GeneralKeys[eGeneralKeys::MENU_RIGHT], sizeof(KeyboardKey));
		optionsFile.read((char*)&g_GeneralKeys[eGeneralKeys::MENU_ACCEPT], sizeof(KeyboardKey));
		optionsFile.read((char*)&g_GeneralKeys[eGeneralKeys::MENU_BACK], sizeof(KeyboardKey));
		// Pong
		optionsFile.read((char*)&g_PongKeys[ePongKeys::FIRSTPLAYER_UP], sizeof(KeyboardKey));
		optionsFile.read((char*)&g_PongKeys[ePongKeys::FIRSTPLAYER_DOWN], sizeof(KeyboardKey));
		optionsFile.read((char*)&g_PongKeys[ePongKeys::SECONDPLAYER_UP], sizeof(KeyboardKey));
		optionsFile.read((char*)&g_PongKeys[ePongKeys::SECONDPLAYER_DOWN], sizeof(KeyboardKey));
		optionsFile.read((char*)&g_PongKeys[ePongKeys::QUITGAME], sizeof(KeyboardKey));
		// Snake
		optionsFile.read((char*)&g_SnakeKeys[eSnakeKeys::MOVE_UP], sizeof(KeyboardKey));
		optionsFile.read((char*)&g_SnakeKeys[eSnakeKeys::MOVE_DOWN], sizeof(KeyboardKey));
		optionsFile.read((char*)&g_SnakeKeys[eSnakeKeys::MOVE_LEFT], sizeof(KeyboardKey));
		optionsFile.read((char*)&g_SnakeKeys[eSnakeKeys::MOVE_RIGHT], sizeof(KeyboardKey));
		optionsFile.read((char*)&g_SnakeKeys[eSnakeKeys::QUITGAME], sizeof(KeyboardKey));
		optionsFile.read((char*)&g_SnakeKeys[eSnakeKeys::NEWGAME], sizeof(KeyboardKey));

		optionsFile.close();
	}
	void WriteOptions()
	{
		std::ofstream optionsFile("./game_options.dat", std::ios::binary);

		// Settings
		optionsFile.write((char*)&g_MasterVolume, sizeof(float));

		optionsFile.write((char*)&g_Fullscreen, sizeof(bool));
		optionsFile.write((char*)&g_ScreenWidth, sizeof(unsigned int));
		optionsFile.write((char*)&g_ScreenHeight, sizeof(unsigned int));

		// Key-Mapping
		optionsFile.write((char*)&g_GeneralKeys[eGeneralKeys::MENU_UP], sizeof(KeyboardKey));
		optionsFile.write((char*)&g_GeneralKeys[eGeneralKeys::MENU_DOWN], sizeof(KeyboardKey));
		optionsFile.write((char*)&g_GeneralKeys[eGeneralKeys::MENU_LEFT], sizeof(KeyboardKey));
		optionsFile.write((char*)&g_GeneralKeys[eGeneralKeys::MENU_RIGHT], sizeof(KeyboardKey));
		optionsFile.write((char*)&g_GeneralKeys[eGeneralKeys::MENU_ACCEPT], sizeof(KeyboardKey));
		optionsFile.write((char*)&g_GeneralKeys[eGeneralKeys::MENU_BACK], sizeof(KeyboardKey));
		// Pong
		optionsFile.write((char*)&g_PongKeys[ePongKeys::FIRSTPLAYER_UP], sizeof(KeyboardKey));
		optionsFile.write((char*)&g_PongKeys[ePongKeys::FIRSTPLAYER_DOWN], sizeof(KeyboardKey));
		optionsFile.write((char*)&g_PongKeys[ePongKeys::SECONDPLAYER_UP], sizeof(KeyboardKey));
		optionsFile.write((char*)&g_PongKeys[ePongKeys::SECONDPLAYER_DOWN], sizeof(KeyboardKey));
		optionsFile.write((char*)&g_PongKeys[ePongKeys::QUITGAME], sizeof(KeyboardKey));
		// Snake
		optionsFile.write((char*)&g_SnakeKeys[eSnakeKeys::MOVE_UP], sizeof(KeyboardKey));
		optionsFile.write((char*)&g_SnakeKeys[eSnakeKeys::MOVE_DOWN], sizeof(KeyboardKey));
		optionsFile.write((char*)&g_SnakeKeys[eSnakeKeys::MOVE_LEFT], sizeof(KeyboardKey));
		optionsFile.write((char*)&g_SnakeKeys[eSnakeKeys::MOVE_RIGHT], sizeof(KeyboardKey));
		optionsFile.write((char*)&g_SnakeKeys[eSnakeKeys::QUITGAME], sizeof(KeyboardKey));
		optionsFile.write((char*)&g_SnakeKeys[eSnakeKeys::NEWGAME], sizeof(KeyboardKey));

		optionsFile.close();
	}

}
