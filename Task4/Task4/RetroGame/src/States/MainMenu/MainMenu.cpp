#include "MainMenu.h"

#include "GamesListMenu.h"
#include "OptionsMenu.h"
#include "CreditsMenu.h"

// Globals.
#include "KeyMaps.h"
namespace Options
{
	extern std::unordered_map<eGeneralKeys, KeyboardKey> g_GeneralKeys;
}
using namespace Options;

MainMenuState::MainMenuState()
{ 
	MenuState::MenuState();

	// Setup Particles
	m_particles = new std::vector<Star>();
	m_particles->resize(m_particleCount);

	for (Star &star : *m_particles)
	{
		star.Init();
		star.position.x = (float)GetRandomValue(-1, GetScreenWidth() * 2);
	}

	// Setup Music
	m_titleMusic = LoadMusicStream("./assets/vgm/title.ogg");

	// Menu
	m_menu.insert(std::pair<eMenu, std::string>(eMenu::GAMELIST, "Games List"));
	m_menu.insert(std::pair<eMenu, std::string>(eMenu::OPTIONS, "Options"));
	m_menu.insert(std::pair<eMenu, std::string>(eMenu::CREDITS, "Credits"));
	m_menu.insert(std::pair<eMenu, std::string>(eMenu::QUIT, "Quit"));
}
MainMenuState::~MainMenuState()
{ 
	MenuState::~MenuState();
	// Remove Music
	if (IsMusicReady(m_titleMusic))
		StopMusicStream(m_titleMusic);
	UnloadMusicStream(m_titleMusic);
}

void MainMenuState::OnEnter()
{
	MenuState::OnEnter();
}
void MainMenuState::OnExit()
{
	MenuState::OnExit();
}

bool MainMenuState::Update(float deltaTime)
{
	if (!MenuState::Update(deltaTime))
		return false;

	// Options
	if (IsKeyReleased(g_GeneralKeys[eGeneralKeys::MENU_ACCEPT]))
	{
		switch (m_index)
		{
			case (int)eMenu::GAMELIST:
			{
				m_isTransition = true;
				m_transitionDest = eGameState::GAMELIST;
			} break;
			case (int)eMenu::OPTIONS:
			{
				m_isTransition = true;
				m_transitionDest = eGameState::OPTIONS;
			} break;
			case (int)eMenu::CREDITS:
			{
				m_isTransition = true;
				m_transitionDest = eGameState::CREDITS;
			} break;
			case (int)eMenu::QUIT:
			{
				Game::Get().Quit();
			} break;
			default:
				break;
		}
	}

	if (IsKeyReleased(g_GeneralKeys[eGeneralKeys::MENU_BACK]))
		Game::Get().Quit();

	int dir = IsKeyPressed(g_GeneralKeys[eGeneralKeys::MENU_DOWN]) - IsKeyPressed(g_GeneralKeys[eGeneralKeys::MENU_UP]); // Up or Down.
	m_index += dir;

	if (m_index < 0) // Clamp Direction
		m_index = (int)eMenu::MENU_MAX - 1;
	if (m_index >= (int)eMenu::MENU_MAX)
		m_index = 0;

	return true;
}
void MainMenuState::Draw()
{
	BeginDrawing();
	ClearBackground(BLACK);
	{
		MenuState::DrawParticles();
		// Title
		const char *title = "Retro Games Gallery";
		int titleOff = MeasureText(title, 48) / 2;
		DrawText(title, (int)m_menuOffset + GetScreenWidth() / 2 - titleOff, GetScreenHeight() / 4, 48, WHITE);
		// Options
		for (int i = 0; i < (int)eMenu::MENU_MAX; i++)
		{
			bool j = m_index == i;

			std::stringstream optionText;
			const char *option = m_menu[(eMenu)i].c_str();
			if (j) optionText << "> ";
			optionText << option;

			int optionOff = MeasureText(optionText.str().c_str(), 24) / 2;
			int x = GetScreenWidth()/2 - optionOff;
			int y = GetScreenHeight()/2 + (i*32);
			if (j)
			{
				x += sinf(GetTime() * 8) * 4;
				y += -cosf(GetTime() * 8) * 4;
			}
			DrawText(optionText.str().c_str(), (int)m_menuOffset + x, y, 24, WHITE);
		}
		// Misc
		const int miscFontSize = 18;
		std::string miscText = reinterpret_cast<const char*>(u8"© Thomas Jackson (BadComoc), 2023");
		int miscOff = miscFontSize + 16;
		DrawText(miscText.c_str(), (int)m_menuOffset + 16, GetScreenHeight() - miscOff, miscFontSize, WHITE);
	}
	EndDrawing();
}

bool MainMenuState::MenuTransition(const eGameState &state, float deltaTime)
{
	if (MenuState::MenuTransition(state, deltaTime))
	{
		switch (state)
		{
			case eGameState::GAMELIST:
			{
				auto *state = (GamesListMenuState *)(Game::Get().GetState((int)eGameState::GAMELIST));
				state->PassParticles(m_particles);
				state->PassMusic(m_titleMusic);
				Game::Get().ChangeState(eGameState::GAMELIST);
			} break;
			case eGameState::OPTIONS:
			{
				auto *state = (OptionsMenuState *)(Game::Get().GetState((int)eGameState::OPTIONS));
				state->PassParticles(m_particles);
				state->PassMusic(m_titleMusic);
				Game::Get().ChangeState(eGameState::OPTIONS);
			} break;
			case eGameState::CREDITS:
			{
				auto *state = (CreditsMenuState *)(Game::Get().GetState((int)eGameState::CREDITS));
				state->PassParticles(m_particles);
				state->PassMusic(m_titleMusic);
				Game::Get().ChangeState(eGameState::CREDITS);
			} break;
			default:
				break;
		}
	}
	return true;
}
