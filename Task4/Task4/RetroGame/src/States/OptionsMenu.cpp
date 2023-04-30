#include "OptionsMenu.h"

#include "MainMenu.h"

// Globals.
namespace Options
{
	extern float g_MasterVolume;
	extern void WriteOptions();
}

OptionsMenuState::OptionsMenuState()
{ 
	m_options.insert(std::pair<eOptionParameters, std::string>(eOptionParameters::MASTER_VOLUME, "Master Volume: "));
	m_options.insert(std::pair<eOptionParameters, std::string>(eOptionParameters::BACK, "Go Back"));

	m_optionsBold.insert(std::pair<eOptionParameters, bool>(eOptionParameters::MASTER_VOLUME, false));
	m_optionsBold.insert(std::pair<eOptionParameters, bool>(eOptionParameters::BACK, false));
}
OptionsMenuState::~OptionsMenuState()
{ }

void OptionsMenuState::OnEnter()
{
	m_isReturning = true;
}
void OptionsMenuState::OnExit()
{
}

bool changeVolume = false;
void OptionsMenuState::Update(float deltaTime)
{
	if (IsMusicReady(m_titleMusic))
		UpdateMusicStream(m_titleMusic);

	// Background Particles
	for (Star &star : m_particles)
	{
		if (star.position.x > GetScreenWidth())
			star.Init();

		star.position.x += star.speed * deltaTime;
	}

	// Transition
	if (m_isReturning)
	{
		m_menuOffset = Lerp(m_menuOffset, 0.0f, 8.0f * deltaTime);
		if (m_menuOffset >= -1.0f)
		{
			m_menuOffset = 0.0f;
			m_isReturning = false;
		}
		return;
	}
	if (m_isTransition)
	{
		MenuTransition(m_transitionDest, deltaTime);
		return;
	}

	// Options
	if (changeVolume)
	{
		int dir = (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) - (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)); // Left or Right.
		Options::g_MasterVolume += dir * 0.1f;
		Options::g_MasterVolume = Clamp(Options::g_MasterVolume, 0, 1);
		SetMasterVolume(Options::g_MasterVolume);
		Options::WriteOptions();
	}

	if (IsKeyReleased(KEY_ENTER))
	{
		switch (m_index)
		{
			case (int)eOptionParameters::MASTER_VOLUME:
			{
				changeVolume = !changeVolume;
				m_optionsBold[eOptionParameters::MASTER_VOLUME] = !m_optionsBold[eOptionParameters::MASTER_VOLUME];
			} break;
			case (int)eOptionParameters::BACK:
			{
				m_isTransition = true;
				m_transitionDest = eGameState::MENU;
			} break;
			default:
				break;
		}
	}
	if (changeVolume)
		return;

	if (IsKeyReleased(KEY_ESCAPE))
	{
		m_isTransition = true;
		m_transitionDest = eGameState::MENU;
	}

	int dir = (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) - (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)); // Up or Down.
	m_index += dir;

	if (m_index < 0) // Clamp Direction
		m_index = (int)eOptionParameters::OPTIONS_MAX - 1;
	if (m_index >= (int)eOptionParameters::OPTIONS_MAX)
		m_index = 0;
}
void OptionsMenuState::Draw()
{
	BeginDrawing();
	ClearBackground(BLACK);
	{
		// Background Particles
		for (const Star &star : m_particles)
		{
			const Color c = ColorFromHSV(0, 0, star.brightness);
			DrawRectangle((int)star.position.x, (int)star.position.y, (int)star.radius, (int)star.radius, c);
		}
		// Options
		for (int i = 0; i < (int)eOptionParameters::OPTIONS_MAX; i++)
		{
			bool j = m_index == i;

			std::stringstream optionText;
			const char *option = m_options[(eOptionParameters)i].c_str();
			if (j) optionText << "> ";
			optionText << option;

			switch (i)
			{
				case (int)eOptionParameters::MASTER_VOLUME:
				{
					optionText << Options::g_MasterVolume;
				} break;
				default:
					break;
			}

			const int fontSize = m_optionsBold[(eOptionParameters)i] ? 28 : 24;
			int optionOff = MeasureText(optionText.str().c_str(), fontSize) / 2;
			DrawText(optionText.str().c_str(), m_menuOffset + GetScreenWidth() / 2 - optionOff, GetScreenHeight() / 2 + (i * 32), fontSize, WHITE);
		}
	}
	EndDrawing();
}

void OptionsMenuState::MenuTransition(const eGameState &state, float deltaTime)
{
	m_menuOffset = Lerp(m_menuOffset, (float)-GetScreenWidth(), 6.0f * deltaTime);
	if (m_menuOffset <= -GetScreenWidth() + 12.0f)
	{
		m_menuOffset = (float)-GetScreenWidth();
		m_isTransition = false;
		switch (state)
		{
			case eGameState::MENU:
			{
				auto *state = (MainMenuState*)(Game::Get().GetState((int)eGameState::MENU));
				state->SetParticles(m_particles);
				state->SetMusic(m_titleMusic);
				Game::Get().ChangeState(eGameState::MENU);
			} break;
			default:
				break;
		}
	}
}
