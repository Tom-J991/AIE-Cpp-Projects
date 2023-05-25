#include "snakeBody.h"

#include "snakeFruit.h"
#include "snakeGame.h"

// Globals.
#include "KeyMaps.h"
#include "Options.h"
using namespace Options;

float g_moveTime;

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
		m_pos = { 4, 8 };
		m_dir = { 0, 0 };
		m_length = 3;

		m_justStarted = true;

		// Init snake body.
		m_body.clear();
		m_body.push_back({ { m_pos.x-2, m_pos.y }, m_dir });
		m_body.push_back({ { m_pos.x-1, m_pos.y }, m_dir });
		m_body.push_back({ m_pos, m_dir });

		g_moveTime = (float)GetTime(); // Initialize movement timer.
	}

	void Snake::Move(float deltaTime)
	{
		// Get Input
		int hMove = IsKeyPressed(g_SnakeKeys[eSnakeKeys::MOVE_RIGHT]) - IsKeyPressed(g_SnakeKeys[eSnakeKeys::MOVE_LEFT]);
		int vMove = IsKeyPressed(g_SnakeKeys[eSnakeKeys::MOVE_DOWN]) - IsKeyPressed(g_SnakeKeys[eSnakeKeys::MOVE_UP]);

		// Move Snake
		if (hMove != 0) // Set horizontal direction.
		{
			if (m_dir.x == 0)
				m_dir.x = (float)hMove;
			else if (m_dir.x == hMove)
				m_dir.x = (float)hMove;
			m_dir.y = 0; // Reset

			m_justStarted = false;
		}
		if (vMove != 0) // Set vertical direction.
		{
			m_dir.x = 0; // Reset
			if (m_dir.y == 0)
				m_dir.y = (float)vMove;
			else if (m_dir.y == vMove)
				m_dir.y = (float)vMove;

			m_justStarted = false;
		}
		
		float elapsedTime = (float)GetTime() - g_moveTime;
		float tick = deltaTime / m_speed;
		if (elapsedTime > tick) // Move Timer
		{
			elapsedTime -= tick;
			g_moveTime += tick;

			m_pos.x += m_dir.x;
			m_pos.y += m_dir.y;

			// Adds new position to head, removes end tail. Snake movement
			if (!m_justStarted)
			{
				m_body.push_back({ m_pos, m_dir });
				if (m_body.size() > m_length)
					m_body.erase(m_body.begin());
			}
		}
	}
	void Snake::Draw(std::vector<Texture2D> &textures)
	{
		if (!m_body.empty())
		{
			for (int i = 0; i < m_body.size(); i++)
			{
				// TODO: Fix head sprite not connecting properly to body when changing directions.
				auto &snake = m_body[i];
				Texture2D *tex = nullptr;
				if (snake.pos.x == m_pos.x && snake.pos.y == m_pos.y) // Is head
				{
					// Check direction.
					if (m_dir.x == 1)
						tex = &textures[(int)eSprites::SNAKE_HEAD_R];
					else if (m_dir.x == -1)
						tex = &textures[(int)eSprites::SNAKE_HEAD_L];
					else if (m_dir.y == 1)
						tex = &textures[(int)eSprites::SNAKE_HEAD_D];
					else if (m_dir.y == -1)
						tex = &textures[(int)eSprites::SNAKE_HEAD_U];
					else // Default
						tex = &textures[(int)eSprites::SNAKE_HEAD_R];
				}
				else if (snake.pos.x == m_body.front().pos.x && snake.pos.y == m_body.front().pos.y) // Is tail
				{
					auto &nextPart = m_body[i+1];
					// Check direction.
					if (nextPart.dir.x == 1)
						tex = &textures[(int)eSprites::SNAKE_TAIL_L];
					else if (nextPart.dir.x == -1)
						tex = &textures[(int)eSprites::SNAKE_TAIL_R];
					else if (nextPart.dir.y == 1)
						tex = &textures[(int)eSprites::SNAKE_TAIL_U];
					else if (nextPart.dir.y == -1)
						tex = &textures[(int)eSprites::SNAKE_TAIL_D];
					else // Default
						tex = &textures[(int)eSprites::SNAKE_TAIL_L];
				}
				else // Is body
				{
					auto &prevPart = m_body[i-1];
					auto &nextPart = m_body[i+1];

					// TODO: Better way of doing all of this? Really messy.
					// Check if body part is in line and which direction
					if ((prevPart.pos.x == snake.pos.x-1 && prevPart.pos.y == snake.pos.y) || // Check Left
						(prevPart.pos.x == snake.pos.x+1 && prevPart.pos.y == snake.pos.y)) // Check Right
						tex = &textures[(int)eSprites::SNAKE_BODY_H];
					else if ((prevPart.pos.x == snake.pos.x && prevPart.pos.y == snake.pos.y-1) || // Check Up
							(prevPart.pos.x == snake.pos.x && prevPart.pos.y == snake.pos.y+1)) // Check Down
						tex = &textures[(int)eSprites::SNAKE_BODY_V];

					// Check corners
					if ((prevPart.pos.x == snake.pos.x-1 && prevPart.pos.y == snake.pos.y && // Check Previous to left
						nextPart.pos.x == snake.pos.x && nextPart.pos.y == snake.pos.y-1) || // Check next is above
						(prevPart.pos.x == snake.pos.x && prevPart.pos.y == snake.pos.y-1 && // Check Previous is above
						nextPart.pos.x == snake.pos.x-1 && nextPart.pos.y == snake.pos.y)) // Check next to left
						tex = &textures[(int)eSprites::SNAKE_BODY_TL];
					else if ((prevPart.pos.x == snake.pos.x+1 && prevPart.pos.y == snake.pos.y && // Check Previous to right
							nextPart.pos.x == snake.pos.x && nextPart.pos.y == snake.pos.y-1) || // Check next is above
							(prevPart.pos.x == snake.pos.x && prevPart.pos.y == snake.pos.y-1 && // Check Previous is above
							nextPart.pos.x == snake.pos.x+1 && nextPart.pos.y == snake.pos.y)) // Check next to right
						tex = &textures[(int)eSprites::SNAKE_BODY_TR];
					else if ((prevPart.pos.x == snake.pos.x-1 && prevPart.pos.y == snake.pos.y && // Check Previous to left
							nextPart.pos.x == snake.pos.x && nextPart.pos.y == snake.pos.y+1) || // Check next is below
							(prevPart.pos.x == snake.pos.x && prevPart.pos.y == snake.pos.y+1 && // Check Previous is below
							nextPart.pos.x == snake.pos.x-1 && nextPart.pos.y == snake.pos.y)) // Check next to left
						tex = &textures[(int)eSprites::SNAKE_BODY_BL];
					else if ((prevPart.pos.x == snake.pos.x+1 && prevPart.pos.y == snake.pos.y && // Check Previous to right
							nextPart.pos.x == snake.pos.x && nextPart.pos.y == snake.pos.y+1) || // Check next is below
							(prevPart.pos.x == snake.pos.x && prevPart.pos.y == snake.pos.y+1 && // Check Previous is below
							nextPart.pos.x == snake.pos.x+1 && nextPart.pos.y == snake.pos.y)) // Check next to right
						tex = &textures[(int)eSprites::SNAKE_BODY_BR];
				}
				if (tex == nullptr)
					return;

				DrawTexturePro(
					*tex,
					{ 0, 0, (float)tex->width, (float)tex->height },
					{ snake.pos.x * m_cellSize, snake.pos.y * m_cellSize, (float)m_cellSize, (float)m_cellSize },
					{ 0, 0 }, 0, WHITE);
			}
		}
	}

	bool Snake::EatFruit(Fruit &fruit)
	{
		if (m_body.empty())
			return false;

		const Vector2 adjPos = { m_body.back().pos.x*m_cellSize, m_body.back().pos.y*m_cellSize };
		const Vector2 adjFPos = { fruit.Position().x*m_cellSize, fruit.Position().y*m_cellSize };
		if (adjPos.x == adjFPos.x && adjPos.y == adjFPos.y)
		{
			m_length++;
			fruit.Init(m_body);
			return true;
		}

		return false;
	}

	bool Snake::CheckCollBounds()
	{
		if (m_pos.x < 0 || m_pos.x > m_gridWidth-1 ||
			m_pos.y < 0 || m_pos.y > m_gridHeight-1) // If hit edge of screen.
		{
			return true;
		}
		return false;
	}
	bool Snake::CheckCollSelf()
	{
		if (m_body.empty())
			return false;

		for (int i = 0; i < m_body.size()-1; i++)
		{
			if (m_body[i].pos.x == m_pos.x && m_body[i].pos.y == m_pos.y) // If tail hits head.
				return true;
		}

		return false;
	}

}
