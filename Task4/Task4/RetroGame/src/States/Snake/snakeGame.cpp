#include "snakeGame.h"

#include "../../Game.h"

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
	{ }
	GameplayState::~GameplayState()
	{ }

	void GameplayState::OnEnter()
	{
		m_gameEnd = false;

		// Init Grid.
		const int adjCellWidth = GetScreenWidth() / m_gridWidth;
		const int adjCellHeight = GetScreenHeight() / m_gridHeight;
		//m_cellSize = (adjCellWidth + adjCellHeight) / 2; // Average
		m_cellSize = adjCellHeight;

		// Initialize Game Objects.
		m_snakeLength = 0;
		m_snake.push_back({ (float)GetRandomValue(0, m_gridWidth-1), (float)GetRandomValue(0, m_gridHeight-1) });
		m_desiredLoc = m_snake.front();
		m_dir = { 0, 0 };

		m_fruitLoc = FruitLocation();
	}
	void GameplayState::OnExit()
	{
		m_snake.clear();
	}

	Vector2 tmpSnake;
	float moveTime = 0;
	bool GameplayState::Update(float deltaTime)
	{
		// Get Input
		int hMove = IsKeyPressed(g_SnakeKeys[eSnakeKeys::MOVE_RIGHT]) - IsKeyPressed(g_SnakeKeys[eSnakeKeys::MOVE_LEFT]);
		int vMove = IsKeyPressed(g_SnakeKeys[eSnakeKeys::MOVE_DOWN]) - IsKeyPressed(g_SnakeKeys[eSnakeKeys::MOVE_UP]);

		// Snake Logic
		if (hMove != 0) // Set horizontal direction.
		{
			m_dir.x = (float)hMove;
			m_dir.y = 0; // Reset
		}
		if (vMove != 0) // Set vertical direction.
		{
			m_dir.x = 0; // Reset
			m_dir.y = (float)vMove;
		}

		if (m_snake.front().x != m_desiredLoc.x || m_snake.front().y != m_desiredLoc.y) // Grid-based movement.
		{
			// Interpolate to desired location.
			if (moveTime < m_snakeSpeed)
			{
				float t = moveTime / m_snakeSpeed;
				m_snake.front().x = Lerp(tmpSnake.x, m_desiredLoc.x, t);
				m_snake.front().y = Lerp(tmpSnake.y, m_desiredLoc.y, t);
				moveTime += deltaTime;
			}
			else
			{
				m_snake.front().x = m_desiredLoc.x;
				m_snake.front().y = m_desiredLoc.y;
			}
		}
		else
		{
			// Set new desired location.
			if (m_dir.x != 0 || m_dir.y != 0)
			{
				tmpSnake = m_snake.front();
				moveTime = 0;
				m_desiredLoc = { tmpSnake.x + m_dir.x, tmpSnake.y + m_dir.y };
				if ((m_desiredLoc.x > m_gridWidth-1 || m_desiredLoc.y > m_gridHeight-1) ||
					(m_desiredLoc.x < 0 || m_desiredLoc.y < 0))
					m_desiredLoc = tmpSnake;
			}
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
			// Snake
			for (auto snake : m_snake)
				DrawRectangle((int)(snake.x * m_cellSize), (int)(snake.y * m_cellSize), m_cellSize, m_cellSize, BLUE);
			// Fruit
			DrawRectangle((int)m_fruitLoc.x * m_cellSize, (int)m_fruitLoc.y * m_cellSize, m_cellSize, m_cellSize, RED);
		}
		EndDrawing();
	}

	Vector2 GameplayState::FruitLocation()
	{
		return Vector2((float)GetRandomValue(0, m_gridWidth-1), (float)GetRandomValue(0, m_gridHeight-1));
	}

}
