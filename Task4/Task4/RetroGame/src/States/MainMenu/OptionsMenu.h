#pragma once

#include "../Menu.h"

enum class eOptions
{
	MASTER_VOLUME = 0,
	RESOLUTION,
	FULLSCREEN,
	KEYMAP,
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

	virtual bool Update(float deltaTime) override;
	virtual void Draw() override;

protected:
	virtual bool MenuTransition(const eGameState &state, float deltaTime) override;

private:
	int m_activeIndex = -1;
	std::map<eOptions, std::string> m_options;

	std::vector<std::pair<std::string, Vector2>> m_resolutions;
	int m_resolutionIndex;

};
