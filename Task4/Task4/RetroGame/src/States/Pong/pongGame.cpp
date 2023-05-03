#include "pongGame.h"

#include <string>

#include "../../Game.h"

namespace Pong
{
	GameplayState::GameplayState()
	{ 
		m_ball = std::make_unique<Ball>();
		m_firstPlayer = std::make_unique<Paddle>(1);
		m_secondPlayer = std::make_unique<Paddle>(2);

		m_loadedSounds.resize((int)eSounds::SOUNDS_MAX);
	}
	GameplayState::~GameplayState()
	{ 
	}

	void GameplayState::OnEnter()
	{
		// Load Assets
		m_loadedSounds[(int)eSounds::BOUNCE] = LoadSound("./assets/sfx/Pong/ball_bounce.ogg");
		m_loadedSounds[(int)eSounds::BOUNDS] = LoadSound("./assets/sfx/Pong/ball_bounds.ogg");
		m_loadedSounds[(int)eSounds::SCORE] = LoadSound("./assets/sfx/Pong/score.ogg");

		// Initialize
		m_ball->Init();
		m_firstPlayer->Init();
		m_secondPlayer->Init();
	}
	void GameplayState::OnExit()
	{
		// Unload Assets
		for (int i = 0; i < (int)eSounds::SOUNDS_MAX; i++)
			if (IsSoundReady(m_loadedSounds[i]))
				UnloadSound(m_loadedSounds[i]);
	}

	void GameplayState::Update(float deltaTime)
	{
		// Move.
		if (m_ball->CheckCollision(*m_firstPlayer.get(), deltaTime) || m_ball->CheckCollision(*m_secondPlayer.get(), deltaTime))
			PlaySFX(eSounds::BOUNCE);
		if (m_ball->CheckBounds(deltaTime))
			PlaySFX(eSounds::BOUNDS);

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
			m_ball->Init();

			PlaySFX(eSounds::SCORE);
		}

		// Exit.
		if (IsKeyReleased(KEY_ESCAPE))
			Game::Get().ChangeState(eGameState::GAMELIST); // Go back.
	}
	void GameplayState::Draw()
	{
		BeginDrawing();
		ClearBackground(BLACK);
		{
			// Draw Centre-line.
			const Vector2 centreLineSize = { 8, 12 };
			for (int i = 0; i < GetScreenHeight(); i += (int)centreLineSize.y * 2)
			{
				DrawRectangle(GetScreenWidth() / 2 - ((int)centreLineSize.x / 2), i - ((int)centreLineSize.x / 2), (int)centreLineSize.x, (int)centreLineSize.y, WHITE);
			}

			// Draw Game Objects.
			m_firstPlayer->Draw();
			m_secondPlayer->Draw();
			m_ball->Draw();

			// Scores.
			const int screenHalf = GetScreenWidth() / 2;
			const int leftHalf = screenHalf / 2;
			const int rightHalf = screenHalf + leftHalf;
			DrawText(std::to_string((int)m_firstPlayer->Score()).c_str(), leftHalf, GetScreenHeight() / 5, 48, WHITE);
			DrawText(std::to_string((int)m_secondPlayer->Score()).c_str(), rightHalf, GetScreenHeight() / 5, 48, WHITE);

		}
		EndDrawing();
	}

	void GameplayState::PlaySFX(eSounds sound)
	{
		if (IsSoundReady(m_loadedSounds[(int)sound]))
			PlaySound(m_loadedSounds[(int)sound]);
	}

}
