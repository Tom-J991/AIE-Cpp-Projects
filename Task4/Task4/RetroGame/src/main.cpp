#include <sstream>

#include "Game.h"
#include <raylib.h>

int main()
{
	// Create Window
	InitWindow(800, 600, "Retro Games Gallery");
	SetTargetFPS(60);
	SetExitKey(NULL);

	// Game Loop
	auto& game = Game::Get();
	std::stringstream* ss = new std::stringstream;
	while (!(WindowShouldClose() || game.IsQuitting()))
	{
#ifdef _DEBUG
		(*ss) << "Retro Games Gallery - FPS: " << GetFPS();
		SetWindowTitle(ss->str().c_str()); // Put FPS in window title
		std::stringstream().swap(*ss);
#endif
		
		game.Update(GetFrameTime());
		game.Draw();
	}

	// Close
	game.Destroy();
	CloseWindow();

	return 0;
}