#pragma once

#include "../Game.h"
#include "../GameState.h"

#include "StarParticle.h"

#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include <raylib.h>
#include <raymath.h>

class CreditsMenuState : public GameState
{
public:
	CreditsMenuState();
	virtual ~CreditsMenuState();

	virtual void OnEnter() override;
	virtual void OnExit() override;

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	void SetParticles(std::vector<Star> &particles) { m_particles = particles; }
	void SetMusic(Music &music) { m_titleMusic = music; }

private:
	void SerializeCreditsText();

	void GoBack();
	void MenuTransition(const eGameState &state, float deltaTime);

private:
	float m_scroll = (float)GetScreenHeight()/2;
	float m_scrollSpeed = 16;
	std::string m_creditsText;
	std::vector<std::string> m_credits;

	std::vector<Star> m_particles;

	bool m_isTransition = false;
	bool m_isReturning = false;
	eGameState m_transitionDest;
	float m_menuOffset = (float)-GetScreenWidth();
	float m_fadeOpacity = 0;

	Music m_titleMusic;

};
