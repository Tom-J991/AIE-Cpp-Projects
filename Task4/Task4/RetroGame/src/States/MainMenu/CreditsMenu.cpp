#include "CreditsMenu.h"

#include "MainMenu.h"

#include <fstream>
#include <iostream>

// Globals.
#include "KeyMaps.h"
namespace Options
{
	extern std::unordered_map<eGeneralKeys, KeyboardKey> g_GeneralKeys;
}
using namespace Options;

CreditsMenuState::CreditsMenuState()
{ 
	MenuState::MenuState();

	std::ifstream creditsFile("./assets/Credits.txt");
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
}
CreditsMenuState::~CreditsMenuState()
{ 
	MenuState::~MenuState();
}

void CreditsMenuState::OnEnter()
{
	MenuState::OnEnter();

	m_scroll = (float)GetScreenHeight() / 2;

	FormatText();
}
void CreditsMenuState::OnExit()
{
	MenuState::OnExit();
}

bool CreditsMenuState::Update(float deltaTime)
{
	if (!MenuState::Update(deltaTime))
		return false;

	// Scrolling
	if (IsKeyDown(g_GeneralKeys[eGeneralKeys::MENU_ACCEPT]))
		m_scrollSpeed = 128;
	else
		m_scrollSpeed = 16;
	m_scroll -= m_scrollSpeed * deltaTime;

	const float end = (float)(m_credits.size() * m_fontSize);
	if (m_scroll <= 0 - (end + (m_fontSize)))
	{
		m_menuOffset = (float)-GetScreenWidth();
		GoBack();
	}

	if (IsKeyReleased(g_GeneralKeys[eGeneralKeys::MENU_BACK]))
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
		// Draw Credits text (line by line)
		for (int i = 0; i < m_credits.size(); i++)
		{
			int creditsOff = MeasureText(m_credits[i].c_str(), m_fontSize) / 2;
			DrawText(m_credits[i].c_str(), (int)m_menuOffset + GetScreenWidth() / 2 - creditsOff, (int)m_scroll + (i * m_fontSize), m_fontSize, WHITE);
		}
	}
	EndDrawing();
}

void CreditsMenuState::FormatText()
{
	m_credits.clear();

	// Word Wrap
	std::stringstream text(m_creditsText);
	std::stringstream newText;
	const int spaceWidth = MeasureText(" ", m_fontSize);
	const int lineWidth = GetScreenWidth() - (spaceWidth * m_fontSize);
	int spaceLeft = lineWidth;
	for (std::string word; std::getline(text, word, ' '); )
	{
		if (MeasureText(word.c_str(), m_fontSize) + spaceWidth > spaceLeft)
		{
			newText << '\n';
			newText << word;
			spaceLeft = lineWidth - (MeasureText(word.c_str(), m_fontSize) + spaceWidth);
		}
		else
		{
			spaceLeft = spaceLeft - (MeasureText(word.c_str(), m_fontSize) + spaceWidth);
			newText << word;
		}
		newText << ' ';
	}

	// Split lines into vector.
	std::stringstream ss(newText.str());
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
