#include "snakeGame.h"

#include "../../Game.h"

#include <raylib.h>
#include <raymath.h>

// Globals.
#include "KeyMaps.h"
#include "Options.h"
using namespace Options;

namespace Snake
{
	GameplayState::GameplayState()
	{ 
		m_loadedSprites.resize((int)eSprites::SPRITES_MAX);
	}
	GameplayState::~GameplayState()
	{ }

	void GameplayState::OnEnter()
	{
		// Load Assets.
		m_loadedSprites[(int)eSprites::FRUIT] = LoadTexture("./assets/gfx/snake/apple.png");

		m_loadedSprites[(int)eSprites::SNAKE_HEAD_U] = LoadTexture("./assets/gfx/snake/body/head_up.png");
		m_loadedSprites[(int)eSprites::SNAKE_HEAD_D] = LoadTexture("./assets/gfx/snake/body/head_down.png");
		m_loadedSprites[(int)eSprites::SNAKE_HEAD_L] = LoadTexture("./assets/gfx/snake/body/head_left.png");
		m_loadedSprites[(int)eSprites::SNAKE_HEAD_R] = LoadTexture("./assets/gfx/snake/body/head_right.png");

		m_loadedSprites[(int)eSprites::SNAKE_BODY_H] = LoadTexture("./assets/gfx/snake/body/body_horizontal.png");
		m_loadedSprites[(int)eSprites::SNAKE_BODY_V] = LoadTexture("./assets/gfx/snake/body/body_vertical.png");
		m_loadedSprites[(int)eSprites::SNAKE_BODY_BL] = LoadTexture("./assets/gfx/snake/body/body_bottomleft.png");
		m_loadedSprites[(int)eSprites::SNAKE_BODY_BR] = LoadTexture("./assets/gfx/snake/body/body_bottomright.png");
		m_loadedSprites[(int)eSprites::SNAKE_BODY_TL] = LoadTexture("./assets/gfx/snake/body/body_topleft.png");
		m_loadedSprites[(int)eSprites::SNAKE_BODY_TR] = LoadTexture("./assets/gfx/snake/body/body_topright.png");

		m_loadedSprites[(int)eSprites::SNAKE_TAIL_U] = LoadTexture("./assets/gfx/snake/body/tail_up.png");
		m_loadedSprites[(int)eSprites::SNAKE_TAIL_D] = LoadTexture("./assets/gfx/snake/body/tail_down.png");
		m_loadedSprites[(int)eSprites::SNAKE_TAIL_L] = LoadTexture("./assets/gfx/snake/body/tail_left.png");
		m_loadedSprites[(int)eSprites::SNAKE_TAIL_R] = LoadTexture("./assets/gfx/snake/body/tail_right.png");

		// Initialize.
		Init();
	}
	void GameplayState::OnExit()
	{
		for (auto &tex : m_loadedSprites)
			if (IsTextureReady(tex))
				UnloadTexture(tex);
		m_loadedSprites.clear();
		m_loadedSprites.resize((int)eSprites::SPRITES_MAX);
	}

	void GameplayState::Init()
	{
		m_gameEnd = false;
		m_score = 0;

		// Initialize Grid.
		float ratio = (float)(GetScreenWidth() / GetScreenHeight());
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
		m_fruit->Init(m_snake->Body());
	}

	bool GameplayState::Update(float deltaTime)
	{
		// Exit
		if (IsKeyReleased(g_SnakeKeys[eSnakeKeys::QUITGAME]))
			Game::Get().ChangeState(eGameState::GAMELIST); // Go back.

		if (m_gameEnd && IsKeyReleased(g_SnakeKeys[eSnakeKeys::NEWGAME]))
		{
			Init(); // Reinit
			m_gameEnd = false;
		}

		// Game logic
		if (m_gameEnd)
			return false; // Don't update the game if it is ended.

		m_snake->Move(deltaTime);
		if (m_snake->EatFruit(*m_fruit.get()))
			m_score++;
		if (m_snake->CheckCollBounds())
			m_gameEnd = true;
		if (m_snake->CheckCollSelf())
			m_gameEnd = true;

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
			m_fruit->Draw(m_loadedSprites[(int)eSprites::FRUIT]);
			m_snake->Draw(m_loadedSprites);
			// Score
			std::stringstream scoreText;
			scoreText << "Score: " << m_score;
			const int scoreOffset = MeasureText(scoreText.str().c_str(), 28)/2;
			DrawText(scoreText.str().c_str(), GetScreenWidth()/4+32-scoreOffset, 32, 28, WHITE);
			scoreText.clear();
			// Game End
			if (m_gameEnd)
			{
				DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), ColorAlpha(BLACK, 0.5f)); // Dark Tint
				const char *endText = "Game Over!";
				const int endOffset = MeasureText(endText, 48)/2;
				DrawText("Game Over!", GetScreenWidth()/2-endOffset, GetScreenHeight()/2, 48, WHITE);
			}
		}
		EndDrawing();
	}

}
