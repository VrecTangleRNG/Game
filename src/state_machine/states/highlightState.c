#include "../stateList.h"


// Initialize // Runs only once at directly before game loop
void Init_HighlightState(void)
{
	InitPhysics();

	// Load textures
	LoadTextureSheet("building_sheet");
	LoadTextureSheet("props_sheet");
	LoadTextureSheet("car_sheet");

	// Load map data
	char *mapFile = "map1.json";
	LoadMap(mapFile);
	LoadCurrentLevel(mapFile, "circuits.json");
	SetRunningLevelIndex(0);
	PlaceObjects();

	// Initialize player
	b2Vec2 initPlayerPos = GetSpawnpoint(0).pos;
	InitPlayer(initPlayerPos, 180.0f);

	// Setup camera
	SetupCamera();
	Vector2 pos = GetCenterPlayerPos();
	SetCameraPos(&pos);
}


// Update // Control the program flow with the return value
StateIndex Update_HighlightState(float deltaTime)
{
	if (IsKeyPressed(KEY_SPACE)) return STATE_COUNTDOWN;
	return STATE_CONTINUE;
}


// Draw // Generic draw function runs directly after update
void Draw_HighlightState(void)
{
	BeginMode2D(GetCamera());
		DrawMap();
		DrawPlayer();
	EndMode2D();
	DrawText("Press SPACE to play the countdown", 10, GetScreenHeight() * .5f - 30, 30, BLACK);
}


// Escape // Return 1 to continue running, 0 to exit program entirely
int Escape_HighlightState(StateIndex toState)
{
	return 1;
}
