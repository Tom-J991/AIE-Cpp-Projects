#include <sstream>
#include "Game.h"
#include <raylib.h>

int main()
{
	InitWindow(800, 600, "Game");
	SetTargetFPS(60);

	auto& game = Game::Get();

	std::stringstream* ss = new std::stringstream;
	while (!WindowShouldClose())
	{
		(*ss) << "Retro Game - FPS: " << GetFPS();
		SetWindowTitle(ss->str().c_str());
		std::stringstream().swap(*ss);

		game.Update(GetFrameTime());
		game.Draw();
	}

	CloseWindow();

	return 0;
}