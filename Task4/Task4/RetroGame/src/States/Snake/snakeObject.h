#pragma once

#include <raylib.h>
#include <raymath.h>

namespace Snake
{
	class SnakeObject
	{
	public:
		virtual void Init() = 0;

		virtual bool Move(float deltaTime) = 0;
		virtual void Draw() = 0;

		virtual Vector2 Position() const { return m_pos; }
		virtual Vector2 Size() const { return m_size; }
		virtual Vector2 Velocity() const { return m_vel; }

	protected:
		Vector2 m_pos;
		Vector2 m_size;
		Vector2 m_vel;
		float m_speed;

	};

}
