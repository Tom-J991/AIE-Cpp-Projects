#pragma once

#include <raylib.h>

namespace Snake
{
	class Fruit
	{
	public:
		Fruit(int gridWidth, int gridHeight, int cellSize);
		~Fruit();

		void Init();
		void Draw();

		Vector2 &Position() { return m_pos; }

	private:
		Vector2 m_pos;

		int m_gridWidth;
		int m_gridHeight;
		int m_cellSize;

	};

}
