#include "snakeHead.h"

namespace Snake
{
	SnakeHead::SnakeHead()
	{ }
	SnakeHead::~SnakeHead()
	{ }

	void SnakeHead::Init()
	{
		m_pos = { 32, 32 };
		m_size = { 16, 16 };
		m_vel = { 0, 0 };
		m_speed = 128;
	}

	bool SnakeHead::Move(float deltaTime)
	{
		// Get Input
		int hMove = IsKeyPressed(KEY_RIGHT) - IsKeyPressed(KEY_LEFT);
		int vMove = IsKeyPressed(KEY_DOWN) - IsKeyPressed(KEY_UP);

		// Move
		if (hMove != 0)
		{
			m_vel.y = 0;
			m_vel.x = hMove * m_speed;
		}
		if (vMove != 0)
		{
			m_vel.x = 0;
			m_vel.y = vMove * m_speed;
		}

		m_pos.x += m_vel.x * deltaTime;
		m_pos.y += m_vel.y * deltaTime;

		return true;
	}
	void SnakeHead::Draw()
	{
		const Vector2 center = { m_pos.x-(m_size.x/2), m_pos.y-(m_size.y/2) };
		DrawRectangle((int)center.x, (int)center.y, (int)m_size.x, (int)m_size.y, BLUE);
	}

}
