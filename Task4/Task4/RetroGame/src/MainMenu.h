#pragma once

#include "GameState.h"

class MainMenuState : public GameState
{
public:
	MainMenuState() { }
	virtual ~MainMenuState() { }

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

};
