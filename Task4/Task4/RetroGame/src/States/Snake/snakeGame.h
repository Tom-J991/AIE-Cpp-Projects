#pragma once

#include <memory>

#include "../../GameState.h"

#include "snakeBody.h"
#include "snakeFruit.h"

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
		bool m_gameEnd = false;

		int m_gridWidth;
		int m_gridHeight;
		int m_cellSize;

		std::unique_ptr<Snake> m_snake;
		std::unique_ptr<Fruit> m_fruit;

	};

}
