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
	void SerializeCreditsText();
	void GoBack();

private:
	float m_scroll = (float)GetScreenHeight()/2;
	float m_scrollSpeed = 16;
	std::string m_creditsText;
	std::vector<std::string> m_credits;

};