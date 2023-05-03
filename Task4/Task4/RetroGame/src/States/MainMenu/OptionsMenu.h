#pragma once

#include "../Menu.h"

enum class eOptions
{
	MASTER_VOLUME = 0,
	BACK,
	OPTIONS_MAX
};

class OptionsMenuState : public MenuState
{
public:
	OptionsMenuState();
	virtual ~OptionsMenuState();

	virtual void OnEnter() override;
	virtual void OnExit() override;

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

protected:
	virtual void MenuTransition(const eGameState &state, float deltaTime) override;

private:
	std::map<eOptions, std::string> m_options;
	std::map<eOptions, bool> m_optionsBold;

};
