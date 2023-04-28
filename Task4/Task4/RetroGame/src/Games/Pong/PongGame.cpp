#include "pongGame.h"

#include <string>

#include "../../Game.h"

namespace Pong
{
	GameplayState::GameplayState()
	{ 
		m_ball = std::make_unique<Ball>();
		m_firstPlayer = std::make_shared<Paddle>(1);
		m_secondPlayer = std::make_shared<Paddle>(2);
	}
	GameplayState::~GameplayState()
	{ }

	void GameplayState::OnEnter()
	{
		m_ball->Init();
		m_firstPlayer->Init();
		m_secondPlayer->Init();
	}

	void GameplayState::Update(float deltaTime)
	{
		// Move.
		if (m_firstPlayer->CheckCollision(*m_ball.get()))
		{
			std::cout << "Collide" << std::endl;
			while (m_firstPlayer->CheckCollision(*m_ball.get())) // Push out of paddle if still inside.
				m_ball->SetPosition(m_ball->Position().x - m_ball->Velocity().x, m_ball->Position().y - m_ball->Velocity().y);
			// Flip directions
			m_ball->SetVelocity(m_ball->Velocity().x * -1, m_ball->Velocity().y * -1);
			// Increase Speed
			m_ball->SetSpeed(m_ball->Speed().x * 1.1f, m_ball->Speed().y * 1.2f);
		}
		if (m_secondPlayer->CheckCollision(*m_ball.get()))
		{
			std::cout << "Collide" << std::endl;
			while (m_secondPlayer->CheckCollision(*m_ball.get())) // Push out of paddle if still inside.
				m_ball->SetPosition(m_ball->Position().x - m_ball->Velocity().x, m_ball->Position().y - m_ball->Velocity().y);
			// Flip directions
			m_ball->SetVelocity(m_ball->Velocity().x * -1, m_ball->Velocity().y * -1);
			// Increase Speed
			m_ball->SetSpeed(m_ball->Speed().x * 1.1f, m_ball->Speed().y * 1.2f);
		}

		m_ball->Move(deltaTime);
		m_firstPlayer->Move(deltaTime);
		m_secondPlayer->Move(deltaTime);

		// Score.
		if (m_ball->Position().x > GetScreenWidth())
			m_firstPlayer->SetScore(m_firstPlayer->Score() + 1);
		else if (m_ball->Position().x < 0)
			m_secondPlayer->SetScore(m_secondPlayer->Score() + 1);

		// Reset ball when out of bounds.
		if (m_ball->Position().x > GetScreenWidth() || m_ball->Position().x < 0)
		{
			Vector2 tmp = m_ball->Velocity();
			m_ball->Init();
			m_ball->SetVelocity({ tmp.x * -1, tmp.y * -1 });
		}

		// Exit.
		if (IsKeyReleased(KEY_ESCAPE))
			Game::Get().ChangeState(eGameState::MENU); // Go to menu.
	}
	void GameplayState::Draw()
	{
		BeginDrawing();
		ClearBackground(BLACK);
		{
			// Draw Centre-line.
			const Vector2 centreLineSize = { 8, 12 };
			for (int i = 0; i < GetScreenHeight(); i += centreLineSize.y * 2)
			{
				DrawRectangle(GetScreenWidth() / 2 - (centreLineSize.x / 2), i - (centreLineSize.x / 2), centreLineSize.x, centreLineSize.y, WHITE);
			}

			// Draw Game Objects.
			m_firstPlayer->Draw();
			m_secondPlayer->Draw();
			m_ball->Draw();

			// Scores.
			DrawText(std::to_string((int)m_firstPlayer->Score()).c_str(), GetScreenWidth() / 4, GetScreenHeight() / 5, 48, WHITE);
			DrawText(std::to_string((int)m_secondPlayer->Score()).c_str(), GetScreenWidth() / 1.5, GetScreenHeight() / 5, 48, WHITE);

		}
		EndDrawing();
	}

}
