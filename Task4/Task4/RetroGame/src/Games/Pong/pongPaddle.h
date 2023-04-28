#pragma once

#include <unordered_map>
#include <utility>

#include <raylib.h>

#include "pongBall.h"

namespace Pong
{
	enum class eControl
	{
		UP = 0,
		DOWN,
		CONTROL_MAX
	};

	class Paddle
	{
	public:
		Paddle(int player = 1);
		~Paddle();

		void Init();

		void Move(float deltaTime);
		void Draw();

		Vector2 Position() const { return m_pos; }
		void SetPosition(Vector2 pos) { m_pos = pos; }
		void SetPosition(float x, float y) { m_pos = { x, y }; }

		Vector2 Size() const { return m_size; }
		void SetSize(Vector2 size) { m_size = size; }
		void SetSize(float x, float y) { m_size = { x, y }; }

		Vector2 Speed() const { return m_speed; }
		void SetSpeed(Vector2 speed) { m_speed = speed; }
		void SetSpeed(float x, float y) { m_speed = { x, y }; }

		int Score() const { return m_score; }
		void SetScore(int score) { m_score = score; }

		bool CheckCollision(Ball &ball);

	private:
		Vector2 m_pos;
		Vector2 m_size;
		Vector2 m_speed;

		int m_player;
		int m_score;

		std::unordered_map<eControl, KeyboardKey> m_controlMap;

	};

}
