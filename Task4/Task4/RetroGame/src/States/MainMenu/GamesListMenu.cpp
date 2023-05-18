#include "GamesListMenu.h"

#include "MainMenu.h"

// Globals.
#include "KeyMaps.h"
namespace Options
{
	extern std::unordered_map<eGeneralKeys, KeyboardKey> g_GeneralKeys;
}
using namespace Options;

GamesListMenuState::GamesListMenuState()
{ 
	MenuState::MenuState();

	m_games.insert(std::pair<eGames, std::string>(eGames::PONG, "PONG"));
	m_games.insert(std::pair<eGames, std::string>(eGames::SNAKE, "SNAKE"));
	m_games.insert(std::pair<eGames, std::string>(eGames::BACK, "Go Back"));
}
GamesListMenuState::~GamesListMenuState()
{ 
	MenuState::~MenuState();
}

void GamesListMenuState::OnEnter()
{
	MenuState::OnEnter();
}
void GamesListMenuState::OnExit()
{
	MenuState::OnExit();
}

bool GamesListMenuState::Update(float deltaTime)
{
	if (!MenuState::Update(deltaTime))
		return false;

	// Options
	if (IsKeyReleased(g_GeneralKeys[eGeneralKeys::MENU_ACCEPT]))
	{
		switch (m_index)
		{
			case (int)eGames::PONG:
			{
				m_isFading = true;
				m_transitionDest = eGameState::PONG_MENU;
			} break;
			case (int)eGames::SNAKE:
			{
				m_isFading = true;
				m_transitionDest = eGameState::SNAKE_GAME;
			} break;
			case (int)eGames::BACK:
			{
				m_isTransition = true;
				m_transitionDest = eGameState::MENU;
			} break;
			default:
				break;
		}
	}

	if (IsKeyReleased(g_GeneralKeys[eGeneralKeys::MENU_BACK]))
	{
		m_isTransition = true;
		m_transitionDest = eGameState::MENU;
	}

	int dir = IsKeyPressed(g_GeneralKeys[eGeneralKeys::MENU_DOWN]) - IsKeyPressed(g_GeneralKeys[eGeneralKeys::MENU_UP]); // Up or Down.
	m_index += dir;

	if (m_index < 0) // Clamp Direction
		m_index = (int)eGames::GAMES_MAX - 1;
	if (m_index >= (int)eGames::GAMES_MAX)
		m_index = 0;

	return true;
}
void GamesListMenuState::Draw()
{
	BeginDrawing();
	ClearBackground(BLACK);
	{
		MenuState::DrawParticles();
		// Title
		const char *title = "Games: ";
		int titleOff = MeasureText(title, 48) / 2;
		DrawText(title, (int)m_menuOffset + GetScreenWidth() / 2 - titleOff, GetScreenHeight() / 4, 48, WHITE);
		// Options
		for (int i = 0; i < (int)eGames::GAMES_MAX; i++)
		{
			bool j = m_index == i;

			std::stringstream optionText;
			const char *option = m_games[(eGames)i].c_str();
			if (j) optionText << "> ";
			optionText << option;

			const int fontSize = 24;
			int optionOff = MeasureText(optionText.str().c_str(), fontSize) / 2;
			int x = GetScreenWidth()/2 - optionOff;
			int y = GetScreenHeight()/2 + (i*32);
			if (j)
			{
				x += (int)(sinf((float)GetTime() * 8) * 4);
				y += (int)(-cosf((float)GetTime() * 8) * 4);
			}
			DrawText(optionText.str().c_str(), (int)m_menuOffset + x, y, fontSize, WHITE);
		}
		MenuState::DrawFade();
	}
	EndDrawing();
}

bool GamesListMenuState::MenuTransition(const eGameState &state, float deltaTime)
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
bool GamesListMenuState::FadeTransition(const eGameState &state, float deltaTime)
{
	if (MenuState::FadeTransition(state, deltaTime))
	{
		if (IsMusicStreamPlaying(m_titleMusic))
			StopMusicStream(m_titleMusic);
		switch (state)
		{
			case eGameState::PONG_MENU:
			{
				Game::Get().ChangeState(eGameState::PONG_MENU);
			} break;
			case eGameState::SNAKE_GAME:
			{
				Game::Get().ChangeState(eGameState::SNAKE_GAME);
			} break;
			default:
				break;
		}
	}
	return true;
}
