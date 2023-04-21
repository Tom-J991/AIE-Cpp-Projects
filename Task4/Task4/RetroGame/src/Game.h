#pragma once

#include <memory>

#include "GameStateManager.h"
#include "MainMenu.h"

class Game
{
public:
	Game();
	~Game();

	void Update(float deltaTime);
	void Draw();

	inline static Game &Get() { m_instance = new Game(); return *m_instance; };

private:
	GameStateManager m_gameStateManager;

private:
	static Game *m_instance;

};
