#include <sstream>
#include "Game.h"
#include <raylib.h>

int main()
{
	InitWindow(640, 480, "Game");
	SetTargetFPS(60);
	SetExitKey(NULL);

	auto& game = Game::Get();

	std::stringstream* ss = new std::stringstream;
	while (!(WindowShouldClose() || game.IsQuitting()))
	{
		(*ss) << "Retro Games Gallery - FPS: " << GetFPS();
		SetWindowTitle(ss->str().c_str());
		std::stringstream().swap(*ss);
		
		game.Update(GetFrameTime());
		game.Draw();
	}

	return 0;
}