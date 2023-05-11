#pragma once

#include <raylib.h>
#include <raymath.h>

namespace Snake
{
	class SnakeObject
	{
	public:
		SnakeObject();
		SnakeObject(Vector2 pos, Vector2 vel);
		~SnakeObject();

		bool Move(float deltaTime);
		void Draw();

		bool EatFruit(const Vector2 &fruitPos, const Vector2& fruitSize);
		bool CollideSelf(const SnakeObject &self);
		bool CollideWall();

		float Speed() const { return m_speed; }

		Vector2 Position() const { return m_pos; }
		Vector2 Size() const { return m_size; }
		Vector2 Velocity() const { return m_vel; }

		void SetPosition(Vector2 pos) { m_pos = pos; }
		void SetSize(Vector2 size) { m_size = size; }
		void SetVelocity(Vector2 vel) { m_vel = vel; }

	private:
		const float m_speed = 256;

		Vector2 m_pos;
		Vector2 m_size;
		Vector2 m_vel;

	};

}
