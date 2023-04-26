#include "PongGame.h"

#include <string>

#include "../../Game.h"

PongGameState::PongGameState()
{ }
PongGameState::~PongGameState()
{ }

void PongGameState::OnEnter()
{
	// Initialize Parameters
	int paddleOffset = 64;
	paddleScale = { 16, 64 };
	firstPos = { (float)paddleOffset, (float)GetScreenHeight() / 2 };
	secondPos = { (float)GetScreenWidth() - paddleOffset, (float)GetScreenHeight() / 2 };

	ballScale = { 10, 10 };
	ballPos = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
	ballDir = { -1, -1 };

	centreLineSize = { 8, 12 };

	moveSpeed = 256;
	ballSpeed = { 128, 64 };

	firstScore = 0;
	secondScore = 0;
}

bool PongGameState::CheckCollision(Vector2 paddlePos)
{
	// AABB
	Vector2 adjustPPos = { paddlePos.x-(paddleScale.x/2), paddlePos.y-(paddleScale.y/2) };
	Vector2 adjustBPos = { ballPos.x-(ballScale.x/2), ballPos.y-(ballScale.y/2) };

	bool collX = adjustPPos.x + paddleScale.x >= adjustBPos.x &&
		adjustBPos.x + ballScale.x >= adjustPPos.x;
	bool collY = adjustPPos.y + paddleScale.y >= adjustBPos.y &&
		adjustBPos.y + ballScale.y >= adjustPPos.y;
	return collX && collY;
}

void PongGameState::Update(float deltaTime)
{
	// Get Input
	int firstMove = IsKeyDown(KEY_S) - IsKeyDown(KEY_W);
	int secondMove = IsKeyDown(KEY_DOWN) - IsKeyDown(KEY_UP);

	// Paddle Move
	firstPos.y += firstMove * moveSpeed * deltaTime;
	secondPos.y += secondMove * moveSpeed * deltaTime;

	// Clamp Paddle to bounds.
	if (firstPos.y - (paddleScale.y/2) < 0)
		firstPos.y = (paddleScale.y/2);
	if (firstPos.y + (paddleScale.y/2) > GetScreenHeight())
		firstPos.y = GetScreenHeight() - (paddleScale.y/2);

	if (secondPos.y - (paddleScale.y/2) < 0)
		secondPos.y = (paddleScale.y/2);
	if (secondPos.y + (paddleScale.y/2) > GetScreenHeight())
		secondPos.y = GetScreenHeight() - (paddleScale.y/2);

	// Bounce
	if (CheckCollision(firstPos) || CheckCollision(secondPos))
	{
		while (CheckCollision(firstPos) || CheckCollision(secondPos))
		{ // Push out of paddle if still inside.
			ballPos.x -= ballDir.x;
			ballPos.y -= ballDir.y;
		}
		// Flip directions
		ballDir.x *= -1;
		ballDir.y *= -1;

		ballSpeed.x *= 1.1f;
		ballSpeed.y *= 1.2f;
	}
	if (ballPos.y < 0 || ballPos.y > GetScreenHeight()) // Flip y direction if hit ceiling or floor.
		ballDir.y *= -1;

	// Score
	if (ballPos.x > GetScreenWidth())
		firstScore++;
	else if (ballPos.x < 0)
		secondScore++;

	if (ballPos.x > GetScreenWidth() || ballPos.x < 0)
	{
		// Reset ball if out of bounds.
		ballPos = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
		ballDir.x *= -1;
		ballDir.y *= -1;
		ballSpeed = { 128, 64 };
	}

	// Ball Move.
	ballPos.x += ballDir.x * ballSpeed.x * deltaTime;
	ballPos.y += ballDir.y * ballSpeed.y * deltaTime;

	// Exit.
	if (IsKeyReleased(KEY_ESCAPE))
		Game::Get().ChangeState(eGameState::MENU); // Go to menu.
}
void PongGameState::Draw()
{
	BeginDrawing();
	ClearBackground(BLACK);
	{
		// Centre line
		for (int i = 0; i < GetScreenHeight(); i += centreLineSize.y*2)
		{
			DrawRectangle(GetScreenWidth()/2 - (centreLineSize.x/2), i - (centreLineSize.x/2), centreLineSize.x, centreLineSize.y, WHITE);
		}

		// Paddles
		DrawRectangle(firstPos.x - (paddleScale.x/2), firstPos.y - (paddleScale.y/2), paddleScale.x, paddleScale.y, WHITE);
		DrawRectangle(secondPos.x - (paddleScale.x/2), secondPos.y - (paddleScale.y/2), paddleScale.x, paddleScale.y, WHITE);

		// Ball
		DrawRectangle(ballPos.x - (ballScale.x/2), ballPos.y - (ballScale.y/2), ballScale.x, ballScale.y, WHITE);

		// Scores
		DrawText(std::to_string((int)firstScore).c_str(), GetScreenWidth()/4, GetScreenHeight()/5, 48, WHITE);
		DrawText(std::to_string((int)secondScore).c_str(), GetScreenWidth()/1.5, GetScreenHeight()/5, 48, WHITE);

	}
	EndDrawing();
}
