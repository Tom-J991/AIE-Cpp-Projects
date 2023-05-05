#pragma once

#include <vector>
#include <memory>

#include "../../GameState.h"

#include "snakeHead.h"
#include "snakeTail.h"

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
		std::unique_ptr<SnakeHead> m_snakeHead;
		std::vector<std::unique_ptr<SnakeTail>> m_snakeTail;

	};

}
