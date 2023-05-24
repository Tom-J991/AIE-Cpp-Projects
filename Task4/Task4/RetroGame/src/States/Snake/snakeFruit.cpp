#include "snakeFruit.h"

namespace Snake
{
	Fruit::Fruit(int gridWidth, int gridHeight, int cellSize)
		: m_gridWidth{ gridWidth }
		, m_gridHeight{ gridHeight }
		, m_cellSize{ cellSize }
	{ }
	Fruit::~Fruit()
	{ }

	void Fruit::Init()
	{
		m_pos = Vector2((float)GetRandomValue(0, m_gridWidth-1), (float)GetRandomValue(0, m_gridHeight-1));
	}

	void Fruit::Draw(Texture2D *tex)
	{
		//DrawRectangle((int)m_pos.x * m_cellSize, (int)m_pos.y * m_cellSize, m_cellSize, m_cellSize, RED);
		DrawTexturePro(
			*tex, 
			{ 0, 0, (float)tex->width, (float)tex->height },
			{ m_pos.x * m_cellSize, m_pos.y * m_cellSize, (float)m_cellSize, (float)m_cellSize },
			{ 0, 0 }, 0, WHITE);
	}

}
