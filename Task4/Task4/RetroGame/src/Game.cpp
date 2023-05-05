#include "Game.h"

#include "States/MainMenu/MainMenu.h"
#include "States/MainMenu/GamesListMenu.h"
#include "States/MainMenu/OptionsMenu.h"
#include "States/MainMenu/CreditsMenu.h"
#include "States/Pong/pongMenu.h"
#include "States/Pong/pongGame.h"
#include "States/Snake/snakeGame.h"

// Globals.
namespace Options
{
	extern float g_MasterVolume;
	extern unsigned int g_ScreenWidth;
	extern unsigned int g_ScreenHeight;

	extern void ReadOptions();
}

Game* Game::m_instance = nullptr;
Game::Game()
{
	Options::ReadOptions();

	InitAudioDevice();
	SetMasterVolume(Options::g_MasterVolume);

	SetWindowSize(Options::g_ScreenWidth, Options::g_ScreenHeight);

	m_gameStateManager = std::make_unique<GameStateManager>((int)eGameState::STATES_MAX);
	m_gameStateManager->RegisterState((int)eGameState::MENU, new MainMenuState());
	m_gameStateManager->RegisterState((int)eGameState::GAMELIST, new GamesListMenuState());
	m_gameStateManager->RegisterState((int)eGameState::OPTIONS, new OptionsMenuState());
	m_gameStateManager->RegisterState((int)eGameState::CREDITS, new CreditsMenuState());
	m_gameStateManager->RegisterState((int)eGameState::PONG_MENU, new Pong::TitleState());
	m_gameStateManager->RegisterState((int)eGameState::PONG_GAME, new Pong::GameplayState());
	m_gameStateManager->RegisterState((int)eGameState::SNAKE_GAME, new Snake::GameplayState());

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
