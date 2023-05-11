#include "LoadingState.h"

LoadingState::LoadingState()
{ }
LoadingState::LoadingState(eGameState dest)
	: m_destination{ dest }
{ }
LoadingState::~LoadingState()
{ }

void LoadingState::OnEnter()
{
}
void LoadingState::OnExit()
{
}

bool LoadingState::Update(float deltaTime)
{
	// Goto Main Menu when done loading.
	Game::Get().ChangeState(m_destination);

	return false;
}
void LoadingState::Draw()
{
	BeginDrawing();
	ClearBackground(BLACK);
	{
		const char *text = "Loading...";
		const int fontSize = 48;
		const int offset = MeasureText(text, fontSize)/2;
		DrawText(text, GetScreenWidth()/2 - offset, GetScreenHeight()/2, fontSize, WHITE);
	}
	EndDrawing();
}
