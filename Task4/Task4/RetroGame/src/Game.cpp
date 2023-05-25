#include "Game.h"

// Game States
#include "States/LoadingState.h"
#include "States/MainMenu/MainMenu.h"
#include "States/MainMenu/GamesListMenu.h"
#include "States/MainMenu/OptionsMenu.h"
#include "States/MainMenu/KeymapMenu.h"
#include "States/MainMenu/CreditsMenu.h"
#include "States/Pong/pongMenu.h"
#include "States/Pong/pongGame.h"
#include "States/Snake/snakeGame.h"

// Globals.
#include "Options.h"
using namespace Options;

Game* Game::m_instance = nullptr;
Game::Game()
{
	InitAudioDevice();
	// Initialize Settings
	ReadOptions();
	SetMasterVolume(g_MasterVolume);

	SetWindowSize(g_ScreenWidth, g_ScreenHeight);
	const int monitor = GetCurrentMonitor();
	const int mWidth = GetMonitorWidth(monitor);
	const int mHeight = GetMonitorHeight(monitor);
	SetWindowPosition(mWidth/2 - GetScreenWidth()/2, mHeight/2 - GetScreenHeight()/2);

	if (g_Fullscreen == true)
		ToggleFullscreen();

	// Initialize States
	m_gameStateManager = std::make_unique<GameStateManager>((int)eGameState::STATES_MAX);
	m_gameStateManager->RegisterState((int)eGameState::LOAD, new LoadingState(eGameState::MENU));
	// Main Menu
	m_gameStateManager->RegisterState((int)eGameState::MENU, new MainMenuState());
	m_gameStateManager->RegisterState((int)eGameState::GAMELIST, new GamesListMenuState());
	m_gameStateManager->RegisterState((int)eGameState::OPTIONS, new OptionsMenuState());
	m_gameStateManager->RegisterState((int)eGameState::KEYMAP, new KeymapMenuState());
	m_gameStateManager->RegisterState((int)eGameState::CREDITS, new CreditsMenuState());
	// Pong
	m_gameStateManager->RegisterState((int)eGameState::PONG_MENU, new Pong::TitleState());
	m_gameStateManager->RegisterState((int)eGameState::PONG_GAME, new Pong::GameplayState());
	// Snake
	m_gameStateManager->RegisterState((int)eGameState::SNAKE_GAME, new Snake::GameplayState());

	// Load First State
	m_gameStateManager->PushState((int)eGameState::LOAD);
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
