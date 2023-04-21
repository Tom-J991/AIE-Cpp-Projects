#include "MainMenu.h"

#include <raylib.h>

void MainMenuState::Update(float deltaTime)
{

}
void MainMenuState::Draw()
{
	BeginDrawing();
	ClearBackground(WHITE);
	{
		DrawText("Retro Game", GetScreenWidth()/2, GetScreenHeight()/2, 24, BLACK);
	}
	EndDrawing();
}
