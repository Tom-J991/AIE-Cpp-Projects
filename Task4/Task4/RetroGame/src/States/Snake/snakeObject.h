#pragma once

#include <raylib.h>
#include <raymath.h>

namespace Snake
{
	class SnakeObject
	{
	public:
		SnakeObject();
		virtual ~SnakeObject();

		virtual void Init();

		virtual bool Move(float deltaTime);
		virtual void Draw();

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
