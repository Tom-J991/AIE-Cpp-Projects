#pragma once

#include <memory>
#include <vector>

#include "../../GameState.h"

#include "snakeBody.h"
#include "snakeFruit.h"

namespace Snake
{
	enum class eSprites
	{
		FRUIT = 0, // Fruit

		SNAKE_HEAD_U, // Up, Down, Left, Right Head
		SNAKE_HEAD_D,
		SNAKE_HEAD_L,
		SNAKE_HEAD_R,

		SNAKE_BODY_H, // Horizontal Body
		SNAKE_BODY_V, // Vertical
		SNAKE_BODY_BL, // Bottom Left Corner
		SNAKE_BODY_BR, // Bottom Right Corner
		SNAKE_BODY_TL, // Top Left Corner
		SNAKE_BODY_TR, // Top Right Corner

		SNAKE_TAIL_U, // Up, Down, Left, Right Tail
		SNAKE_TAIL_D,
		SNAKE_TAIL_L,
		SNAKE_TAIL_R,

		SPRITES_MAX
	};

	class GameplayState : public GameState
	{
	public:
		GameplayState();
		virtual ~GameplayState();

		virtual void OnEnter() override;
		virtual void OnExit() override;

		virtual bool Update(float deltaTime) override;
		virtual void Draw() override;

		void Init();

	private:
		bool m_gameEnd = false;
		int m_score;

		int m_gridWidth;
		int m_gridHeight;
		int m_cellSize;

		std::unique_ptr<Snake> m_snake;
		std::unique_ptr<Fruit> m_fruit;

		std::vector<Texture2D> m_loadedSprites;

	};

}
