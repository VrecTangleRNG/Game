#include "../stateList.h"
static StateStatus status = { STATE_CONTINUE, false, false, 1 };

static LapTracker playerLap;
static bool firstTimeEnter = true;
static Stopwatch *playerLapTimer;


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
	// TODO: somehow, after repeatedly entering and quiting game, it fail to load initpos
	InitPlayer(GetSpawnpoint(level->spawnpointId).pos, level->angle);

	// Set initial camera focus
	Vector2 playerPos = GetCenterPlayerPos();
	SetCameraPos(&playerPos);

	// Initialize lap time
	firstTimeEnter = true;
	playerLapTimer = InitStopwatch("plyr");
}


// Update // Control the program flow with the return value (has deltaTime)
UPDATE_STATE(Circuit)
{
	// Enter getReadyState first before playing any further
	if (firstTimeEnter)
	{
		firstTimeEnter = false;
		status.state = STATE_GET_READY;
		return &status;
	}
	else status.state = STATE_CONTINUE;

	// Start lap timer
	SetPlayerControl(HELD);
	playerLapTimer = RunStopwatch("plyr", false);

	// Update player
	UpdatePlayer(deltaTime);
	Vector2 playerPos = GetCenterPlayerPos();
	SetCameraPos(&playerPos);

	// Update physics world after all of physics action were made
	UpdatePhysics(1.0f / GetConstantFPS(), deltaTime);

	// Set progress that the player has made
	RunLapTracker(&playerLap, GetRunningLevel(), GetPlayerShape());

	// DEBUG
	// static float timer = .0f;
	// timer += deltaTime;
	// if (timer >= 1.5f)
	// {
	// 	printf("cl: %d\n", playerLap.currentLap);
	// 	printf("ccpi: %d\n\n", playerLap.currentCpIndex);
	// 	timer = .0f;
	// }

	// Control state flow
	if (playerLap.currentLap > 3)	status.state = STATE_FINISHED;
	if (EscapeInput()) 				status.state = STATE_PAUSED;
	return &status;
}


// Pause // Do something in background (also has deltaTime)
PAUSE_STATE(Circuit)
{
	switch (status.state) {
		case STATE_FINISHED:
			SetPlayerControl(RELEASE);
			UpdatePlayer(deltaTime);
			UpdatePhysics(1.0f / GetConstantFPS(), deltaTime);
			break;

		default: return;
	}
}


// Draw // Generic draw function runs directly after update
DRAW_STATE(Circuit)
{
	// Draw physical gameplay objects
	ClearBackground(GRAY);
	BeginMode2D(GetCamera());
	DrawMap();
	DrawPlayer();
	DrawRectangle(0, 0, 100, 100, BLUE);
	EndMode2D();

	// Control ui behaviour during some state
	switch (status.state)
	{
		case STATE_CONTINUE: break;
		case STATE_FINISHED: return;
	}

	// Draw lap counter
	DrawText
	(
		TextFormat("Lap: %d/3", (playerLap.currentLap > 3) ? 3 : playerLap.currentLap),
		10, 10, 30, WHITE
	);

	// Draw lap timer
	DrawText
	(
		TextFormat
		(
			"Time: %02d:%02d.%03d",
			ExtractTime(playerLapTimer->elapsed, MINUTES),
			ExtractTime(playerLapTimer->elapsed, SECONDS),
			ExtractTime(playerLapTimer->elapsed, MSECONDS)
		),
		10, 40, 30, WHITE
	);

	// Draw FPS
	DrawRectangle(0, GetScreenHeight() - 20, 100, 30, BLACK);
	DrawFPS(10, GetScreenHeight() - 20);
}


// Exit // Do clean ups before continue to the next state
EXIT_STATE(Circuit)
{
	CleanTimeStorage();
	FreeMapDatas();
	DestroyMapBodies();
	UnloadCurrentLevel();
}
