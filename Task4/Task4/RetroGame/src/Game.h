#pragma once

#include <iostream>
#include <memory>

#include <raylib.h>

#include "GameStateManager.h"

enum class eGameState
{
	MENU = 0,
	GAMELIST,
	OPTIONS,
	CREDITS,
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

	void Quit() { m_quit = true; }
	bool IsQuitting() const { return m_quit; }

	void ChangeState(const eGameState &state);
	void PushState(const eGameState &state);
	void PopState();

	GameState *GetTopState() const { return m_gameStateManager->GetTopState(); }
	int ActiveStateCount() const { return (int)m_gameStateManager->ActiveStateCount(); }
	GameState *GetState(int id) const { return m_gameStateManager->GetState(id); }

	static Game &Get() {
		if (m_instance == nullptr) // Don't recreate itself if it already exists.
			m_instance = new Game(); 
		return *m_instance; 
	};

	static void Destroy()
	{
		if (m_instance != nullptr) // Don't try to delete if it doesn't exist.
			delete m_instance;
		m_instance = nullptr;
	}

private:
	std::unique_ptr<GameStateManager> m_gameStateManager;
	bool m_quit;

private:
	static Game *m_instance;

};
