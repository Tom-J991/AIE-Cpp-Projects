#include "snakeGame.h"

#include "../../Game.h"

namespace Snake
{
	GameplayState::GameplayState()
	{ }
	GameplayState::~GameplayState()
	{ }

	void GameplayState::OnEnter()
	{
		// Initialize
		m_gameEnd = false;

		m_snakeLength = 0;
		m_snake.push_back(new SnakeObject());

		m_fruitLoc = FruitLocation();
		m_fruitSize = { 16, 16 };
	}
	void GameplayState::OnExit()
	{
		for (auto *snake : m_snake)
		{
			delete snake;
			m_snake.clear();
		}
	}

	bool GameplayState::Update(float deltaTime)
	{
		// Get Input
		int hMove = IsKeyPressed(KEY_RIGHT) - IsKeyPressed(KEY_LEFT);
		int vMove = IsKeyPressed(KEY_DOWN) - IsKeyPressed(KEY_UP);

		// Snake Logic
		for (int i = m_snakeLength; i > 0; i--)
		{
			// Position snake bit behind next snake bit.
			m_snake[i]->SetVelocity(m_snake.front()->Velocity());
			const Vector2 newPos = { m_snake[i-1]->Position().x-(m_snake[i-1]->Velocity().x*m_snake[i-1]->Size().x),
									m_snake[i-1]->Position().y-(m_snake[i-1]->Velocity().y*m_snake[i-1]->Size().y) };
			m_snake[i]->SetPosition(newPos);
		}

		if (hMove != 0)
			m_snake.front()->SetVelocity({ (float)hMove, 0 });
		if (vMove != 0)
			m_snake.front()->SetVelocity({ 0, (float)vMove });
		m_snake.front()->Move(deltaTime);

		if (m_snake.front()->EatFruit(m_fruitLoc, m_fruitSize))
		{
			m_fruitLoc = FruitLocation();
			// Grow Snake
			m_snakeLength++;
			const Vector2 newPos = { m_snake.front()->Position().x-(m_snake.front()->Velocity().x*m_snake.front()->Size().x*m_snakeLength), 
									m_snake.front()->Position().y-(m_snake.front()->Velocity().y*m_snake.front()->Size().y*m_snakeLength) };
			m_snake.push_back(new SnakeObject(newPos, m_snake.front()->Velocity()));
		}

		// Exit.
		if (IsKeyReleased(KEY_ESCAPE))
			Game::Get().ChangeState(eGameState::GAMELIST); // Go back.

		return true;
	}
	void GameplayState::Draw()
	{
		BeginDrawing();
		ClearBackground(BLACK);
		{
			// Draw Fruit
			DrawRectangle((int)m_fruitLoc.x, (int)m_fruitLoc.y, (int)m_fruitSize.x, (int)m_fruitSize.y, RED);
			// Draw Snake Body
			for (auto* snake : m_snake)
				snake->Draw();
		}
		EndDrawing();
	}

	Vector2 GameplayState::FruitLocation()
	{
		return Vector2((float)GetRandomValue(0, GetScreenWidth()), (float)GetRandomValue(0, GetScreenHeight()));
	}

}
