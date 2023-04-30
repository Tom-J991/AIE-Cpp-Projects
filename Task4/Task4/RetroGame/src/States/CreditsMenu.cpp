#include "CreditsMenu.h"

#include "MainMenu.h"

#include <iostream>

CreditsMenuState::CreditsMenuState()
{ 
	std::ifstream creditsFile("./Credits.txt");
	if (!creditsFile.is_open())
	{
		std::cout << "Could not open Credits File" << std::endl;
	}
	else
	{
		std::stringstream ss;
		for (std::string line; std::getline(creditsFile, line); )
			ss << line << std::endl;
		m_creditsText = ss.str();
		creditsFile.close();
	}

	SerializeCreditsText();
}
CreditsMenuState::~CreditsMenuState()
{ }

void CreditsMenuState::OnEnter()
{
	m_scroll = (float)GetScreenHeight() / 2;
	m_isReturning = true;
}
void CreditsMenuState::OnExit()
{
}

const int fontSize = 20;
void CreditsMenuState::Update(float deltaTime)
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

	// Scrolling
	if (IsKeyDown(KEY_ENTER))
		m_scrollSpeed = 128;
	else
		m_scrollSpeed = 16;
	m_scroll -= m_scrollSpeed * deltaTime;

	const float end = m_credits.size() * fontSize;
	if (m_scroll <= 0 - (end + (fontSize)))
	{
		m_menuOffset = (float)-GetScreenWidth();
		GoBack();
	}

	if (IsKeyReleased(KEY_ESCAPE))
	{
		m_isTransition = true;
		m_transitionDest = eGameState::MENU;
	}
}
void CreditsMenuState::Draw()
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
		// Draw Credits
		for (int i = 0; i < m_credits.size(); i++)
		{
			int creditsOff = MeasureText(m_credits[i].c_str(), fontSize) / 2;
			DrawText(m_credits[i].c_str(), (int)m_menuOffset + GetScreenWidth() / 2 - creditsOff, (int)m_scroll + (i * fontSize), fontSize, WHITE);
		}
	}
	EndDrawing();
}

void CreditsMenuState::SerializeCreditsText()
{
	std::stringstream ss(m_creditsText);
	for (std::string line; std::getline(ss, line, '\n'); )
		m_credits.push_back(line);
}

void CreditsMenuState::GoBack()
{
	auto *state = (MainMenuState *)(Game::Get().GetState((int)eGameState::MENU));
	state->SetParticles(m_particles);
	state->SetMusic(m_titleMusic);
	Game::Get().ChangeState(eGameState::MENU);
}

void CreditsMenuState::MenuTransition(const eGameState &state, float deltaTime)
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
				GoBack();
			} break;
			default:
				break;
		}
	}
}
