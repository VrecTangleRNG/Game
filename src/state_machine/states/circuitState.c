#include "../stateList.h"
static StateStatus status = { STATE_CONTINUE, false, false };

static LapTracker playerLap;


// Initialize // Runs only once at directly before game loop
INIT_STATE(Circuit)
{
	// Set current level map
	char *currentMap = "map1.json";

	// Setup camera and physics world
	SetupCamera();
	InitPhysics();

	// Load map
	LoadMap(currentMap);
	PlaceObjects();

	// Load level the map has
	LoadCurrentLevel(currentMap, "circuits.json");
	SetRunningLevelIndex(0);
	Level *level = GetRunningLevel();

	// Initialize player
	InitLapTracker(&playerLap, level);
	InitPlayer(GetSpawnpoint(level->spawnpointId).pos, level->angle);
}


// Update // Control the program flow with the return value (has deltaTime)
UPDATE_STATE(Circuit)
{
	// Update player
	UpdatePlayer(deltaTime);
	Vector2 playerPos = GetCenterPlayerPos();
	SetCameraPos(&playerPos);

	// Update physics world after all of physics action were made
	UpdatePhysics(1.0f / GetConstantFPS(), deltaTime);
	return &status;
}


// Pause // Do something in background
PAUSE_STATE(Circuit)
{
	return;
}


// Draw // Generic draw function runs directly after update
DRAW_STATE(Circuit)
{
	ClearBackground(GRAY);
	BeginMode2D(GetCamera());
	DrawMap();
	DrawPlayer();
	EndMode2D();
	DrawFPS(10, GetScreenHeight() - 20);
}


// Exit // Do clean ups before continue to the next state
EXIT_STATE(Circuit)
{
	return;
}
