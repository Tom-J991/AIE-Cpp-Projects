#pragma once

#include "snakeObject.h"

namespace Snake
{
	class SnakeHead : public SnakeObject
	{
	public:
		SnakeHead();
		~SnakeHead();

		virtual void Init() override;

		virtual bool Move(float deltaTime) override;
		virtual void Draw() override;

	};

}
