#include "snakeTail.h"

namespace Snake
{
	SnakeTail::SnakeTail()
	{ }
	SnakeTail::~SnakeTail()
	{ }

	void SnakeTail::Init()
	{
		m_pos = { 32, 32 };
		m_size = { 16, 16 };
		m_vel = { 0, 0 };
		m_speed = 128;
	}

	bool SnakeTail::Move(float deltaTime)
	{
		return true;
	}
	void SnakeTail::Draw()
	{
		const Vector2 center = { m_pos.x-(m_size.x/2), m_pos.y-(m_size.y/2) };
		DrawRectangle((int)center.x, (int)center.y, (int)m_size.x, (int)m_size.y, BLUE);
	}

}
