#pragma once

#include <vector>
#include <memory>

#include "../../GameState.h"

#include "snakeObject.h"
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

		std::vector<SnakeObject*> m_snake;
		int m_snakeLength = 0;

		Vector2 m_fruitLoc;
		Vector2 m_fruitSize;

	};

}
