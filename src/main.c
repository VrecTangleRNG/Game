#include "dependencies.h"


// Main function
int main() 
{
	
	// Initialization
	//-------------------------------------------------------------------------------------
	const int screenWidth = 1200;
	const int screenHeight = 900;
	InitWindow(screenWidth, screenHeight, "Racing Game");
	SetTargetFPS(90);
	
	Texture2D ground = LoadTexture("assets/land.png");

	InitPlayer();
	
	Camera2D camera = { 0 };
	camera.offset = (Vector2){ GetScreenWidth()/2, GetScreenHeight()/2 };
	camera.rotation = 0.0f;
	camera.zoom = 1.5f;
	//-------------------------------------------------------------------------------------
	
	
	// Main game loop
	while (!WindowShouldClose())
	{
		// Update
		//---------------------------------------------------------------------------------
		UpdatePlayer();
		camera.target = (Vector2){ GetPlayerX(), GetPlayerY() };
		//---------------------------------------------------------------------------------
		
		
		// Draw
		//---------------------------------------------------------------------------------
		BeginDrawing();
		
			ClearBackground(BLACK);
			
			BeginMode2D(camera);
			
				DrawTexture(ground, 0, 0, WHITE);
				DrawPlayer();
				
			EndMode2D();
		
			DrawText(TextFormat("FPS: %.2f", (float)GetFPS()), 10, 10, 20, WHITE);
			DrawText(TextFormat("Player X: %.2f", GetPlayerX()), 10, 40, 20, WHITE);
			DrawText(TextFormat("Player Y: %.2f", GetPlayerY()), 10, 70, 20, WHITE);
			
		EndDrawing();
		//---------------------------------------------------------------------------------
	}
	
	// Exit the program
	CloseWindow();
	return 0;
}
