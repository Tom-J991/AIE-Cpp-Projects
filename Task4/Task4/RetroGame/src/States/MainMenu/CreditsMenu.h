#pragma once

#include "../Menu.h"

class CreditsMenuState : public MenuState
{
public:
	CreditsMenuState();
	virtual ~CreditsMenuState();

	virtual void OnEnter() override;
	virtual void OnExit() override;

	virtual bool Update(float deltaTime) override;
	virtual void Draw() override;

protected:
	virtual bool MenuTransition(const eGameState &state, float deltaTime) override;

private:
	void FormatText();
	void GoBack();

private:
	const int m_fontSize = 20;
	float m_scroll = (float)GetScreenHeight()/2;
	float m_scrollSpeed = 32;
	std::string m_creditsText;
	std::vector<std::string> m_credits;

};
