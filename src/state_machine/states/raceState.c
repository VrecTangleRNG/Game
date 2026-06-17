#include "../stateList.h"


static Stopwatch stopwatch;
static Level *currentLevel = NULL;
static LapTracker playerLapProg = { 0 };
static smalluint cpIndex = 0;
static bool firstIteration = true;


// Initialize // Runs only once at directly before game loop
void Init_RaceState(void)
{
	StopwatchStart(&stopwatch);
	currentLevel = GetRunningLevel();
	InitLapTracker(&playerLapProg, currentLevel);
}


// Update // Control the program flow with the return value
StateIndex Update_RaceState(float deltaTime)
{
	// Update lap time and player
	StopwatchUpdate(&stopwatch);
	UpdatePlayer(deltaTime);
	Vector2 playerPos = GetCenterPlayerPos();
	SetCameraPos(&playerPos);

	// Update physics
	float timeStep = 1.0f * GetVirtualTime()->scale / GetConstantFPS();
	UpdatePhysics(timeStep, deltaTime);

	// Update lap
		// Check whether the player has passed the target checkpoint
	b2ShapeId *targetCpShape = GetCpShapeFromId(playerLapProg.currentCp);
	b2ShapeId *overlapCp = CheckSensorCollision(GetPlayerShape(), NULL, 1);
	if (overlapCp != NULL && B2_ID_EQUALS(*overlapCp, *targetCpShape))
	{
			// Check if player reached finish line (ignore first check first checkpoint)
		if (cpIndex == 0 && !firstIteration) playerLapProg.currentLap++;
		firstIteration = false;
		cpIndex = (cpIndex + 1) % (currentLevel->cpIdCount);
		playerLapProg.currentCp = currentLevel->checkpointIds[cpIndex];
	}

	// Control state transition
	if (playerLapProg.currentLap > 3)
	{
		playerLapProg.currentLap = 3;
		return STATE_EXIT;				// TODO: make result screen state
	}
	return STATE_CONTINUE;
}


// Draw // Generic draw function runs directly after update
void Draw_RaceState(void)
{
	BeginMode2D(GetCamera());
		DrawMap();
		DrawPlayer();
	EndMode2D();
	DrawDriveModeUi();
	DrawText
	(
		TextFormat
		(
			"Lap time: %02d:%02d.%03d",
			ExtractTime(stopwatch.elapsed, MINUTES),
			ExtractTime(stopwatch.elapsed, SECONDS),
			ExtractTime(stopwatch.elapsed, MSECONDS)
		),
		10, 30, 30, BLACK
	);
	DrawText(TextFormat("Lap: %d/3", playerLapProg.currentLap), 10, 60, 30, BLACK);
}


// Escape // Return 1 to continue running, 0 to exit program entirely
int Escape_RaceState(StateIndex toState)
{
	switch (toState)
	{
		case STATE_EXIT:
			FreeMapDatas();
			DestroyMapBodies();
			FreeAllTextures();
			return 1;

		default: return 1;
	}
}
