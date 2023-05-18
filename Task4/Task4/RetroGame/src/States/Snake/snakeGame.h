#pragma once

#include <vector>
#include <memory>

#include "../../GameState.h"

#include <raylib.h>
#include <raymath.h>

namespace Snake
{
	class GameplayState : public GameState
	{
	public:
		GameplayState();
		virtual ~GameplayState();

		virtual void OnEnter() override;
		virtual void OnExit() override;

		virtual bool Update(float deltaTime) override;
		virtual void Draw() override;

	private:
		Vector2 FruitLocation();

	private:
		bool m_gameEnd = false;

		int m_gridWidth = 16;
		int m_gridHeight = 16;
		int m_cellSize;

		std::vector<Vector2> m_snake;
		Vector2 m_dir;
		Vector2 m_desiredLoc;
		float m_snakeSpeed = 0.10f;
		int m_snakeLength = 0;

		Vector2 m_fruitLoc;

	};

}
