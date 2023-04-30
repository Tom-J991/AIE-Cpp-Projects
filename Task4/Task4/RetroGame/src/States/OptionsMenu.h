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

enum class eOptionParameters
{
	MASTER_VOLUME = 0,
	BACK,
	OPTIONS_MAX
};

class OptionsMenuState : public GameState
{
public:
	OptionsMenuState();
	virtual ~OptionsMenuState();

	virtual void OnEnter() override;
	virtual void OnExit() override;

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	void SetParticles(std::vector<Star> &particles) { m_particles = particles; }
	void SetMusic(Music &music) { m_titleMusic = music; }

private:
	void MenuTransition(const eGameState &state, float deltaTime);

private:
	int m_index = 0;
	std::map<eOptionParameters, std::string> m_options;
	std::map<eOptionParameters, bool> m_optionsBold;

	std::vector<Star> m_particles;

	bool m_isTransition = false;
	bool m_isReturning = false;
	eGameState m_transitionDest;
	float m_menuOffset = (float)-GetScreenWidth();
	float m_fadeOpacity = 0;

	Music m_titleMusic;

};
