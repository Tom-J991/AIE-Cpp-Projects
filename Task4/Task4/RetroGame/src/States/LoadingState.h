#pragma once

#include "Game.h"
#include "GameState.h"

#include <raylib.h>

class LoadingState : public GameState
{
public:
	LoadingState();
	LoadingState(eGameState dest);
	virtual ~LoadingState();

	virtual void OnEnter() override;
	virtual void OnExit() override;

	virtual bool Update(float deltaTime) override;
	virtual void Draw() override;

	eGameState Destination() const { return m_destination; }
	void ChangeDestination(eGameState dest) { m_destination = dest; }

private:
	eGameState m_destination;

};
