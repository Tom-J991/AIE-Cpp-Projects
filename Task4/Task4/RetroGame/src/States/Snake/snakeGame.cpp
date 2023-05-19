#include "snakeGame.h"

#include "../../Game.h"

#include <raylib.h>
#include <raymath.h>

// Globals.
#include "KeyMaps.h"
namespace Options
{
	extern std::unordered_map<eSnakeKeys, KeyboardKey> g_SnakeKeys;
}
using namespace Options;

namespace Snake
{
	GameplayState::GameplayState()
	{ 
	}
	GameplayState::~GameplayState()
	{ }

	void GameplayState::OnEnter()
	{
		m_gameEnd = false;

		// Initialize Grid.
		float ratio = GetScreenWidth() / GetScreenHeight();
		if (ratio > 1)
			ratio = 1 / ratio;
		m_gridWidth = (int)(GetScreenWidth() / (50.f * ratio));
		m_gridHeight = (int)(GetScreenHeight() / (50.f / ratio));

		const int adjCellWidth = GetScreenWidth() / m_gridWidth;
		const int adjCellHeight = GetScreenHeight() / m_gridHeight;
		m_cellSize = (adjCellWidth + adjCellHeight) / 2; // Average

		// Initialize Game objects.
		m_snake = std::make_unique<Snake>(m_gridWidth, m_gridHeight, m_cellSize);
		m_fruit = std::make_unique<Fruit>(m_gridWidth, m_gridHeight, m_cellSize);

		m_snake->Init();
		m_fruit->Init();
	}
	void GameplayState::OnExit()
	{
	}

	bool GameplayState::Update(float deltaTime)
	{
		m_snake->Move(deltaTime);
		if (m_snake->EatFruit(*m_fruit.get()))
		{

		}

		// Exit
		if (IsKeyReleased(g_SnakeKeys[eSnakeKeys::QUITGAME]))
			Game::Get().ChangeState(eGameState::GAMELIST); // Go back.

		return true;
	}
	void GameplayState::Draw()
	{
		BeginDrawing();
		ClearBackground(BLACK);
		{
			// Background
			DrawRectangle(0, 0, m_gridWidth * m_cellSize, m_gridHeight * m_cellSize, DARKGREEN);
			// Objects
			m_snake->Draw();
			m_fruit->Draw();
		}
		EndDrawing();
	}

}
