#include "Game.h"

#include "States/MainMenu.h"
#include "States/GamesListMenu.h"
#include "States/OptionsMenu.h"
#include "States/CreditsMenu.h"
#include "States/Pong/pongGame.h"

// Globals.
namespace Options
{
	extern float g_MasterVolume;
	extern void ReadOptions();
}

Game* Game::m_instance = nullptr;
Game::Game()
{
	Options::ReadOptions();

	InitAudioDevice();
	SetMasterVolume(Options::g_MasterVolume);

	m_gameStateManager = std::make_unique<GameStateManager>((int)eGameState::STATES_MAX);
	m_gameStateManager->RegisterState((int)eGameState::MENU, new MainMenuState());
	m_gameStateManager->RegisterState((int)eGameState::GAMELIST, new GamesListMenuState());
	m_gameStateManager->RegisterState((int)eGameState::OPTIONS, new OptionsMenuState());
	m_gameStateManager->RegisterState((int)eGameState::CREDITS, new CreditsMenuState());
	m_gameStateManager->RegisterState((int)eGameState::PONG, new Pong::GameplayState());

	m_gameStateManager->PushState((int)eGameState::MENU);
}
Game::~Game()
{
	CloseAudioDevice();
}

void Game::Update(float deltaTime)
{
	m_gameStateManager->Update(deltaTime);
}
void Game::Draw()
{
	m_gameStateManager->Draw();
}

void Game::ChangeState(const eGameState &state)
{
	m_gameStateManager->PopState(); 
	m_gameStateManager->PushState((int)state);
}

void Game::PushState(const eGameState &state)
{
	m_gameStateManager->PushState((int)state);
}
void Game::PopState()
{
	m_gameStateManager->PopState();
}
