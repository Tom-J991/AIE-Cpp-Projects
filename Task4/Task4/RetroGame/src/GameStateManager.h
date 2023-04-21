#pragma once

#include "GameState.h"

#include <vector>

class GameStateManager
{
public:
	GameStateManager(unsigned int stateCount)
	{
		m_registeredStates.resize(stateCount);
	}
	~GameStateManager()
	{
		for (auto state : m_registeredStates)
			delete state;
	}

	void RegisterState(int id, GameState *state);
	void PushState(int id);
	void PopState();

	void Update(float deltaTime);
	void Draw()
	{
		for (auto state : m_stateStack)
			state->Draw();
	}

	GameState *GetTopState() const { return m_stateStack.back(); }
	int ActiveStateCount() const { return (int)m_stateStack.size(); }
	GameState *GetState(int id) const { return m_registeredStates[id]; }

protected:
	std::vector<GameState*> m_pushedStates;
	std::vector<GameState*> m_registeredStates;
	std::vector<GameState*> m_stateStack;

	bool m_popState = false;

};
