#pragma once

#include "../../Game.h"
#include "../../GameState.h"

#include "../StarParticle.h"

#include <vector>
#include <string>
#include <sstream>
#include <map>

#include <raylib.h>
#include <raymath.h>

enum class eGames
{
	PONG = 0,
	BACK,
	GAMES_MAX
};

class GamesListMenuState : public GameState
{
public:
	GamesListMenuState();
	virtual ~GamesListMenuState();

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
	std::map<eGames, std::string> m_games;

	std::vector<Star> m_particles;

	bool m_isTransition = false;
	bool m_isReturning = false;
	bool m_isFading = false;
	eGameState m_transitionDest;

	float m_menuOffset = (float)-GetScreenWidth();
	float m_fadeOpacity = 0;
	float m_musicVolume = 1.0f;

	Music m_titleMusic;

};
