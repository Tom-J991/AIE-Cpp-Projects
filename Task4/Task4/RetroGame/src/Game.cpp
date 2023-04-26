#include "Game.h"

#include "MainMenu.h"
#include "Games/Pong/PongGame.h"

Game* Game::m_instance = nullptr;
Game::Game()
	: m_gameStateManager((int)eGameState::STATES_MAX)
{
	m_gameStateManager.RegisterState((int)eGameState::MENU, new MainMenuState());
	m_gameStateManager.RegisterState((int)eGameState::PONG, new PongGameState());

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

void Game::ChangeState(eGameState state)
{
	m_gameStateManager.PopState(); 
	m_gameStateManager.PushState((int)state);
}
