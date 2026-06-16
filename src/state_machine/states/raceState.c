#include "../stateList.h"


static Stopwatch stopwatch;
static Level *currentLevel = NULL;


// Initialize // Runs only once at directly before game loop
void Init_RaceState(void)
{
	StopwatchStart(&stopwatch);
	currentLevel = GetRunningLevel();
}


// Update // Control the program flow with the return value
StateIndex Update_RaceState(float deltaTime)
{
	StopwatchUpdate(&stopwatch);
	UpdatePlayer(deltaTime);
	Vector2 playerPos = GetCenterPlayerPos();
	SetCameraPos(&playerPos);

	float timeStep = 1.0f * GetVirtualTime()->scale / GetConstantFPS();
	UpdatePhysics(timeStep, deltaTime);

	//GetCpShapeFromId(/* TODO */);

	// Control state transition
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
	DrawText(TextFormat("Lap time: %.2f", stopwatch.elapsed), 10, 30, 30, BLACK);
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
