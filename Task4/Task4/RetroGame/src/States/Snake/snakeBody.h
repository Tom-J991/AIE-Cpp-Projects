#pragma once

#include <vector>

#include <raylib.h>
#include <raymath.h>

namespace Snake
{
	class Fruit;
	enum class eSounds;

	struct SnakeBody
	{
		Vector2 pos;
		Vector2 dir;
	};

	class Snake
	{
	public:
		Snake(int gridWidth, int gridHeight, int cellSize);
		~Snake();

		void Init();
		void Move(std::vector<Sound> &sounds, float deltaTime);
		void Draw(std::vector<Texture2D> &textures);

		bool EatFruit(Fruit &fruit);

		bool CheckCollBounds();
		bool CheckCollSelf();

		std::vector<SnakeBody> &Body() { return m_body; }

	private:
		void PlaySFX(std::vector<Sound> &sounds, eSounds sound);

	private:
		std::vector<SnakeBody> m_body;
		Vector2 m_pos;
		Vector2 m_dir;
		int m_length = 0;
		const float m_speed = 0.12f;
		bool m_justStarted = false;

		int m_gridWidth;
		int m_gridHeight;
		int m_cellSize;

	};

}
