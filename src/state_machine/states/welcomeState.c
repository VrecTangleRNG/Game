#include "../stateList.h"
static StateStatus status = { STATE_CONTINUE, false, false };

static char transparency;


// Initialize // Runs only once at directly before game loop
INIT_STATE(Welcome)
{
	LoadTextureSheet("building_sheet");
	LoadTextureSheet("car_sheet");
	LoadTextureSheet("props_sheet");
}


// Update // Control the program flow with the return value (has deltaTime)
UPDATE_STATE(Welcome)
{
	// NOTE: might overflow that leads to undef behaviour
	Stopwatch *sw = RunStopwatch("wlcm", true);
	transparency = ((uint2)(sw->elapsed * 1.75f) % 2) ? 255 : 0;
	if (EnterInput())
	{
		status.state = STATE_MAIN_MENU;
		status.replace = true;
	}
	return &status;
}


// Pause // Do something in background
PAUSE_STATE(Welcome)
{
	return;
}


// Draw // Generic draw function runs directly after update
DRAW_STATE(Welcome)
{
	ClearBackground(GRAY);
	DrawText("Welcome to the game!", 40, GetScreenHeight() * .4f - 40, 40, BLACK);
	DrawText("Press SPACE to continue", 40, GetScreenHeight() * .75f - 25, 25, (Color){ 0, 0, 0, transparency });
}


// Exit // Do clean ups before continue to the next state
EXIT_STATE(Welcome)
{
	return;
}
