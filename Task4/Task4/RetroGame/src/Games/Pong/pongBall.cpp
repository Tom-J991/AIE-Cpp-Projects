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
		m_speed = { 128, 64 };
	}

	void Ball::Move(float deltaTime)
	{
		if (m_pos.y < 0 || m_pos.y > GetScreenHeight()) // Flip y direction if hit ceiling or floor.
			m_vel.y *= -1;

		// Move.
		m_pos.x += m_vel.x * m_speed.x * deltaTime;
		m_pos.y += m_vel.y * m_speed.y * deltaTime;
	}

	void Ball::Draw()
	{
		DrawRectangle(m_pos.x - (m_size.x / 2), m_pos.y - (m_size.y / 2), m_size.x, m_size.y, WHITE);
	}

}
