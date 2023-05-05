#pragma once

#include "../Menu.h"

enum class eGames
{
	PONG = 0,
	SNAKE,
	BACK,
	GAMES_MAX
};

class GamesListMenuState : public MenuState
{
public:
	GamesListMenuState();
	virtual ~GamesListMenuState();

	virtual void OnEnter() override;
	virtual void OnExit() override;

	virtual bool Update(float deltaTime) override;
	virtual void Draw() override;

protected:
	virtual bool MenuTransition(const eGameState &state, float deltaTime) override;
	virtual bool FadeTransition(const eGameState &state, float deltaTime) override;

private:
	std::map<eGames, std::string> m_games;

};
