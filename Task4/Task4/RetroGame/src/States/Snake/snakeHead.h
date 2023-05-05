#pragma once

#include <raylib.h>
#include <raymath.h>

namespace Snake
{
	class SnakeHead
	{
	public:
		SnakeHead();
		~SnakeHead();

		void Init();

		bool Move(float deltaTime);
		void Draw();

	private:
		Vector2 m_pos;
		Vector2 m_size;
		Vector2 m_vel;
		float m_speed;

	};

}
