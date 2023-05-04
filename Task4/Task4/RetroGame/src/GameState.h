#pragma once

class GameState
{
	friend class GameStateManager;
public:
	GameState() { }
	virtual ~GameState() { }

	bool IsActive() const { return m_active; }

protected:
	virtual bool Update(float deltaTime) = 0;
	virtual void Draw() = 0;

	void Enter() { m_active = true; OnEnter(); }
	void Exit() { m_active = false; OnExit(); }

	virtual void OnEnter() { }
	virtual void OnExit() { }
	virtual void OnPushed() { }
	virtual void OnPopped() { }

private:
	bool m_active = false;

};
