#include "Menu.h"

MenuState::MenuState()
	: m_index{ 0 }
{ }
MenuState::~MenuState()
{ }

void MenuState::OnEnter()
{
	m_musicVolume = 1.0f;
	SetMusicVolume(*m_titleMusic, m_musicVolume);
	if (!IsMusicStreamPlaying(*m_titleMusic))
		PlayMusicStream(*m_titleMusic);

	m_fadeOpacity = 0.0f;
	m_isReturning = true;
}
void MenuState::OnExit()
{
}

bool MenuState::Update(float deltaTime)
{
	if (IsMusicReady(*m_titleMusic))
		UpdateMusicStream(*m_titleMusic);

	// Background Particles
	for (Star &star : *m_particles)
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
		return false;
	}

	if (m_isTransition)
	{
		MenuTransition(m_transitionDest, deltaTime);
		return false;
	}
	else if (m_isFading)
	{
		FadeTransition(m_transitionDest, deltaTime);
		return false;
	}

	return true;
}
void MenuState::Draw()
{
	BeginDrawing();
	ClearBackground(BLACK);
	{
		DrawParticles();
		//
		DrawFade();
	}
	EndDrawing();
}

bool MenuState::MenuTransition(const eGameState &state, float deltaTime)
{
	m_menuOffset = Lerp(m_menuOffset, (float)GetScreenWidth(), 6.0f * deltaTime);
	if (m_menuOffset < GetScreenWidth() - 1.0f)
		return false;

	m_menuOffset = (float)GetScreenWidth();
	m_isTransition = false;

	return true;
}
bool MenuState::FadeTransition(const eGameState &state, float deltaTime)
{
	m_fadeOpacity = Lerp(m_fadeOpacity, 1.0f, 6.0f * deltaTime);
	m_musicVolume = Lerp(m_musicVolume, 0.0f, 6.0f * deltaTime);
	SetMusicVolume(*m_titleMusic, m_musicVolume);
	if (m_fadeOpacity <= 1.0f - 0.0012f)
		return false;

	m_fadeOpacity = 1.0f;
	m_musicVolume = 0.0f;
	SetMusicVolume(*m_titleMusic, m_musicVolume);
	m_isFading = false;

	return true;
}

void MenuState::DrawParticles()
{
	for (const Star &star : *m_particles)
	{
		const Color c = ColorFromHSV(0, 0, star.brightness);
		DrawRectangle((int)star.position.x, (int)star.position.y, (int)star.radius, (int)star.radius, c);
	}
}
void MenuState::DrawFade()
{
	const Color fadeColor = Fade(BLACK, m_fadeOpacity);
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), fadeColor);
}
