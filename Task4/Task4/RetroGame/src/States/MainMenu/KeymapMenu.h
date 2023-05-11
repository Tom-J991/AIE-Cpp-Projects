#pragma once

#include "../Menu.h"

#include "KeyMaps.h"

enum class eKeyCategory
{
	GENERAL = 0,
	PONG,
	SNAKE,
	KEYMAP_MAX
};

enum class eKeyOptions
{
	CATEGORY = 0,
	BACK,
	OPTIONS_MAX
};

class KeymapMenuState : public MenuState
{
public:
	KeymapMenuState();
	virtual ~KeymapMenuState();

	virtual void OnEnter() override;
	virtual void OnExit() override;

	virtual bool Update(float deltaTime) override;
	virtual void Draw() override;

protected:
	virtual bool MenuTransition(const eGameState &state, float deltaTime) override;

private:
	int m_maxOptions;
	int m_activeIndex = -1;

	std::map<eKeyOptions, std::string> m_options;

	eKeyCategory m_currentCategory;
	std::map<eKeyCategory, std::string> m_category;

	std::map<eGeneralKeys, std::string> m_generalKeys;
	std::map<ePongKeys, std::string> m_pongKeys;
	std::map<eSnakeKeys, std::string> m_snakeKeys;

};
