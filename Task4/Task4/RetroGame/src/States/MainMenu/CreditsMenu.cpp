#include "CreditsMenu.h"

#include "MainMenu.h"

#include <fstream>
#include <iostream>

CreditsMenuState::CreditsMenuState()
{ 
	MenuState::MenuState();

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
{ 
	MenuState::~MenuState();
}

void CreditsMenuState::OnEnter()
{
	MenuState::OnEnter();

	m_scroll = (float)GetScreenHeight() / 2;
}
void CreditsMenuState::OnExit()
{
	MenuState::OnExit();
}

const int fontSize = 20;
bool CreditsMenuState::Update(float deltaTime)
{
	if (!MenuState::Update(deltaTime))
		return false;

	// Scrolling
	if (IsKeyDown(KEY_ENTER))
		m_scrollSpeed = 128;
	else
		m_scrollSpeed = 16;
	m_scroll -= m_scrollSpeed * deltaTime;

	const float end = (float)(m_credits.size() * fontSize);
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

	return true;
}
void CreditsMenuState::Draw()
{
	BeginDrawing();
	ClearBackground(BLACK);
	{
		MenuState::DrawParticles();
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
	state->PassParticles(m_particles);
	state->PassMusic(m_titleMusic);
	Game::Get().ChangeState(eGameState::MENU);
}

bool CreditsMenuState::MenuTransition(const eGameState &state, float deltaTime)
{
	if (MenuState::MenuTransition(state, deltaTime))
	{
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
	return true;
}
