#pragma once

#include "../Menu.h"

namespace Pong
{
	enum class eModes
	{
		ONEPLAYER = 0,
		TWOPLAYER,
		QUIT,
		PONG_MAX
	};

	class TitleState : public MenuState
	{
	public:
		TitleState();
		virtual ~TitleState();

		virtual void OnEnter() override;
		virtual void OnExit() override;

		virtual bool Update(float deltaTime) override;
		virtual void Draw() override;

	protected:
		virtual bool MenuTransition(const eGameState &state, float deltaTime) override;

	private:
		std::map<eModes, std::string> m_modes;
		bool onePlayer;

	};

}
