#include "../stateList.h"
static StateStatus status = { STATE_CONTINUE, false, false, 1 };


// Initialize // Runs only once at directly before game loop
INIT_STATE(Paused)
{
	status.state = STATE_CONTINUE;
	status.pop = false;
	return;
}


// Update // Control the program flow with the return value (has deltaTime)
UPDATE_STATE(Paused)
{
	if (EnterInput())
	{
		status.state = STATE_CIRCUIT;
		status.pop = true;
	}
	return &status;
}


// Pause // Do something in background
PAUSE_STATE(Paused)
{
	return;
}


// Draw // Generic draw function runs directly after update
DRAW_STATE(Paused)
{
	DrawText("PAUSED", 20, GetScreenHeight() * .5f - 25, 50, WHITE);
	DrawText("Click ENTER/SPACE to Resume", 20, GetScreenHeight() * .5f + 25, 30, WHITE);
	DrawText("Click ESCAPE to Go Back to Main Menu (UNDONE)", 20, GetScreenHeight() * .5f + 60, 30, WHITE);
	return;
}


// Exit // Do clean ups before continue to the next state
EXIT_STATE(Paused)
{
	return;
}
