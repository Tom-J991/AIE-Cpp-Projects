#include "pongBall.h"

#include <iostream>
namespace Pong
{
	Ball::Ball()
		: m_pos{ 0, 0 }
		, m_vel{ 0, 0 }
		, m_size{ 0, 0 }
		, m_speed{ 0, 0 }
	{ }
	Ball::~Ball()
	{ }

	void Ball::Init()
	{
		m_pos = { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 };
		m_vel = { -1, -1 };
		m_size = { 10, 10 };
		m_speed = { 64, 256 };
	}

	void Ball::Move(float deltaTime)
	{
		// Move.
		m_pos.x += m_vel.x * m_speed.x * deltaTime;
		m_pos.y += m_vel.y * m_speed.y * deltaTime;
	}

	void Ball::Draw()
	{
		DrawRectangle((int)(m_pos.x - (m_size.x / 2)), (int)(m_pos.y - (m_size.y / 2)), (int)m_size.x, (int)m_size.y, WHITE);
	}

	bool Ball::CheckBounds()
	{
		if (m_pos.y < 0 || m_pos.y > GetScreenHeight()) // Flip y direction if hit ceiling or floor.
		{
			m_vel.y *= -1;
			return true;
		}

		return false;
	}

	bool Ball::CheckCollision(Paddle &paddle)
	{
		if (paddle.Player() < 1 || paddle.Player() > 2) // Paddle is neither player 1 or 2.
			return false;

		if (paddle.Player() == 1) // Check Left Paddle
		{
			if (m_pos.y - (m_size.y / 2) < paddle.Position().y + (paddle.Size().y / 2) &&
				m_pos.y + (m_size.y / 2) > paddle.Position().y - (paddle.Size().y / 2) &&
				m_pos.x - (m_size.x / 2) < paddle.Position().x + (paddle.Size().x / 2))
			{
				if (m_pos.x > paddle.Position().x)
				{
					m_vel.x *= -1;
					m_vel.y *= -1;

					return true;
				}
			}
		}
		if (paddle.Player() == 2) // Check Left Paddle
		{
			if (m_pos.y - (m_size.y / 2) < paddle.Position().y + (paddle.Size().y / 2) &&
				m_pos.y + (m_size.y / 2) > paddle.Position().y - (paddle.Size().y / 2) &&
				m_pos.x + (m_size.x / 2) > paddle.Position().x - (paddle.Size().x / 2))
			{
				if (m_pos.x < paddle.Position().x)
				{
					m_vel.x *= -1;
					m_vel.y *= -1;

					return true;
				}
			}
		}

		return false;
	}

}
