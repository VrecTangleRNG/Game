#include "../../HEADERS/stateList.h"
static StateStatus status = { STATE_CONTINUE, false, false };


// Initialize // Runs only once at directly before game loop
INIT_STATE(Splash)
{
	return;
}


// Update // Control the program flow with the return value (has deltaTime)
UPDATE_STATE(Splash)
{
	return &status;
}


// Pause // Do something in background
PAUSE_STATE(Splash)
{
	return;
}


// Draw // Generic draw function runs directly after update
DRAW_STATE(Splash)
{
	return;
}


// Exit // Do clean ups before continue to the next state
EXIT_STATE(Splash)
{
	return;
}
