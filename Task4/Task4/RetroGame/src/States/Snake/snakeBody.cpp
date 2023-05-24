#include "snakeBody.h"

#include "snakeFruit.h"

// Globals.
#include "KeyMaps.h"
#include "Options.h"
using namespace Options;

Vector2 tmpPos;
Vector2 tmpDest;
float moveTime = 0;

namespace Snake
{
	Snake::Snake(int gridWidth, int gridHeight, int cellSize)
		: m_gridWidth{ gridWidth }
		, m_gridHeight{ gridHeight }
		, m_cellSize{ cellSize }
	{ }
	Snake::~Snake()
	{ }

	void Snake::Init()
	{
		m_body.clear();
		m_body.push_back({ 4, 8 });
		m_body.push_back({ m_body.front().x-1, m_body.front().y });
		m_body.push_back({ m_body.front().x-2, m_body.front().y });

		m_length = 3;
		m_dir = { 0, 0 };

		tmpDest = m_body.front(); // Initialize destination for movement
	}

	void Snake::Move(float deltaTime)
	{
		// Get Input
		int hMove = IsKeyPressed(g_SnakeKeys[eSnakeKeys::MOVE_RIGHT]) - IsKeyPressed(g_SnakeKeys[eSnakeKeys::MOVE_LEFT]);
		int vMove = IsKeyPressed(g_SnakeKeys[eSnakeKeys::MOVE_DOWN]) - IsKeyPressed(g_SnakeKeys[eSnakeKeys::MOVE_UP]);

		// Move Snake
		if (hMove != 0) // Set horizontal direction.
		{
			m_dir.x = (float)hMove;
			m_dir.y = 0; // Reset
		}
		if (vMove != 0) // Set vertical direction.
		{
			m_dir.x = 0; // Reset
			m_dir.y = (float)vMove;
		}

		MoveInDirection(m_body.front(), m_dir, deltaTime);
	}
	void Snake::Draw()
	{
		for (auto snake : m_body)
			DrawRectangle((int)(snake.x * m_cellSize), (int)(snake.y * m_cellSize), m_cellSize, m_cellSize, BLUE);
	}

	bool Snake::EatFruit(Fruit &fruit)
	{
		const Vector2 adjPos = { m_body.front().x*m_cellSize, m_body.front().y*m_cellSize };
		const Vector2 adjFPos = { fruit.Position().x*m_cellSize, fruit.Position().y*m_cellSize };
		if (adjPos.x == adjFPos.x && adjPos.y == adjFPos.y)
		{
			m_body.push_back({ m_body.back().x-m_dir.x, m_body.back().y-m_dir.y });
			m_length++;
			fruit.Init();

			return true;
		}
		return false;
	}

	bool Snake::MoveInDirection(Vector2 &start, const Vector2 &dir, float deltaTime)
	{
		bool moved = false;
		if (start.x != tmpDest.x || start.y != tmpDest.y) // Hasn't reached destination.
		{
			if (moveTime < m_speed) 
			{
				// Interpolate to desired location.
				float t = moveTime / m_speed;
				start.x = Lerp(tmpPos.x, tmpDest.x, t);
				start.y = Lerp(tmpPos.y, tmpDest.y, t);
				moveTime += deltaTime;
			}
			else
			{
				// Snap to destination.
				start.x = tmpDest.x;
				start.y = tmpDest.y;

				moved = true;
			}
		}
		else
		{
			// Reset
			moveTime = 0;
			tmpPos = start;
			tmpDest = { tmpPos.x+dir.x, tmpPos.y+dir.y };
			// Clamp to border
			if (tmpDest.x < 0 || tmpDest.x > m_gridWidth-1 ||
				tmpDest.y < 0 || tmpDest.y > m_gridHeight-1)
				tmpDest = tmpPos;
		}
		return moved;
	}

}
