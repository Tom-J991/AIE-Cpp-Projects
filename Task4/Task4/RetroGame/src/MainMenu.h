#pragma once

#include "GameState.h"

#include <string>
#include <sstream>
#include <map>

#include <raylib.h>

enum class eOptions
{
	PONG = 0,
	QUIT,
	OPTIONS_MAX
};

class MainMenuState : public GameState
{
public:
	MainMenuState();
	virtual ~MainMenuState();

	virtual void OnEnter() override;

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:
	int m_index = 0;
	std::map<eOptions, std::string> m_options;

};
