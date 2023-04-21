#include "GameStateManager.h"

void GameStateManager::RegisterState(int id, GameState *state)
{
	m_registeredStates[id] = state;
}
void GameStateManager::PushState(int id)
{
	m_pushedStates.push_back(m_registeredStates[id]);
}
void GameStateManager::PopState()
{
	m_popState = true;
}

void GameStateManager::Update(float deltaTime)
{
	while (m_popState)
	{
		m_popState = false;

		m_stateStack.back()->Exit();
		auto temp = m_stateStack.back();
		m_stateStack.pop_back();
		temp->OnPopped();

		if (m_stateStack.empty() == false)
			m_stateStack.back()->Enter();
	}

	for (auto pushedState : m_pushedStates)
	{
		if (m_stateStack.empty() == false)
			m_stateStack.back()->Exit();

		pushedState->OnPushed();
		m_stateStack.push_back(pushedState);
		m_stateStack.back()->Enter();
	}
	m_pushedStates.clear();

	for (auto state : m_stateStack)
		state->Update(deltaTime);
}
