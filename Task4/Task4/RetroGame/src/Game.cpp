#include "Game.h"

#include <iostream>
#include "raylib.h"

enum class eGameState
{
	MENU,
	STATES_MAX
};

Game* Game::m_instance = nullptr;
Game::Game()
	: m_gameStateManager((int)eGameState::STATES_MAX)
{
	if (m_instance != nullptr) // Don't recreate itself if it already exists.
	{
		std::cout << "Game instance already exists!" << std::endl;
		return;
	}

	m_gameStateManager.RegisterState((int)eGameState::MENU, new MainMenuState());
	m_gameStateManager.PushState((int)eGameState::MENU);
}
Game::~Game()
{ }

void Game::Update(float deltaTime)
{
	m_gameStateManager.Update(deltaTime);
}
void Game::Draw()
{
	m_gameStateManager.Draw();
}
