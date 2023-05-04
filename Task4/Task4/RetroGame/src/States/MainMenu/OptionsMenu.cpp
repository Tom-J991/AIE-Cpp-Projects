#include "OptionsMenu.h"

#include "MainMenu.h"

#include <iomanip>

// Globals.
namespace Options
{
	extern float g_MasterVolume;
	extern void WriteOptions();
}

OptionsMenuState::OptionsMenuState()
{ 
	MenuState::MenuState();

	m_options.insert(std::pair<eOptions, std::string>(eOptions::MASTER_VOLUME, "Master Volume: "));
	m_options.insert(std::pair<eOptions, std::string>(eOptions::BACK, "Go Back"));

	m_optionsBold.insert(std::pair<eOptions, bool>(eOptions::MASTER_VOLUME, false));
	m_optionsBold.insert(std::pair<eOptions, bool>(eOptions::BACK, false));
}
OptionsMenuState::~OptionsMenuState()
{ 
	MenuState::~MenuState();
}

void OptionsMenuState::OnEnter()
{
	MenuState::OnEnter();
}
void OptionsMenuState::OnExit()
{
	MenuState::OnEnter();
}

bool changeVolume = false;
bool OptionsMenuState::Update(float deltaTime)
{
	if (!MenuState::Update(deltaTime))
		return false;

	// Options
	if (changeVolume)
	{
		int dir = (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) - (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)); // Left or Right.
		Options::g_MasterVolume += 0.1f * dir;
		Options::g_MasterVolume = Clamp(Options::g_MasterVolume, 0, 1);
		Options::g_MasterVolume = (float)(std::trunc(Options::g_MasterVolume * 10) / 10); // 1 decimal
		std::cout << Options::g_MasterVolume << std::endl;
		SetMasterVolume(Options::g_MasterVolume);
	}

	if (IsKeyReleased(KEY_ENTER))
	{
		switch (m_index)
		{
			case (int)eOptions::MASTER_VOLUME:
			{
				changeVolume = !changeVolume;
				m_optionsBold[eOptions::MASTER_VOLUME] = !m_optionsBold[eOptions::MASTER_VOLUME];
			} break;
			case (int)eOptions::BACK:
			{
				Options::WriteOptions();
				m_isTransition = true;
				m_transitionDest = eGameState::MENU;
			} break;
			default:
				break;
		}
	}
	if (changeVolume)
		return false;

	if (IsKeyReleased(KEY_ESCAPE))
	{
		m_isTransition = true;
		m_transitionDest = eGameState::MENU;
	}

	int dir = (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) - (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)); // Up or Down.
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
					optionText << Options::g_MasterVolume;
				} break;
				default:
					break;
			}

			const int fontSize = m_optionsBold[(eOptions)i] ? 28 : 24;
			int optionOff = MeasureText(optionText.str().c_str(), fontSize) / 2;
			DrawText(optionText.str().c_str(), (int)m_menuOffset + GetScreenWidth() / 2 - optionOff, GetScreenHeight() / 2 + (i * 32), fontSize, WHITE);
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
			default:
				break;
		}
	}
	return true;
}
