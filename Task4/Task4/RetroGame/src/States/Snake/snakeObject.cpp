#include "snakeObject.h"

namespace Snake
{
	SnakeObject::SnakeObject()
		: m_pos { 0, 0 }
		, m_size { 16, 16 }
		, m_vel { 0, 0 }
	{ }
	SnakeObject::SnakeObject(Vector2 pos, Vector2 vel)
		: m_pos{ pos }
		, m_size{ 16, 16 }
		, m_vel{ vel }
	{ }
	SnakeObject::~SnakeObject()
	{ }

	bool SnakeObject::Move(float deltaTime)
	{
		m_pos.x += m_vel.x * m_speed * deltaTime;
		m_pos.y += m_vel.y * m_speed * deltaTime;

		return true;
	}
	void SnakeObject::Draw()
	{
		const Vector2 center = { m_pos.x-(m_size.x/2), m_pos.y-(m_size.y/2) };
		//DrawRectangle((int)center.x, (int)center.y, (int)m_size.x, (int)m_size.y, BLUE);
		DrawRectangle((int)m_pos.x, (int)m_pos.y, (int)m_size.x, (int)m_size.y, BLUE);
	}

	bool SnakeObject::EatFruit(const Vector2 &fruitPos, const Vector2 &fruitSize)
	{
		bool collX = m_pos.x + m_size.x >= fruitPos.x && fruitPos.x + fruitSize.x >= m_pos.x;
		bool collY = m_pos.y + m_size.y >= fruitPos.y && fruitPos.y + fruitSize.y >= m_pos.y;
		return collX && collY;
	}

	bool SnakeObject::CollideSelf(const SnakeObject &self)
	{
		return false;
	}

	bool SnakeObject::CollideWall()
	{
		return false;
	}

}
