#include "GamesListMenu.h"

#include "MainMenu.h"

GamesListMenuState::GamesListMenuState()
{ 
	m_games.insert(std::pair<eGames, std::string>(eGames::PONG, "PONG"));
	m_games.insert(std::pair<eGames, std::string>(eGames::BACK, "Go Back"));
}
GamesListMenuState::~GamesListMenuState()
{ }

void GamesListMenuState::OnEnter()
{
	m_musicVolume = 1.0f;
	SetMusicVolume(m_titleMusic, m_musicVolume);
	if (!IsMusicStreamPlaying(m_titleMusic))
		PlayMusicStream(m_titleMusic);

	m_fadeOpacity = 0.0f;
	m_isReturning = true;
}
void GamesListMenuState::OnExit()
{
}

void GamesListMenuState::Update(float deltaTime)
{
	if (IsMusicReady(m_titleMusic))
		UpdateMusicStream(m_titleMusic);

	// Background Particles
	for (Star &star : m_particles)
	{
		if (star.position.x > GetScreenWidth())
			star.Init();

		star.position.x += star.speed * deltaTime;
	}

	// Transition
	if (m_isReturning)
	{
		m_menuOffset = Lerp(m_menuOffset, 0.0f, 8.0f * deltaTime);
		if (m_menuOffset >= -1.0f)
		{
			m_menuOffset = 0.0f;
			m_isReturning = false;
		}
		return;
	}
	if (m_isTransition)
	{
		MenuTransition(m_transitionDest, deltaTime);
		return;
	}
	if (m_isFading)
	{
		FadeTransition(m_transitionDest, deltaTime);
		return;
	}

	// Options
	if (IsKeyReleased(KEY_ENTER))
	{
		switch (m_index)
		{
			case (int)eGames::PONG:
			{
				m_isFading = true;
				m_transitionDest = eGameState::PONG;
			} break;
			case (int)eGames::BACK:
			{
				m_isTransition = true;
				m_transitionDest = eGameState::MENU;
			} break;
			default:
				break;
		}
	}

	if (IsKeyReleased(KEY_ESCAPE))
	{
		m_isTransition = true;
		m_transitionDest = eGameState::MENU;
	}

	int dir = (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) - (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)); // Up or Down.
	m_index += dir;

	if (m_index < 0) // Clamp Direction
		m_index = (int)eGames::GAMES_MAX - 1;
	if (m_index >= (int)eGames::GAMES_MAX)
		m_index = 0;
}
void GamesListMenuState::Draw()
{
	BeginDrawing();
	ClearBackground(BLACK);
	{
		// Background Particles
		for (const Star &star : m_particles)
		{
			const Color c = ColorFromHSV(0, 0, star.brightness);
			DrawRectangle((int)star.position.x, (int)star.position.y, (int)star.radius, (int)star.radius, c);
		}
		// Title
		const char *title = "Games: ";
		int titleOff = MeasureText(title, 48) / 2;
		DrawText(title, (int)m_menuOffset + GetScreenWidth() / 2 - titleOff, GetScreenHeight() / 4, 48, WHITE);
		// Options
		for (int i = 0; i < (int)eGames::GAMES_MAX; i++)
		{
			bool j = m_index == i;

			std::stringstream optionText;
			const char *option = m_games[(eGames)i].c_str();
			if (j) optionText << "> ";
			optionText << option;

			const int fontSize = 24;
			int optionOff = MeasureText(optionText.str().c_str(), fontSize) / 2;
			DrawText(optionText.str().c_str(), (int)m_menuOffset + GetScreenWidth() / 2 - optionOff, GetScreenHeight() / 2 + (i * 32), fontSize, WHITE);
		}
		// Fade
		const Color fadeColor = Fade(BLACK, m_fadeOpacity);
		DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), fadeColor);
	}
	EndDrawing();
}

void GamesListMenuState::MenuTransition(const eGameState &state, float deltaTime)
{
	m_menuOffset = Lerp(m_menuOffset, (float)-GetScreenWidth(), 6.0f * deltaTime);
	if (m_menuOffset <= -GetScreenWidth() + 12.0f)
	{
		m_menuOffset = (float)-GetScreenWidth();
		m_isTransition = false;
		switch (state)
		{
			case eGameState::MENU:
			{
				auto *state = (MainMenuState *)(Game::Get().GetState((int)eGameState::MENU));
				state->PassParticles(&m_particles);
				state->PassMusic(&m_titleMusic);
				Game::Get().ChangeState(eGameState::MENU);
			} break;
			default:
				break;
		}
	}
}
void GamesListMenuState::FadeTransition(const eGameState &state, float deltaTime)
{
	m_fadeOpacity = Lerp(m_fadeOpacity, 1.0f, 6.0f * deltaTime);
	m_musicVolume = Lerp(m_musicVolume, 0.0f, 6.0f * deltaTime);
	SetMusicVolume(m_titleMusic, m_musicVolume);
	if (m_fadeOpacity >= 1.0f - 0.0012f)
	{
		m_fadeOpacity = 1.0f;
		m_musicVolume = 0.0f;
		SetMusicVolume(m_titleMusic, m_musicVolume);
		m_isFading = false;
		switch (state)
		{
			case eGameState::PONG:
			{
				if (IsMusicStreamPlaying(m_titleMusic))
					StopMusicStream(m_titleMusic);
				Game::Get().ChangeState(eGameState::PONG);
			} break;
			default:
				break;
		}
	}
}
