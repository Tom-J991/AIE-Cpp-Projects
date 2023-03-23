#include "Application.h"
#include "raylib.h"
#include <stdlib.h>


Application::Application()
{

}

Application::~Application()
{

}

void Application::Run()
{
	InitWindow(m_windowWidth, m_windowHeight, "Simple Tilemap");
	SetTargetFPS(60);

	Load();

	while (!WindowShouldClose())
	{
		Update(GetFrameTime());
		Draw();
	}

	Unload();
}

void Application::Load()
{
	// Task1:
	// Initialise all values in m_tiles array to a random
	// value between 0 and 5 exclusive;
	// -----------------------------------------------------
	
	// write your code here
	for (int y = 0; y < ROWS; ++y)
	{
		for (int x = 0; x < COLS; ++x)
		{
			int col = GetRandomValue(0, 4);
			m_tiles[y * COLS + x] = col;
		}
	}

	// -----------------------------------------------------
}

void Application::Unload()
{

}

#include <iostream>
void Application::Update(float deltaTime)
{
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		Vector2 mousePos = GetMousePosition();

		// Task 3:
		// TODO: Calculate row and col index based on the mouse positon
		int rowIndex = (int)mousePos.y / m_tileHeight; 
		int colIndex = (int)mousePos.x / m_tileWidth;

		// TODO: calculate the index of the tile clicked on based on the row/col index
		int tileIndex = rowIndex * COLS + colIndex;

		m_tiles[tileIndex] += 1;
		if (m_tiles[tileIndex] >= 5)
			m_tiles[tileIndex] = 0;
	}
}

void Application::Draw()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);

	// Task2:
	// use a nested loop to iterate over rows and columns
	// Use raylib's DrawRect method to draw each tile in the array.
	// 	   use the row and col index multipled by m_tileHeight/m_tileWidth
	// 	   to calculate the x and y position for each rectangle.
	// 
	// change the color of the rect drawn based on the value of the tile.
	// 	   We have created a helper function you can use "GetTileColor"
	// --------------------------------------------------------------------
	// write your code here
	float xPos = 0;
	float yPos = 0;
	Color color = GetTileColor(1); // pass in the tilevalue

	for (int y = 0; y < ROWS; ++y)
	{
		for (int x = 0; x < COLS; ++x)
		{
			xPos = x * m_tileWidth;
			yPos = y * m_tileHeight;
			color = GetTileColor(m_tiles[y * COLS + x]);
			DrawRectangle(xPos, yPos, m_tileWidth, m_tileHeight, color);
		}
	}

	// --------------------------------------------------------------------

	EndDrawing();
}

Color Application::GetTileColor(int tileValue)
{
	switch (tileValue)
	{
	case 0: return WHITE;
	case 1: return RED;
	case 2: return GREEN;
	case 3: return BLUE;
	case 4: return YELLOW;
	}
	
	return BLACK;
}