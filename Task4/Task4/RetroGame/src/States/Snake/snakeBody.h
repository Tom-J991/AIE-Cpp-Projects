#pragma once

#include <vector>

#include <raylib.h>
#include <raymath.h>

namespace Snake
{
	class Fruit;

	class Snake
	{
	public:
		Snake(int gridWidth, int gridHeight, int cellSize);
		~Snake();

		void Init();
		void Move(float deltaTime);
		void Draw();

		bool EatFruit(Fruit &fruit);

	private:
		bool MoveTowardsPosition(Vector2 &start, const Vector2 &dest, float deltaTime);
		bool MoveInDirection(Vector2 &start, const Vector2 &dir, float deltaTime);

	private:
		std::vector<Vector2> m_body;
		int m_length = 0;
		float m_speed = 0.10f;
		Vector2 m_dir;

		int m_gridWidth;
		int m_gridHeight;
		int m_cellSize;

	};

}
