#include "KeymapMenu.h"

#include "OptionsMenu.h"

// Globals.
namespace Options
{
	extern std::unordered_map<eGeneralKeys, KeyboardKey> g_GeneralKeys;
	extern std::unordered_map<ePongKeys, KeyboardKey> g_PongKeys;
	extern std::unordered_map<eSnakeKeys, KeyboardKey> g_SnakeKeys;

	extern void WriteOptions();
}
using namespace Options;

KeymapMenuState::KeymapMenuState()
{
	MenuState::MenuState();

	// Initalize Options
	m_options.insert(std::pair<eKeyOptions, std::string>(eKeyOptions::CATEGORY, "CATEGORY: "));
	m_options.insert(std::pair<eKeyOptions, std::string>(eKeyOptions::BACK, "Go Back"));

	m_category.insert(std::pair<eKeyCategory, std::string>(eKeyCategory::GENERAL, "GENERAL"));
	m_category.insert(std::pair<eKeyCategory, std::string>(eKeyCategory::PONG, "PONG"));
	m_category.insert(std::pair<eKeyCategory, std::string>(eKeyCategory::SNAKE, "SNAKE"));
}
KeymapMenuState::~KeymapMenuState()
{
	MenuState::~MenuState();
}

void KeymapMenuState::OnEnter()
{
	MenuState::OnEnter();

	m_activeIndex = -1;

	m_currentCategory = eKeyCategory::GENERAL;
	switch (m_currentCategory)
	{
		case eKeyCategory::GENERAL:
		{
			m_maxOptions = (int)eGeneralKeys::KEYS_MAX + (int)eKeyOptions::OPTIONS_MAX;
		} break;
		case eKeyCategory::PONG:
		{
			m_maxOptions = (int)ePongKeys::KEYS_MAX + (int)eKeyOptions::OPTIONS_MAX;
		} break;
		case eKeyCategory::SNAKE:
		{
			m_maxOptions = (int)eSnakeKeys::KEYS_MAX + (int)eKeyOptions::OPTIONS_MAX;
		} break;
		default:
		{
			m_maxOptions = (int)eKeyOptions::OPTIONS_MAX;
		} break;
	}
}
void KeymapMenuState::OnExit()
{
	MenuState::OnEnter();
}

bool changeCategory = false;
bool KeymapMenuState::Update(float deltaTime)
{
	if (!MenuState::Update(deltaTime))
		return false;

	// Options
	if (changeCategory)
	{
		int dir = IsKeyPressed(g_GeneralKeys[eGeneralKeys::MENU_RIGHT]) - IsKeyPressed(g_GeneralKeys[eGeneralKeys::MENU_LEFT]); // Left or Right.
		m_currentCategory = (eKeyCategory)((int)m_currentCategory + dir);
		if ((int)m_currentCategory < 0)
			m_currentCategory = (eKeyCategory)((int)eKeyCategory::KEYMAP_MAX - 1);
		if ((int)m_currentCategory >= (int)eKeyCategory::KEYMAP_MAX)
			m_currentCategory = (eKeyCategory)0;
	}

	if (IsKeyReleased(g_GeneralKeys[eGeneralKeys::MENU_ACCEPT]))
	{
		switch (m_index)
		{
			case (int)eKeyOptions::CATEGORY:
			{
				changeCategory = !changeCategory;
				if (changeCategory)
					m_activeIndex = m_index;
				else
					m_activeIndex = -1;
			} break;
			case (int)eKeyOptions::BACK:
			{
				WriteOptions();
				m_isTransition = true;
				m_transitionDest = eGameState::OPTIONS;
			} break;
			default:
				break;
		}
	}
	if (changeCategory)
		return false;

	if (IsKeyReleased(g_GeneralKeys[eGeneralKeys::MENU_BACK]))
	{
		WriteOptions();
		m_isTransition = true;
		m_transitionDest = eGameState::OPTIONS;
	}

	int dir = IsKeyPressed(g_GeneralKeys[eGeneralKeys::MENU_DOWN]) - IsKeyPressed(g_GeneralKeys[eGeneralKeys::MENU_UP]); // Up or Down.
	m_index += dir;

	if (m_index < 0) // Clamp Direction
		m_index = m_maxOptions-1;
	if (m_index >= m_maxOptions)
		m_index = 0;

	return true;
}
void KeymapMenuState::Draw()
{
	BeginDrawing();
	ClearBackground(BLACK);
	{
		MenuState::DrawParticles();
		// Key-Map
		for (int i = 0; i < m_maxOptions; i++)
		{
			bool j = m_index == i;

			std::stringstream optionText;
			const char *option = m_options[(eKeyOptions)i].c_str();
			if (j) optionText << "> ";
			optionText << option;

			switch (i)
			{
				case (int)eKeyOptions::CATEGORY:
				{
					optionText << m_category[m_currentCategory];
				} break;
				default:
					break;
			}

			const int fontSize = (m_activeIndex == i) ? 28 : 24;
			int optionOff = MeasureText(optionText.str().c_str(), fontSize) / 2;
			int x = GetScreenWidth()/2 - optionOff;
			const int listHeight = (fontSize*(int)m_maxOptions);
			int y = GetScreenHeight()/2 + (i*32) - listHeight/2;
			if (j)
			{
				// Wobble when highlighted.
				x += sinf(GetTime() * 8) * 4;
				y += -cosf(GetTime() * 8) * 4;
			}
			DrawText(optionText.str().c_str(), (int)m_menuOffset + x, y, fontSize, WHITE);
		}
	}
	EndDrawing();
}

bool KeymapMenuState::MenuTransition(const eGameState &state, float deltaTime)
{
	if (MenuState::MenuTransition(state, deltaTime))
	{
		switch (state)
		{
			case eGameState::OPTIONS:
			{
				auto *state = (OptionsMenuState*)(Game::Get().GetState((int)eGameState::OPTIONS));
				state->PassParticles(m_particles);
				state->PassMusic(m_titleMusic);
				Game::Get().ChangeState(eGameState::OPTIONS);
			} break;
			default:
				break;
		}
	}
	return true;
}
