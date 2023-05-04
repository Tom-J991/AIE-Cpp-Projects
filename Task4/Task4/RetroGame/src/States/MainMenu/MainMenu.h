#pragma once

#include "../Menu.h"

enum class eMenu
{
	GAMELIST = 0,
	OPTIONS,
	CREDITS,
	QUIT,
	MENU_MAX
};

class MainMenuState : public MenuState
{
public:
	MainMenuState();
	virtual ~MainMenuState();

	virtual void OnEnter() override;
	virtual void OnExit() override;

	virtual bool Update(float deltaTime) override;
	virtual void Draw() override;

protected:
	virtual bool MenuTransition(const eGameState &state, float deltaTime) override;

private:
	std::map<eMenu, std::string> m_menu;

};
