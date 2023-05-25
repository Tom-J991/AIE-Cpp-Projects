#pragma once

#include <vector>

#include <raylib.h>

namespace Snake
{
	struct SnakeBody;

	class Fruit
	{
	public:
		Fruit(int gridWidth, int gridHeight, int cellSize);
		~Fruit();

		void Init(const std::vector<SnakeBody> &snakePositions);
		void Draw(const Texture2D &tex);

		Vector2 &Position() { return m_pos; }

	private:
		Vector2 m_pos;

		int m_gridWidth;
		int m_gridHeight;
		int m_cellSize;

	};

}
