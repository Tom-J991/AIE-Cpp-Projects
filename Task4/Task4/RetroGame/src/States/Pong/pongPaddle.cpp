#include "pongPaddle.h"

#include "pongBall.h"

// Globals.
#include "KeyMaps.h"
namespace Options
{
	extern std::unordered_map<ePongKeys, KeyboardKey> g_PongKeys;
}
using namespace Options;

namespace Pong
{
	Paddle::Paddle(int player)
		: m_player{ player }
		, m_ai{ false }
		, m_pos{ 0, 0 }
		, m_size{ 0, 0 }
		, m_speed{ 0, 0 }
		, m_score{ 0 }
	{ }
	Paddle::~Paddle()
	{ }

	void Paddle::Init()
	{
		if (m_player < 1 || m_player > 2) // Is neither player 1 or 2.
			return;

		m_size = { 12, 96 };
		m_speed.y = 256;

		m_score = 0;

		const int paddleOffset = 64;
		if (m_player == 1)
		{
			m_pos = { (float)paddleOffset, (float)GetScreenHeight() / 2 };
			m_controlMap[eControl::UP] = g_PongKeys[ePongKeys::FIRSTPLAYER_UP];
			m_controlMap[eControl::DOWN] = g_PongKeys[ePongKeys::FIRSTPLAYER_DOWN];
		}
		else if (m_player == 2)
		{
			m_pos = { (float)GetScreenWidth() - paddleOffset, (float)GetScreenHeight() / 2 };
			m_controlMap[eControl::UP] = g_PongKeys[ePongKeys::SECONDPLAYER_UP];
			m_controlMap[eControl::DOWN] = g_PongKeys[ePongKeys::SECONDPLAYER_DOWN];
		}
	}

	void Paddle::Move(Ball &ball, float deltaTime)
	{
		if (m_ai)
		{
			MoveAI(ball, deltaTime);
			return;
		}

		// Get Input.
		int move = IsKeyDown(m_controlMap[eControl::DOWN]) - IsKeyDown(m_controlMap[eControl::UP]);

		// Move.
		m_pos.y += move * m_speed.y * deltaTime;

		// Clamp Paddle to bounds.
		if (m_pos.y - (m_size.y / 2) < 0)
			m_pos.y = (m_size.y / 2);
		if (m_pos.y + (m_size.y / 2) > GetScreenHeight())
			m_pos.y = GetScreenHeight() - (m_size.y / 2);
	}
	void Paddle::MoveAI(Ball &ball, float deltaTime)
	{
		const float left = m_pos.x - (m_size.x / 2);
		const float right = m_pos.x + (m_size.x / 2);
		const float top = m_pos.y - (m_size.y / 2);
		const float bottom = m_pos.y + (m_size.y / 2);
		// AI
		if (ball.Position().x < 0 || ball.Position().x > GetScreenWidth()) // If ball left bounds.
			m_aiState = eAIStates::IDLE;
		if ((ball.Position().x < left && ball.Velocity().x < 0) || (ball.Position().x > right && ball.Velocity().x > 0)) // If ball is moving away.
			m_aiState = eAIStates::IDLE;
		else
		{
			Vector2 prediction = PredictBall(ball, deltaTime);
			if (prediction.y < top && GetRandomValue(0, 3) == 1)
				m_aiState = eAIStates::MOVE_UP;
			else if (prediction.y > bottom && GetRandomValue(0, 3) == 1)
				m_aiState = eAIStates::MOVE_DOWN;
		}

		// Handle States
		switch (m_aiState)
		{
			case eAIStates::MOVE_UP:
			{
				m_pos.y -= m_speed.y * deltaTime;
			} break;
			case eAIStates::MOVE_DOWN:
			{
				m_pos.y += m_speed.y * deltaTime;
			} break;
			default:
				break;
		}
		// Clamp Paddle to bounds.
		if (m_pos.y - (m_size.y / 2) < 0)
			m_pos.y = (m_size.y / 2);
		if (m_pos.y + (m_size.y / 2) > GetScreenHeight())
			m_pos.y = GetScreenHeight() - (m_size.y / 2);
	}

	void Paddle::Draw()
	{
		const Vector2 center = { m_pos.x-(m_size.x/2), m_pos.y-(m_size.y/2) };
		DrawRectangle((int)center.x, (int)center.y, (int)m_size.x, (int)m_size.y, WHITE);
	}

	Vector2 Paddle::PredictBall(Ball &ball, float deltaTime)
	{
		// TODO:
		return { ball.Position().x, ball.Position().y };
	}

}
