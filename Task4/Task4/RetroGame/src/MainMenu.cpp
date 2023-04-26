#include "MainMenu.h"

#include "Game.h"

MainMenuState::MainMenuState()
{ 
	m_options.insert(std::pair<eOptions, std::string>(eOptions::PONG, "Pong"));
	m_options.insert(std::pair<eOptions, std::string>(eOptions::QUIT, "Quit"));

	m_index = 0;
}
MainMenuState::~MainMenuState()
{ }

void MainMenuState::OnEnter()
{
}

void MainMenuState::Update(float deltaTime)
{
	int dir = (IsKeyPressed(KEY_DOWN)||IsKeyPressed(KEY_S)) - (IsKeyPressed(KEY_UP)||IsKeyPressed(KEY_W));
	m_index += dir;

	if (m_index < 0) // Clamp Direction
		m_index = (int)eOptions::OPTIONS_MAX-1;
	if (m_index >= (int)eOptions::OPTIONS_MAX)
		m_index = 0;

	if (IsKeyReleased(KEY_ENTER))
	{
		switch (m_index)
		{
			case (int)eOptions::PONG:
			{
				Game::Get().ChangeState(eGameState::PONG);
			} break;
			case (int)eOptions::QUIT:
			{
				Game::Get().Quit();
			} break;
			default:
				break;
		}
	}
	if (IsKeyReleased(KEY_ESCAPE))
	{
		Game::Get().Quit();
	}
}
void MainMenuState::Draw()
{
	BeginDrawing();
	ClearBackground(WHITE);
	{
		// Title
		const char *title = "Retro Games Gallery";
		int titleOff = MeasureText(title, 48) / 2;
		DrawText(title, GetScreenWidth()/2 - titleOff, GetScreenHeight()/4, 48, BLACK);
		// Options
		for (int i = 0; i < (int)eOptions::OPTIONS_MAX; i++)
		{
			bool j = m_index == i;

			std::stringstream optionText;
			const char *option = m_options[(eOptions)i].c_str();
			if (j) optionText << "> ";
			optionText << option;

			int optionOff = MeasureText(optionText.str().c_str(), 24) / 2;
			DrawText(optionText.str().c_str(), GetScreenWidth()/2 - optionOff, GetScreenHeight()/2 + (i*32), 24, BLACK);
		}
	}
	EndDrawing();
}
