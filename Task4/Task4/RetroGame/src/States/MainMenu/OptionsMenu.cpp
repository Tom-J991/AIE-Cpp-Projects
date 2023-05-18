#include "OptionsMenu.h"

#include "MainMenu.h"
#include "KeymapMenu.h"

// Globals.
#include "KeyMaps.h"
namespace Options
{
	extern float g_MasterVolume;

	extern bool g_Fullscreen;
	extern unsigned int g_ScreenWidth;
	extern unsigned int g_ScreenHeight;

	extern std::unordered_map<eGeneralKeys, KeyboardKey> g_GeneralKeys;

	extern void WriteOptions();
}
using namespace Options;

OptionsMenuState::OptionsMenuState()
{ 
	MenuState::MenuState();

	// Initalize Options
	m_options.insert(std::pair<eOptions, std::string>(eOptions::MASTER_VOLUME, "Master Volume: "));
	m_options.insert(std::pair<eOptions, std::string>(eOptions::RESOLUTION, "Resolution: "));
	m_options.insert(std::pair<eOptions, std::string>(eOptions::FULLSCREEN, "Go Fullscreen"));
	m_options.insert(std::pair<eOptions, std::string>(eOptions::KEYMAP, "Change Keys"));
	m_options.insert(std::pair<eOptions, std::string>(eOptions::BACK, "Go Back"));

	// Initialize Resolutions List
	m_resolutions.push_back(std::pair<std::string, Vector2>("640, 360", { 640, 360 }));
	m_resolutions.push_back(std::pair<std::string, Vector2>("640, 480", { 640, 480 }));
	m_resolutions.push_back(std::pair<std::string, Vector2>("800, 600", { 800, 600 }));
	m_resolutions.push_back(std::pair<std::string, Vector2>("960, 540", { 960, 540 }));
	m_resolutions.push_back(std::pair<std::string, Vector2>("1024, 768", { 1024, 768 }));
	m_resolutions.push_back(std::pair<std::string, Vector2>("1280, 720", { 1280, 720 }));
	m_resolutions.push_back(std::pair<std::string, Vector2>("1366, 768", { 1366, 768 }));
	m_resolutions.push_back(std::pair<std::string, Vector2>("1400, 1080", { 1400, 1080 }));
	m_resolutions.push_back(std::pair<std::string, Vector2>("1600, 900", { 1600, 900 }));
	m_resolutions.push_back(std::pair<std::string, Vector2>("1920, 1080", { 1920, 1080 }));

	int i = 0;
	for (auto const &[key, val] : m_resolutions)
	{
		if (g_ScreenWidth == val.x && g_ScreenHeight == val.y)
			m_resolutionIndex = i;
		i++;
	}

	if (IsWindowFullscreen())
		m_options[eOptions::FULLSCREEN] = "Go Windowed";
	else
		m_options[eOptions::FULLSCREEN] = "Go Fullscreen";
}
OptionsMenuState::~OptionsMenuState()
{ 
	MenuState::~MenuState();
}

void OptionsMenuState::OnEnter()
{
	MenuState::OnEnter();

	m_activeIndex = -1;
}
void OptionsMenuState::OnExit()
{
	MenuState::OnEnter();
}

bool changeVolume = false;
bool changeResolution = false;
bool resolutionChanged = false;
bool OptionsMenuState::Update(float deltaTime)
{
	if (!MenuState::Update(deltaTime))
		return false;

	// Options
	if (changeVolume)
	{
		int dir = IsKeyPressed(g_GeneralKeys[eGeneralKeys::MENU_RIGHT]) - IsKeyPressed(g_GeneralKeys[eGeneralKeys::MENU_LEFT]); // Left or Right.
		g_MasterVolume += 0.1f * dir;
		g_MasterVolume = Clamp(g_MasterVolume, 0, 1);
		g_MasterVolume = (float)(std::trunc(g_MasterVolume * 10) / 10); // 1 decimal
		SetMasterVolume(g_MasterVolume);
	}

	if (changeResolution)
	{
		int dir = IsKeyPressed(g_GeneralKeys[eGeneralKeys::MENU_RIGHT]) - IsKeyPressed(g_GeneralKeys[eGeneralKeys::MENU_LEFT]); // Left or Right.
		m_resolutionIndex += dir;
		if (m_resolutionIndex < 0)
			m_resolutionIndex = (int)m_resolutions.size()-1;
		if (m_resolutionIndex >= m_resolutions.size())
			m_resolutionIndex = 0;
		resolutionChanged = true;
	}

	if (IsWindowFullscreen())
		m_options[eOptions::FULLSCREEN] = "Go Windowed";
	else
		m_options[eOptions::FULLSCREEN] = "Go Fullscreen";

	if (IsKeyReleased(g_GeneralKeys[eGeneralKeys::MENU_ACCEPT]))
	{
		switch (m_index)
		{
			case (int)eOptions::MASTER_VOLUME:
			{
				changeVolume = !changeVolume;
				if (changeVolume)
					m_activeIndex = m_index;
				else
					m_activeIndex = -1;
			} break;
			case (int)eOptions::RESOLUTION:
			{
				changeResolution = !changeResolution;
				if (changeResolution)
					m_activeIndex = m_index;
				else
					m_activeIndex = -1;
				if (resolutionChanged)
				{
					if (g_Fullscreen)
						ToggleFullscreen();
					Vector2 r = m_resolutions[m_resolutionIndex].second;
					g_ScreenWidth = (unsigned int)r.x;
					g_ScreenHeight = (unsigned int)r.y;
					SetWindowSize((int)r.x, (int)r.y);
					const int monitor = GetCurrentMonitor();
					const int mWidth = GetMonitorWidth(monitor);
					const int mHeight = GetMonitorHeight(monitor);
					SetWindowPosition(mWidth/2 - GetScreenWidth()/2, mHeight/2 - GetScreenHeight()/2);
					for (Star &star : *m_particles)
					{
						star.Init();
						star.position.x = (float)GetRandomValue(-1, GetScreenWidth() * 2);
					}
					if (g_Fullscreen)
						ToggleFullscreen();
					resolutionChanged = false;
				}
			} break;
			case (int)eOptions::FULLSCREEN:
			{
				g_Fullscreen = !g_Fullscreen;
				ToggleFullscreen();
			} break;
			case (int)eOptions::KEYMAP:
			{
				WriteOptions();
				m_isTransition = true;
				m_transitionDest = eGameState::KEYMAP;
			} break;
			case (int)eOptions::BACK:
			{
				WriteOptions();
				m_isTransition = true;
				m_transitionDest = eGameState::MENU;
			} break;
			default:
				break;
		}
	}
	if (changeVolume || changeResolution)
		return false;

	if (IsKeyReleased(g_GeneralKeys[eGeneralKeys::MENU_BACK]))
	{
		WriteOptions();
		m_isTransition = true;
		m_transitionDest = eGameState::MENU;
	}

	int dir = IsKeyPressed(g_GeneralKeys[eGeneralKeys::MENU_DOWN]) - IsKeyPressed(g_GeneralKeys[eGeneralKeys::MENU_UP]); // Up or Down.
	m_index += dir;

	if (m_index < 0) // Clamp Direction
		m_index = (int)eOptions::OPTIONS_MAX - 1;
	if (m_index >= (int)eOptions::OPTIONS_MAX)
		m_index = 0;

	return true;
}
void OptionsMenuState::Draw()
{
	BeginDrawing();
	ClearBackground(BLACK);
	{
		MenuState::DrawParticles();
		// Options
		for (int i = 0; i < (int)eOptions::OPTIONS_MAX; i++)
		{
			bool j = m_index == i;

			std::stringstream optionText;
			const char *option = m_options[(eOptions)i].c_str();
			if (j) optionText << "> ";
			optionText << option;

			switch (i)
			{
				case (int)eOptions::MASTER_VOLUME:
				{
					optionText << g_MasterVolume;
				} break;
				case (int)eOptions::RESOLUTION:
				{
					optionText << "[ " << m_resolutions[m_resolutionIndex].first << " ]";
				} break;
				default:
					break;
			}

			const int fontSize = (m_activeIndex == i) ? 28 : 24;
			int optionOff = MeasureText(optionText.str().c_str(), fontSize) / 2;
			int x = GetScreenWidth()/2 - optionOff;
			const int listHeight = (fontSize*(int)eOptions::OPTIONS_MAX);
			int y = GetScreenHeight()/2 + (i*32) - listHeight/2;
			if (j)
			{
				// Wobble when highlighted.
				x += (int)(sinf((float)GetTime() * 8) * 4);
				y += (int)(-cosf((float)GetTime() * 8) * 4);
			}
			DrawText(optionText.str().c_str(), (int)m_menuOffset + x, y, fontSize, WHITE);
		}
	}
	EndDrawing();
}

bool OptionsMenuState::MenuTransition(const eGameState &state, float deltaTime)
{
	if (MenuState::MenuTransition(state, deltaTime))
	{
		switch (state)
		{
			case eGameState::MENU:
			{
				auto *state = (MainMenuState *)(Game::Get().GetState((int)eGameState::MENU));
				state->PassParticles(m_particles);
				state->PassMusic(m_titleMusic);
				Game::Get().ChangeState(eGameState::MENU);
			} break;
			case eGameState::KEYMAP:
			{
				auto *state = (KeymapMenuState *)(Game::Get().GetState((int)eGameState::KEYMAP));
				state->PassParticles(m_particles);
				state->PassMusic(m_titleMusic);
				Game::Get().ChangeState(eGameState::KEYMAP);
			} break;
			default:
				break;
		}
	}
	return true;
}
