#pragma once

#include <memory>

#include "../../GameState.h"

#include "pongBall.h"
#include "pongPaddle.h"

#include <raylib.h>

namespace Pong
{
	class GameplayState : public GameState
	{
	public:
		GameplayState();
		virtual ~GameplayState();

		virtual void OnEnter() override;

		virtual void Update(float deltaTime) override;
		virtual void Draw() override;

	private:
		std::unique_ptr<Ball> m_ball;
		std::shared_ptr<Paddle> m_firstPlayer;
		std::shared_ptr<Paddle> m_secondPlayer;

	};

}
