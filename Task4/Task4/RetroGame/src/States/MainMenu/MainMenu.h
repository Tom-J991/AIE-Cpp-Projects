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

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

protected:
	virtual void MenuTransition(const eGameState &state, float deltaTime) override;

private:
	std::map<eMenu, std::string> m_menu;

};
