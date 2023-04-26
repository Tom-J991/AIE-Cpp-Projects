#pragma once

#include "../../GameState.h"

#include <raylib.h>

class PongGameState : public GameState
{
public:
	PongGameState();
	virtual ~PongGameState();

	virtual void OnEnter() override;

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:
	bool CheckCollision(Vector2 paddlePos);

private:
	Vector2 firstPos;
	Vector2 secondPos;
	Vector2 paddleScale;
	float firstScore, secondScore;
	float moveSpeed;

	Vector2 ballPos;
	Vector2 ballDir;
	Vector2 ballScale;
	Vector2 ballSpeed;

	Vector2 centreLineSize;

};
