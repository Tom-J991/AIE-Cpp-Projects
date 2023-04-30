#include "MainMenu.h"

#include "OptionsMenu.h"
#include "CreditsMenu.h"

MainMenuState::MainMenuState()
{ 
	m_options.insert(std::pair<eOptions, std::string>(eOptions::PONG, "Pong"));
	m_options.insert(std::pair<eOptions, std::string>(eOptions::OPTIONS, "Options"));
	m_options.insert(std::pair<eOptions, std::string>(eOptions::CREDITS, "Credits"));
	m_options.insert(std::pair<eOptions, std::string>(eOptions::QUIT, "Quit"));

	m_particles.resize(m_particleCount);

	m_index = 0;

	for (Star &star : m_particles)
	{
		star.Init();
		star.position.x = (float)GetRandomValue(-1, GetScreenWidth() * 2);
	}

	m_titleMusic = LoadMusicStream("./assets/vgm/title.ogg");
	if (IsMusicReady(m_titleMusic))
		PlayMusicStream(m_titleMusic);
}
MainMenuState::~MainMenuState()
{ 
	if (IsMusicReady(m_titleMusic))
	{
		StopMusicStream(m_titleMusic);
		UnloadMusicStream(m_titleMusic);
	}
}

void MainMenuState::OnEnter()
{
	m_musicVolume = 1.0f;
	SetMusicVolume(m_titleMusic, m_musicVolume);
	if (!IsMusicStreamPlaying(m_titleMusic))
		PlayMusicStream(m_titleMusic);

	m_fadeOpacity = 0.0f;
	m_isReturning = true;
}
void MainMenuState::OnExit()
{
}

void MainMenuState::Update(float deltaTime)
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
		if (m_menuOffset <= 1.0f)
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
	int dir = (IsKeyPressed(KEY_DOWN)||IsKeyPressed(KEY_S)) - (IsKeyPressed(KEY_UP)||IsKeyPressed(KEY_W)); // Up or Down.
	m_index += dir;

	if (m_index < 0) // Clamp Direction
		m_index = (int)eOptions::OPTIONS_MAX-1;
	if (m_index >= (int)eOptions::OPTIONS_MAX)
		m_index = 0;

	if (IsKeyReleased(KEY_ENTER))
	{
		switch (m_index)
		{
			case (int)eOptions::PONG:
			{
				m_isFading = true;
				m_transitionDest = eGameState::PONG;
			} break;
			case (int)eOptions::OPTIONS:
			{
				m_isTransition = true;
				m_transitionDest = eGameState::OPTIONS;
			} break;
			case (int)eOptions::CREDITS:
			{
				m_isTransition = true;
				m_transitionDest = eGameState::CREDITS;
			} break;
			case (int)eOptions::QUIT:
			{
				Game::Get().Quit();
			} break;
			default:
				break;
		}
	}
	if (IsKeyReleased(KEY_ESCAPE))
	{
		Game::Get().Quit();
	}
}
void MainMenuState::Draw()
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
		const char *title = "Retro Games Gallery";
		int titleOff = MeasureText(title, 48) / 2;
		DrawText(title, (int)m_menuOffset + GetScreenWidth() / 2 - titleOff, GetScreenHeight() / 4, 48, WHITE);
		// Options
		for (int i = 0; i < (int)eOptions::OPTIONS_MAX; i++)
		{
			bool j = m_index == i;

			std::stringstream optionText;
			const char *option = m_options[(eOptions)i].c_str();
			if (j) optionText << "> ";
			optionText << option;

			int optionOff = MeasureText(optionText.str().c_str(), 24) / 2;
			DrawText(optionText.str().c_str(), (int)m_menuOffset + GetScreenWidth()/2 - optionOff, GetScreenHeight()/2 + (i*32), 24, WHITE);
		}
		// Misc
		const int miscFontSize = 18;
		const char *miscText = u8"© Thomas Jackson (BadComoc), 2023";
		int miscOff = miscFontSize + 16;
		DrawText(miscText, (int)m_menuOffset + 16, GetScreenHeight() - miscOff, miscFontSize, WHITE);
		// Fade
		const Color fadeColor = Fade(BLACK, m_fadeOpacity);
		DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), fadeColor);
	}
	EndDrawing();
}

void MainMenuState::MenuTransition(const eGameState &state, float deltaTime)
{
	m_menuOffset = Lerp(m_menuOffset, (float)GetScreenWidth(), 6.0f * deltaTime);
	if (m_menuOffset >= GetScreenWidth() - 12.0f)
	{
		m_menuOffset = (float)GetScreenWidth();
		m_isTransition = false;
		switch (state)
		{
			case eGameState::OPTIONS:
			{
				auto *state = (OptionsMenuState *)(Game::Get().GetState((int)eGameState::OPTIONS));
				state->SetParticles(m_particles);
				state->SetMusic(m_titleMusic);
				Game::Get().ChangeState(eGameState::OPTIONS);
			} break;
			case eGameState::CREDITS:
			{
				auto *state = (CreditsMenuState *)(Game::Get().GetState((int)eGameState::CREDITS));
				state->SetParticles(m_particles);
				state->SetMusic(m_titleMusic);
				Game::Get().ChangeState(eGameState::CREDITS);
			} break;
			default:
				break;
		}
	}
}

void MainMenuState::FadeTransition(const eGameState &state, float deltaTime)
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

void Star::Init()
{
	position.x = (float)GetRandomValue(-GetScreenWidth(), -1);
	position.y = (float)GetRandomValue(0, GetScreenHeight());
	radius = (float)GetRandomValue(1, 4);
	brightness = radius / 6;
	speed = radius * 16;
}
