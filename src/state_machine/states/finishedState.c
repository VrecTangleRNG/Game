#include "../stateList.h"
static StateStatus status = { STATE_CONTINUE, false, false };


// Initialize // Runs only once at directly before game loop
INIT_STATE(Finished)
{
	return;
}


// Update // Control the program flow with the return value (has deltaTime)
UPDATE_STATE(Finished)
{
	return &status;
}


// Pause // Do something in background
PAUSE_STATE(Finished)
{
	return;
}


// Draw // Generic draw function runs directly after update
DRAW_STATE(Finished)
{
	return;
}


// Exit // Do clean ups before continue to the next state
EXIT_STATE(Finished)
{
	return;
}
