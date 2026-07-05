#include "../stateList.h"
static StateStatus status = { STATE_CONTINUE, false, false, 1 };


// Initialize // Runs only once at directly before game loop
INIT_STATE(Exit)
{
	status.pop = false;
	return;
}


// Update // Control the program flow with the return value (has deltaTime)
UPDATE_STATE(Exit)
{
	if (EscapeInput()) status.pop = true;
	if (EnterInput()) status.state = QUIT_REQUEST;
	return &status;
}


// Pause // Do something in background
PAUSE_STATE(Exit)
{
	return;
}


// Draw // Generic draw function runs directly after update
DRAW_STATE(Exit)
{
	DrawText("Are you sure you want to quit?", 20, GetScreenHeight() * .5f - 15, 30, BLACK);
	DrawText("Press ENTER to confirm", 20, GetScreenHeight() * .5f - 15 + 40, 30, BLACK);
	DrawText("Press ESCAPE to go back", 20, GetScreenHeight() * .5f - 15 + 80, 30, BLACK);
}


// Exit // Do clean ups before continue to the next state
EXIT_STATE(Exit)
{
	return;
}
