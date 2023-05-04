#pragma once

#include <vector>
#include <memory>

#include "../../GameState.h"

#include "pongBall.h"
#include "pongPaddle.h"

#include <raylib.h>
#include <raymath.h>

namespace Pong
{
	enum class eSounds
	{
		BOUNDS = 0,
		BOUNCE,
		SCORE,
		SOUNDS_MAX
	};

	class GameplayState : public GameState
	{
	public:
		GameplayState();
		virtual ~GameplayState();

		virtual void OnEnter() override;
		virtual void OnExit() override;

		virtual bool Update(float deltaTime) override;
		virtual void Draw() override;
		
	private:
		void PlaySFX(eSounds sound);

	private:
		std::unique_ptr<Ball> m_ball;
		std::unique_ptr<Paddle> m_firstPlayer;
		std::unique_ptr<Paddle> m_secondPlayer;

		bool m_aiPlayer;

		std::vector<Sound> m_loadedSounds;

	};

}
