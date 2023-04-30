#pragma once

#include <math.h>

#include <raylib.h>

#include "pongPaddle.h"

namespace Pong
{
	class Ball
	{
	public:
		Ball();
		~Ball();

		void Init();

		void Move(float deltaTime);
		void Draw();

		bool CheckBounds();
		bool CheckCollision(Paddle &paddle);

		Vector2 Position() const { return m_pos; }
		void SetPosition(Vector2 pos) { m_pos = pos; }
		void SetPosition(float x, float y) { m_pos = { x, y }; }

		Vector2 Velocity() const { return m_vel; }
		void SetVelocity(Vector2 vel) { m_vel = vel; }
		void SetVelocity(float x, float y) { m_vel = { x, y }; }

		Vector2 Size() const { return m_size; }
		void SetSize(Vector2 size) { m_size = size; }
		void SetSize(float x, float y) { m_size = { x, y }; }

		Vector2 Speed() const { return m_speed; }
		void SetSpeed(Vector2 speed) { m_speed = speed; }
		void SetSpeed(float x, float y) { m_speed = { x, y }; }

	private:
		Vector2 m_pos;
		Vector2 m_vel;
		Vector2 m_size;
		Vector2 m_speed;

	};

}
