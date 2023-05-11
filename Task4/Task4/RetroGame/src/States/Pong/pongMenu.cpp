#include "pongMenu.h"

#include "pongGame.h"
#include "../MainMenu/GamesListMenu.h"

// Globals.
#include "KeyMaps.h"
namespace Options
{
	extern std::unordered_map<eGeneralKeys, KeyboardKey> g_GeneralKeys;
}
using namespace Options;

namespace Pong
{
	TitleState::TitleState()
	{
		MenuState::MenuState();

		m_modes.insert(std::pair<eModes, std::string>(eModes::ONEPLAYER, "ONE PLAYER"));
		m_modes.insert(std::pair<eModes, std::string>(eModes::TWOPLAYER, "TWO PLAYER"));
		m_modes.insert(std::pair<eModes, std::string>(eModes::QUIT, "QUIT"));
	}
	TitleState::~TitleState()
	{
		MenuState::~MenuState();
	}

	void TitleState::OnEnter()
	{
		MenuState::OnEnter();
	}
	void TitleState::OnExit()
	{
		MenuState::OnExit();
	}

	bool TitleState::Update(float deltaTime)
	{
		if (!MenuState::Update(deltaTime))
			return false;

		// Options
		if (IsKeyReleased(g_GeneralKeys[eGeneralKeys::MENU_ACCEPT]))
		{
			switch (m_index)
			{
				case (int)eModes::ONEPLAYER:
				{
					onePlayer = true;
					m_isTransition = true;
					m_transitionDest = eGameState::PONG_GAME;
				} break;
				case (int)eModes::TWOPLAYER:
				{
					onePlayer = false;
					m_isTransition = true;
					m_transitionDest = eGameState::PONG_GAME;
				} break;
				case (int)eModes::QUIT:
				{
					m_isTransition = true;
					m_transitionDest = eGameState::GAMELIST;
				} break;
				default:
					break;
			}
		}

		if (IsKeyReleased(g_GeneralKeys[eGeneralKeys::MENU_BACK]))
		{
			m_isTransition = true;
			m_transitionDest = eGameState::GAMELIST;
		}

		int dir = IsKeyPressed(g_GeneralKeys[eGeneralKeys::MENU_DOWN]) - IsKeyPressed(g_GeneralKeys[eGeneralKeys::MENU_UP]); // Up or Down.
		m_index += dir;

		if (m_index < 0) // Clamp Direction
			m_index = (int)eModes::PONG_MAX - 1;
		if (m_index >= (int)eModes::PONG_MAX)
			m_index = 0;

		return true;
	}
	void TitleState::Draw()
	{
		BeginDrawing();
		ClearBackground(BLACK);
		{
			// Title
			const char *title = "PONG";
			int titleOff = MeasureText(title, 48) / 2;
			DrawText(title, (int)m_menuOffset + GetScreenWidth() / 2 - titleOff, GetScreenHeight() / 4, 48, WHITE);
			// Options
			for (int i = 0; i < (int)eModes::PONG_MAX; i++)
			{
				bool j = m_index == i;

				std::stringstream optionText;
				const char *option = m_modes[(eModes)i].c_str();
				if (j) optionText << "> ";
				optionText << option;

				const int fontSize = 24;
				int optionOff = MeasureText(optionText.str().c_str(), fontSize) / 2;
				DrawText(optionText.str().c_str(), (int)m_menuOffset + GetScreenWidth() / 2 - optionOff, GetScreenHeight() / 2 + (i * 32), fontSize, WHITE);
			}
		}
		EndDrawing();
	}

	bool TitleState::MenuTransition(const eGameState &state, float deltaTime)
	{
		if (MenuState::MenuTransition(state, deltaTime))
		{
			switch (state)
			{
				case eGameState::GAMELIST:
				{
					Game::Get().ChangeState(eGameState::GAMELIST);
				} break;
				case eGameState::PONG_GAME:
				{
					auto *state = (GameplayState*)(Game::Get().GetState((int)eGameState::PONG_GAME));
					state->SetOnePlayer(onePlayer);
					Game::Get().ChangeState(eGameState::PONG_GAME);
				} break;
				default:
					break;
			}
		}
		return true;
	}
}
