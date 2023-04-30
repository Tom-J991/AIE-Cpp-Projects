#pragma once

#include "../Game.h"
#include "../GameState.h"

#include "StarParticle.h"

#include <vector>
#include <string>
#include <sstream>
#include <map>

#include <raylib.h>
#include <raymath.h>

enum class eOptions
{
	PONG = 0,
	OPTIONS,
	CREDITS,
	QUIT,
	OPTIONS_MAX
};

class MainMenuState : public GameState
{
public:
	MainMenuState();
	virtual ~MainMenuState();

	virtual void OnEnter() override;
	virtual void OnExit() override;

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	void SetParticles(std::vector<Star> &particles) { m_particles = particles; }
	void SetMusic(Music &music) { m_titleMusic = music; }

private:
	void MenuTransition(const eGameState &state, float deltaTime);
	void FadeTransition(const eGameState &state, float deltaTime);

private:
	int m_index = 0;
	std::map<eOptions, std::string> m_options;

	bool m_isTransition = false;
	bool m_isReturning = false;
	eGameState m_transitionDest;
	float m_menuOffset = 0;
	float m_fadeOpacity = 0;

	int m_particleCount = 1024;
	std::vector<Star> m_particles;

	Music m_titleMusic;

};