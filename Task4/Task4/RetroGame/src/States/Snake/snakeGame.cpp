#include "snakeGame.h"

#include "../../Game.h"

namespace Snake
{
	GameplayState::GameplayState()
	{
		m_snakeHead = std::make_unique<SnakeHead>();
	}
	GameplayState::~GameplayState()
	{
	}

	void GameplayState::OnEnter()
	{
		m_snakeHead->Init();
	}
	void GameplayState::OnExit()
	{
	}

	bool GameplayState::Update(float deltaTime)
	{
		m_snakeHead->Move(deltaTime);

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
			m_snakeHead->Draw();
		}
		EndDrawing();
	}

}
