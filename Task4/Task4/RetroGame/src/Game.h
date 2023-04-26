#pragma once

#include <iostream>
#include <memory>

#include <raylib.h>

#include "GameStateManager.h"

enum class eGameState
{
	MENU = 0,
	PONG,
	STATES_MAX
};

class Game
{
public:
	Game();
	~Game();

	void Update(float deltaTime);
	void Draw();

	void ChangeState(eGameState state);

	void Quit() { m_quit = true; }
	bool IsQuitting() const { return m_quit; }

	int ActiveStateCount() const { return m_gameStateManager.ActiveStateCount(); }

	inline static Game &Get() {
		if (m_instance == nullptr) // Don't recreate itself if it already exists.
			m_instance = new Game(); 
		return *m_instance; 
	};

private:
	GameStateManager m_gameStateManager;
	bool m_quit;

private:
	static Game *m_instance;

};
