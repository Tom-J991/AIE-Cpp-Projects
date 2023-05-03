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

class MenuState : public GameState
{
public:
	MenuState();
	virtual ~MenuState();

	virtual void OnEnter() override;
	virtual void OnExit() override;

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	virtual void PassParticles(std::vector<Star> *particles) { m_particles = particles; }
	virtual void PassMusic(Music *music) { m_titleMusic = music; }

protected:
	virtual void MenuTransition(const eGameState &state, float deltaTime);
	virtual void FadeTransition(const eGameState &state, float deltaTime);

	void DrawParticles();
	void DrawFade();

protected:
	int m_index = 0;

	const int m_particleCount = 1024;
	std::vector<Star> *m_particles;

	bool m_isTransition = false;
	bool m_isReturning = false;
	bool m_isFading = false;
	eGameState m_transitionDest;

	float m_menuOffset = (float)-GetScreenWidth();
	float m_fadeOpacity = 0;
	float m_musicVolume = 1.0f;

	Music* m_titleMusic;

};
